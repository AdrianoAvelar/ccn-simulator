#include "CcnCore.h"
#include "lru_cache.h"
#include "CcnPacket_m.h"
#include "CcnAppMessage_m.h"
#include "Util.h"
#include "Ieee802Ctrl.h"

Define_Module (CcnCore);

CcnCore::CcnCore() {

    ccnModule = 0;
    ccnr = 0;
    contentStore = 0;
    pitTimeoutMsg = new cMessage("pitTimeout");
    fibTimeoutMsg = new cMessage("fibTimeout");

    server_hit = 0;
    tot_delay = 0;
}

void CcnCore::initialize() {

    this->debugLevel = ::defaultDebugLevel;
    hasCcnr = false;

    RTT = par("RTT");
    char nome[16];
    sprintf(nome, "pit_size_%s", getParentModule()->getParentModule()->getName());

    pitsizeSignal = registerSignal("pit_size");

    //Can we use only one timeout for PIT and FIB?
    //Get this information from ini.
    timeoutPIT = par("pit_timeout");
    timeoutFIB = par("fib_timeout");

    statistic = new cMessage("Statistic");
    scheduleAt(simTime() + STAT_INTERVAL, statistic);

    if (timeoutPIT > 0)
    scheduleAt(simTime() + timeoutPIT, pitTimeoutMsg);

    if (timeoutFIB > 0)
    scheduleAt(simTime() + timeoutFIB, fibTimeoutMsg);

    /* ContentStore Strategy*/
    contentStore = (base_cache *) gate("content_store_port$o")->getNextGate()->getOwner();

    if (getParentModule()->par("hasCcnr")) {
        ccnr = (Ccnr *) gate("ccnr_port$o")->getNextGate()->getOwner();
        ccnr->init();
        hasCcnr = true;
    }

//    ccnfib = (ForwardingTable*)getParentModule()
//    ->getParentModule()->getParentModule()->getSubmodule("forwardingTable");

    ccnfib = getModuleFromPar<ForwardingTable>(par("forwardingTableModule"), this);

    if(ccnfib == NULL)
        opp_error("CcnCore: Couldn't get ForwardingTable.");
    //Add some basic rules

    //FIXME:[EAMA]strategy = (strategy_layer *) gate("strategy_port$o")->getNextGate()->getOwner();

    //Betweenness decision strategy
//    cTopology topo;
//    vector < string > types;
//    //Extract topology map
//    types.push_back("ccnlite.compounds.node.CcnCore");
//    topo.extractByNedTypeName(types);
//    topo.betweenness_centrality();
//    cTopology::Node *node = topo.getNode(getParentModule()->getParentModule()->getIndex()); //iterator node
//    my_btw = node->get_betweenness();
    my_btw = getAncestorPar("centrality");
}

void CcnCore::handleMessage(cMessage *msg) {

    if (msg == statistic) {
        //  DBGPRT(EVAUX, Info, this->getFullPath()) << "Checking for Statistics\n";
        emit(pitsizeSignal,PIT.size());
        //pitSizeVector.record();

    } else if (msg == pitTimeoutMsg) {

       // PRINT_ERR << "Timeout pit: "<< simTime() << ENDL;
        //DBGPRT(EVAUX, Info, this->getFullPath()) << "Checking for stale PIT entry\n";
        double diff;
        PIT_TABLE::iterator it = PIT.begin();
        for (; it != PIT.end();) {

            diff = (simTime().dbl() - it->second.time.dbl());

            if (diff > timeoutPIT) {
                // dumpPIT();
                it = PIT.erase(it);

                if (PIT.size() == 0)
                    break;
            } else {
                it++;
            }
        }

        scheduleAt(simTime() + timeoutPIT, pitTimeoutMsg);
    }else if(msg == fibTimeoutMsg){

        // PRINT_ERR << "Timeout pit: "<< simTime() << ENDL;
         //DBGPRT(EVAUX, Info, this->getFullPath()) << "Checking for stale PIT entry\n";
         double diff;
         ForwardingTable::FIB_TABLE* FIB = ccnfib->getTablePtr();

         ForwardingTable::FIB_TABLE::iterator it =  FIB->begin();
         for (; it != FIB->end();) {

             double time = it->second.time.dbl();

             diff = (simTime().dbl() - time);



             if (diff > timeoutFIB && it->second.isLocal == false ) {
//                 ccnfib->printForwardingTable();

                 it = FIB->erase(it);

                 if (FIB->size() == 0)
                     break;
             } else {
                 it++;
             }
         }

         scheduleAt(simTime() + timeoutFIB, fibTimeoutMsg);
    }
}

std::string CcnCore::macToString(char *srcAddr) {

    char mac[18];

    memset(mac + 17, '\0', sizeof(char));
    sprintf(mac, "%2.2X-%2.2X-%2.2X-%2.2X-%2.2X-%2.2X",
            (unsigned char) srcAddr[0], (unsigned char) srcAddr[1],
            (unsigned char) srcAddr[2], (unsigned char) srcAddr[3],
            (unsigned char) srcAddr[4], (unsigned char) srcAddr[5]);
    return std::string(mac);
}

PIT_TABLE::iterator CcnCore::pitLookup(std::string contentName) {

    std::string content = contentName;
    PIT_TABLE::iterator pit_entry;

    // dumpPIT();

    for (;;) {

        if (content == "") {
            content = "/";
            pit_entry = PIT.find(content);
            break;
        }

        pit_entry = PIT.find(content);
        if (pit_entry != PIT.end()) {
            break;
        }

        content = Util::getPrefixContentName(content);
    }

    return pit_entry;
}

//FIXME: muda essa função, talvez criar uma classe só para tabelas
void CcnCore::dumpPIT() {

    if (PIT.size() == 0) {
        DBGPRT(EVAUX, Info, this->getFullPath()) << "PIT is empty...\n";
        return;
    }

    char output[254];

    PIT_TABLE::iterator it;
    for (it = PIT.begin(); it != PIT.end(); it++) {

        sprintf(output, "Dumping PIT:\nContentName: %s\n", (*it).first.c_str());
        INTERFACES::iterator i = ((*it).second).faces.begin();
        for (; i != (((*it).second).faces.end()); i++) {
            sprintf(output + strlen(output), "src: %s\n", i->first.c_str());
            sprintf(output + strlen(output), "dst: %s\n",
                    i->second.str().c_str());
            sprintf(output + strlen(output), "time: %f\n",
                    PIT[i->first.c_str()].time.dbl());
        }
    }

    DBGPRT(EVAUX, Info, this->getFullPath()) << output;

}

/*****************************************************************************
 * pass request for content to relay
 */
void CcnCore::requestContent(CcnPacket *ccnPkt, int arrivalGateId) {

    // Enter_Method("CcnCore::requestContent");
    chunk_t chunk = std::string(ccnPkt->getName());

    pit_entry entry;

    stringstream gate_stream;
    gate_stream << arrivalGateId;
    std::string gate_string = "local:";
    gate_string.append(gate_stream.str());
    entry.faces.insert( pair<std::string, MACAddress>(gate_string, MACAddress::UNSPECIFIED_ADDRESS));
    entry.time = simTime();
    //chunk_t content = Util::getPrefixContentName(chunk);
    PIT[chunk] = entry;

    //PriorityCache
    ccnPkt->setSenderTime(simTime().dbl());
    //PriorityCache

    string router_prefix = "/";
    router_prefix += ccnfib->getRouterName();
    ccnPkt->setConsumer(router_prefix.c_str());

    sendInterest(ccnPkt);

    delete ccnPkt;
}

bool CcnCore::addRule(const char *contentName, MACAddress srcAddr,
        MACAddress dstAddr, bool isLocal) {

    return ccnfib->addL2FwdRule(contentName, srcAddr, dstAddr, isLocal,0,true);
}


int CcnCore::addFileToCache(const char* contentName, const char* localPath) {

    ccnr->addToCache(contentName, localPath);
    return 0;
}

/** Add to cache a buffer of content chunks of equal size. Return the number of chunks successfully added to CS */
int CcnCore::addToCacheFixedSizeChunks(const char *contentName, const int numChunks, const int chunkSize) {

    ccnr->addToDummyCache(contentName, numChunks, chunkSize);
    return 0;
}


void CcnCore::fromMACFace(CcnPacket *ccnPkt_, CcnContext *ccnCtx) {

    CcnPacket *ccnPkt = (CcnPacket *) ccnPkt_->dup();

    char srcMAC[6];
    char dstMAC[6];
    memset(srcMAC, 0, 6);
    memset(dstMAC, 0, 6);
    ccnCtx->getSrcAddress802().getAddressBytes(srcMAC);
    ccnCtx->getDstAddress802().getAddressBytes(dstMAC);

    chunk_t chunk = std::string(ccnPkt->getName());

    //tmp_btw = ccnPkt->getBtw();
    double int_btw = ccnPkt->getBtw();
    int type = ccnPkt->getType();

    double delay = simTime().dbl() - ccnPkt->getSenderTime();
    ccnPkt->setSumDi(ccnPkt->getSumDi() + delay);

    ccnPkt->setHops(ccnPkt->getHops() + 1);
    ccnPkt->setTSB(ccnPkt->getHops());

    switch (type) {

    case CCN_INTEREST: {

        sendInterestToListeners(ccnPkt);

        double delay = ccnPkt->getSumDi();
        if (delay > 0) {
            tot_pkt++;
            tot_delay += delay;
        }

        ccnPkt->setCapacity(ccnPkt->getCapacity() + contentStore->get_size());

        //a) Check in Content Store
        cache_response *cache_res = contentStore->lookup(ccnPkt);
        if (cache_res != NULL) {

            //cache_response *ccn_up = new cache_response;
            //memcpy(ccn_up, cache_res, sizeof(cache_response));
            //registerContent(chunk.c_str(),ccn_up->data, ccn_up->size);

            ccnPkt->setBtw(int_btw);

            ccnPkt->setType(CCN_CONTENT);
            ccnPkt->setDataFromBuffer(cache_res->data, cache_res->size);
            ccnPkt->addByteLength(cache_res->size);

            //ProbCache policy
            ccnPkt->setTSB(1);
            ccnPkt->setTSI(ccnPkt->getHops());

            //Reseting hop count.
            ccnPkt->setHops(0);

            //PriorityCache
            ccnPkt->setTotDelay(ccnPkt->getSumDi());
            ccnPkt->setSumDi(0);

            //PriorityCache
            toMACFace(dstMAC, srcMAC, ccnPkt);

            //toMACFace(CCN_CONTENT, dstMAC, srcMAC, chunk.c_str(),cache_res->data, cache_res->size);

            DBGPRT(EVAUX, Info, this->getFullPath())
                    << "Chunk found in content store.\n";

        } else if (hasCcnr) {


            //b) Look locally (only if you own a repository)
            // we are mimicking a message sent to the repository
            ccnr_response *ccnr_res = ccnr->lookup(ccnPkt);

            if (ccnr_res != NULL) {
                /**
                 * If has a Repository add the packet to PIT, get the chunk and
                 * send back to requester.
                 * */
                addPITRule(srcMAC, dstMAC, chunk);

                server_hit++;

                ccnPkt->setBtw(std::max(my_btw, int_btw));

                ccnPkt->setType(CCN_CONTENT);

                ccnPkt->setDataFromBuffer(ccnr_res->data, ccnr_res->size);
                ccnPkt->addByteLength(ccnr_res->size);

                //ProbCache policy
                ccnPkt->setTSB(1);
                ccnPkt->setTSI(ccnPkt->getHops() + 1);

                //Reseting hop count.
                ccnPkt->setHops(0);

                //PriorityCache
                ccnPkt->setTotDelay(ccnPkt->getSumDi());
                ccnPkt->setSumDi(0);

                //PriorityCache
                forwardingObject(ccnPkt);

            } else {
                //We have a repository but we don't have the chunk
                goto ADD_TO_PIT_AND_FORWARD;
            }

        } else {

            ADD_TO_PIT_AND_FORWARD:

            if (my_btw > int_btw) {
                ccnPkt->setBtw(my_btw);
            }

            //
            //c) Put the interface within the PIT (and forwading the Interest)
            //

            /****
             * Lookup is performed on PIT. If a matching Interest Message is found in the PIT
             * it means that an equivalent Interest Message has already been forwarded and is pending.
             * The arrival face of the new Interest Message is added to the list of sources
             * of unsatisfied Interests in the PIT entry and the the Interest Message is discarded.
             ****/
            PIT_TABLE::iterator pit_e = pitLookup(chunk);
            if (pit_e != PIT.end()) {
                //FIXME:So inserir na pit e na fib se não superar o limite máximo
                addPITRule(srcMAC, dstMAC, chunk);
            } else {

                addPITRule(srcMAC, dstMAC, chunk); //FIXME:So inserir na pit e na fib se não superar o limite máximo
                //FIXME:[EAMA] Implementar o encaminhamento usando a camada de estratégia.
                forwardingInterest(ccnPkt);
            }

        }
    }
        break;

    case CCN_CONTENT: {

        PIT_TABLE::iterator pit_e = pitLookup(chunk);
        if (pit_e != PIT.end()) {

            contentStore->store(ccnPkt);
            forwardingObject(ccnPkt);
        }

    }
        break;
    default:
        DBGPRT(EVAUX, Err, this->getFullPath())
                << "Unknow packet type. Only supported  (CCN_INTEREST and CCN_OBJECT)"
                << std::endl;
    }

    delete ccnPkt;
}

void CcnCore::sendInterestToListeners(CcnPacket *ccnPacket){

    CcnPacket *ccnPkt = (CcnPacket *)ccnPacket->dup();

    cGate *inGate = ccnPkt->getArrivalGate();
    InterfaceEntry *intf = inGate ?
    ccnModule->getInterfaceEntry()->getInterfaceByNetworkLayerGateIndex(inGate->getIndex()) : NULL;
    CcnContext *ccnCtx = (CcnContext *) ccnPkt->getContextPointer();
    ccnCtx->set802Info(ccnCtx->getSrcAddress802(), intf->getMacAddress());
    ccnPkt->setContextPointer((void *) ccnCtx);

    chunk_t chunk = std::string(ccnPkt->getName());

    int appId = ccnModule->getChunkListener(chunk);

    if(appId > 0){

        CcnAppMessage *appPkt = (CcnAppMessage *) ccnPkt->decapsulate();
        appPkt->setAppId(appId);
        ccnPkt->encapsulate(appPkt);
        deliverContent(ccnPkt);
    }

    delete ccnPkt;
}

//void CcnCore::forwardingObject(chunk_t chunk, void *data, int size,double delayed)
void CcnCore::forwardingObject(CcnPacket *ccnPkt) {
    chunk_t chunk = std::string(ccnPkt->getName());

    PIT_TABLE::iterator pit_entry = pitLookup(chunk);

    if (pit_entry != PIT.end()) {

        char src[6];
        memset(src, 0, 6);

        char dst[6];
        memset(dst, 0, 6);
        INTERFACES::iterator i = pit_entry->second.faces.begin();
        for (; i != pit_entry->second.faces.end(); i++) {

            if ((i->first).find("local") == 0) {

                //pit_entry->second.faces.erase("local");
                ccnPkt->setDstIface(Util::getArrivalId(i->first));
                deliverContent(ccnPkt);

                if (pit_entry->second.faces.size() == 1) {
                    return;
                } else
                    continue;
            }

            MACAddress macSrc(i->first.c_str());
            (macSrc).getAddressBytes(src);
            (i->second).getAddressBytes(dst);

            DBGPRT(EVAUX, Info, this->getFullPath())
                    << "\nPIT: Sending to face " << i->first.c_str() << "::"
                    << i->second.str().c_str() << std::endl;

            ccnPkt->setType(CCN_CONTENT);

            toMACFace(src, dst, ccnPkt);
        }

        PIT.erase(chunk);
    }
}

void CcnCore::sendInterest(CcnPacket *ccnPkt){

       chunk_t chunk = std::string(ccnPkt->getName());

       bool isintable = ccnfib->isInTable(chunk);
       bool sendToDefaultGateway = false;
       ForwardingTable::FIB_TABLE::iterator fib_entry;

       if(!isintable){
           DBGPRT(EVAUX, Err, this->getFullPath())
              << "There's no FIB Entry... Dropping the packet " << chunk
              << std::endl;

           if(ccnfib->isInTable(DEFAULT_PREFIX)){
               fib_entry  = ccnfib->getDefaultGateway();
               sendToDefaultGateway = true;
           }else
               return;
       }

       if(sendToDefaultGateway == false)
           fib_entry = ccnfib->lookup(chunk);

       //ccnfib->printForwardingTable();
       if (fib_entry != ccnfib->getTable().end()) {
           char src[6];
           memset(src, 0, 6);

           //Get source from FIB
           (fib_entry->second.src).getAddressBytes(src);

           char dst[6];
           memset(dst, 0, 6);

           //Get destination from FIB
           (fib_entry->second.dst).getAddressBytes(dst);
           //(MACAddress::BROADCAST_ADDRESS).getAddressBytes(dst);

           ccnPkt->setType(CCN_INTEREST);
           toMACFace(src, dst, ccnPkt);
       }
}

//void CcnCore::forwardingInterest(chunk_t chunk, void *data, int size) {
void CcnCore::forwardingInterest(CcnPacket *ccnPkt) {

    chunk_t chunk = std::string(ccnPkt->getName());
    ForwardingTable::FIB_TABLE::iterator fib_entry = ccnfib->lookup(chunk);


    if(ccnfib->isInTable(chunk)){

        if (fib_entry != ccnfib->getTable().end()) {
            char src[6];
            memset(src, 0, 6);

            //Get source from FIB

            (fib_entry->second.src).getAddressBytes(src);

            char dst[6];
            memset(dst, 0, 6);

            //Get destination from FIB
            (fib_entry->second.dst).getAddressBytes(dst);

            ccnPkt->setType(CCN_INTEREST);

            if(fib_entry->second.isLocal == true){
                deliverContent(ccnPkt);
                return;

            }else if(fib_entry->second.dst == MACAddress::BROADCAST_ADDRESS){

                cGate *inGate = ccnPkt->getArrivalGate();
                InterfaceEntry *intf = inGate ?
                 ccnModule->getInterfaceEntry()->getInterfaceByNetworkLayerGateIndex(inGate->getIndex()) : NULL;
                //cerr << "Ccn::fromLowerLayer MACAddress: " << intf->getMacAddress() << endl;

                CcnContext *ccnCtx = (CcnContext *) ccnPkt->getContextPointer();
                ccnCtx->set802Info(ccnCtx->getSrcAddress802(), intf->getMacAddress());
                ccnPkt->setContextPointer((void *) ccnCtx);

                deliverContent(ccnPkt);
                return;
            }

            //for fib stale
            fib_entry->second.time = simTime();

            toMACFace(src, dst, ccnPkt);
        }

    } else {
        DBGPRT(EVAUX, Err, this->getFullPath())
                << "There's no FIB Entry... Dropping the packet " << chunk
                << std::endl;
    }

}

bool CcnCore::isThisDestination(MACAddress dst) {

    for (int i = 0; i < ccnModule->numMacIds; i++) {

        if ((ccnModule->macIds[i]) == dst) {
            return true;
        }
    }
    return false;
}

//FIXME:[EAMA] Criar uma rotina para deletar as entradas da pit que estão obsoletas. **/
void CcnCore::addPITRule(const char *srcAddr, const char *dstAddr,
        chunk_t chunk) {

    char srcAddrStr[18];
    char dstAddrStr[18];

    memset(srcAddrStr + 17, '\0', sizeof(char));
    memset(dstAddrStr + 17, '\0', sizeof(char));

    sprintf(srcAddrStr, "%2.2X:%2.2X:%2.2X:%2.2X:%2.2X:%2.2X",
            (unsigned char) srcAddr[0], (unsigned char) srcAddr[1],
            (unsigned char) srcAddr[2], (unsigned char) srcAddr[3],
            (unsigned char) srcAddr[4], (unsigned char) srcAddr[5]);
    sprintf(dstAddrStr, "%2.2X:%2.2X:%2.2X:%2.2X:%2.2X:%2.2X",
            (unsigned char) dstAddr[0], (unsigned char) dstAddr[1],
            (unsigned char) dstAddr[2], (unsigned char) dstAddr[3],
            (unsigned char) dstAddr[4], (unsigned char) dstAddr[5]);

    if (PIT.size() > PIT_MAX_SIZE && !pitTimeoutMsg->isScheduled()) {
        scheduleAt(simTime() + timeoutPIT, pitTimeoutMsg);
    }

    if (!statistic->isScheduled()) {
        scheduleAt(simTime() + STAT_INTERVAL, statistic);
    }

    MACAddress macSrcAddr(dstAddrStr);
    MACAddress macDstAddr(srcAddrStr);

//    Não adiciona na pit se for broadcast e for um pacote ponto a ponto.
//    verificar se no chunk possui o nome desse nó.

    string routerName = ccnfib->getRouterName();
    std::size_t found = chunk.find(routerName);
    /* If a packet is broadcasted, there is no way to put a single path back to the sender.*/
    if(macSrcAddr.isBroadcast() || found!=std::string::npos)
        return;

    DBGPRT(EVAUX, Info, this->getFullPath()) << "Adding PIT Entry:\n"
               << "Mac Src: " << macSrcAddr.str().c_str() << "\nMac Dst: "
               << macDstAddr.str().c_str() << std::endl;

    /**In the PIT, source becomes destination and destination becomes source. **/
    std::string macSrc = macSrcAddr.str();

    PIT_TABLE::iterator pit_e = pitLookup(chunk);
    if (pit_e == PIT.end()) {

        pit_entry entry;
        entry.faces.insert(pair<std::string, MACAddress>(macSrc, macDstAddr));
        entry.time = simTime();
        PIT[chunk] = entry;

    } else {

        //The PIT entry already exist. So add the new face.
        INTERFACES::iterator i = pit_e->second.faces.begin();
        bool exists = false;
        for (; i != pit_e->second.faces.end(); i++) {

            if (i->first == macSrc) {
                //Already exists so update the time,because the Interest is still needed.
                pit_e->second.time = simTime();
                exists = true;
            }
        }
        if (!exists) {
            pit_e->second.faces.insert(
                    pair<std::string, MACAddress>(macSrc, macDstAddr));
        }
    }
}

//FIXME:[EAMA] Verificar os lixos que precisam ser removidos.
CcnCore::~CcnCore() {

    cancelAndDelete(statistic);
    cancelAndDelete(pitTimeoutMsg);
    cancelAndDelete(fibTimeoutMsg);
}

bool CcnCore::deliverContent(CcnPacket* ccnPkt) {

    int buffSize = ccnPkt->getByteArray().getDataArraySize();
    char *dataBuff = new char[buffSize];
    int dataLen = ccnPkt->copyDataToBuffer(dataBuff, buffSize);
    string name = ccnPkt->getName();
    CcnAppMessage *appPkt = (CcnAppMessage *) ccnPkt->decapsulate();

    if(appPkt == 0){
        cout<< "CcnCore::deliverContent CcnAppMessage is null name: " << name << endl;
        return false;
    }

    if(ccnPkt->getType() == CCN_CONTENT){
        appPkt->setType(CCN_APP_CONTENT);
        appPkt->setName("ContentObject");
    }else if(ccnPkt->getType() == CCN_INTEREST){
        appPkt->setType(CCN_APP_INTEREST);
        appPkt->setName("Interest");
    }

//    new CcnAppMessage(ccnPkt->getName());
    CcnAppMessage *c = (CcnAppMessage *) ccnPkt->decapsulate();
     if ( c != 0 ) {
         int appid= c->getAppId();
         appPkt->setAppId(appid);
         int AppPort = this->ccnModule->getAppGate(appid );
         ccnPkt->setDstIface(AppPort);
         appPkt->encapsulate(c);
     }

    CcnContext *ccnCtx = (CcnContext *) ccnPkt->getContextPointer();

    Ieee802Ctrl* macCtx = new Ieee802Ctrl();
    macCtx->setSrc(ccnCtx->getSrcAddress802());
    macCtx->setDest(ccnCtx->getDstAddress802());
    appPkt->setConsumer(ccnPkt->getConsumer());
    appPkt->setControlInfo(macCtx);
   // appPkt->encapsulate(ccnPkt->decapsulate());
    appPkt->setDstGate(ccnPkt->getDstIface());
    appPkt->setHops(ccnPkt->getHops());
    appPkt->setType(CCN_APP_CONTENT);
    appPkt->setAction(CONTENT_DELIVER);
    appPkt->setContentName(ccnPkt->getName());
    appPkt->setDataFromBuffer(dataBuff, dataLen);
    appPkt->addByteLength(dataLen);
    appPkt->setChunkSize(ccnPkt->getChunkSize());
    appPkt->setArrivalTime(simTime());
    ccnModule->toUpperLayer(appPkt);
    return true;
}

bool CcnCore::toMACFace(const char *srcAddr, const char *dstAddr,
        CcnPacket *ccnPkt) {

    char srcAddrStr[18];
    char dstAddrStr[18];

    if (!dstAddr || !srcAddr) {
        DBGPRT(EVAUX, Err, this->getFullPath())
                << "Outgoing eth pkt dropped (endpoint information inconsistency)!"
                << std::endl;
        return false;
    }

    CcnContext *ctx = new CcnContext(AF_PACKET);
    ctx->set802Info(srcAddr, dstAddr);

    memset(srcAddrStr + 17, '\0', sizeof(char));
    memset(dstAddrStr + 17, '\0', sizeof(char));
    sprintf(srcAddrStr, "%2.2X:%2.2X:%2.2X:%2.2X:%2.2X:%2.2X",
            (unsigned char) srcAddr[0], (unsigned char) srcAddr[1],
            (unsigned char) srcAddr[2], (unsigned char) srcAddr[3],
            (unsigned char) srcAddr[4], (unsigned char) srcAddr[5]);
    sprintf(dstAddrStr, "%2.2X:%2.2X:%2.2X:%2.2X:%2.2X:%2.2X",
            (unsigned char) dstAddr[0], (unsigned char) dstAddr[1],
            (unsigned char) dstAddr[2], (unsigned char) dstAddr[3],
            (unsigned char) dstAddr[4], (unsigned char) dstAddr[5]);
    std::string pktInfo = " [" + std::string(srcAddrStr) + "] --ccn--> ["
            + std::string(dstAddrStr) + "] ";
    std::string txInfo = " [" + ctx->getSrcAddress802().str() + "] --ccn--> ["
            + ctx->getDstAddress802().str() + "] ";

    CcnPacket *pkt = new CcnPacket();
    pkt->setName(ccnPkt->getName());
    pkt->setType(ccnPkt->getType());
    pkt->setHops(ccnPkt->getHops());
    pkt->setKind(PROT_CCN);
    pkt->setContextPointer(ctx);
    pkt->setChunkSize(ccnPkt->getChunkSize());

    //Caching Policies
    pkt->setBtw(ccnPkt->getBtw()); //Centrality Based

    //ProbCache {
    pkt->setCapacity(ccnPkt->getCapacity());
    pkt->setTSB(ccnPkt->getHops());
    pkt->setTSI(ccnPkt->getTSI());
    //ProbCache }

    //PriorityCache {
    pkt->setSumDi(ccnPkt->getSumDi());
    pkt->setTotDelay(ccnPkt->getTotDelay());
    pkt->setSenderTime(simTime().dbl());
    int pr_ = ccnPkt->getPriority();
    pkt->setPriority(pr_);
    //PriorityCache }

    //RankCache
    pkt->setRank(ccnPkt->getRank());
    //RankCache

    int buffSize = ccnPkt->getByteArray().getDataArraySize();
    char *dataBuff = new char[buffSize];
    int dataLen = ccnPkt->copyDataToBuffer(dataBuff, buffSize);

    pkt->setDataFromBuffer(dataBuff, dataLen);
    pkt->addByteLength(dataLen);

    DBGPRT(EVAUX, Info, this->getFullPath()) << "CCN Core to-send data : "
            << pktInfo.c_str() << "\nCCN Preparing Transmission: "
            << txInfo.c_str() << std::endl;

    pkt->encapsulate(ccnPkt->decapsulate());

    //Aggregated Content Name.

//    if(ccnPkt->getType() == CCN_INTEREST){
//        string router_name = "/";
//        router_name += ccnfib->getRouterName();
//
//        string acn = router_name + ccnPkt->getAggregateCN();
//        pkt->setAggregateCN(acn.c_str());
//    }

    pkt->setConsumer(ccnPkt->getConsumer());
    ccnModule->toLowerLayer(pkt);

    return true;
}

void CcnCore::finish() {

    if (server_hit > 0)
        recordScalar("server_hit", server_hit);

    if (tot_delay > 0) {
        char name[32];
        sprintf(name, "int_delay_%s",
                getParentModule()->getParentModule()->getName());
        recordScalar(name, tot_delay / tot_pkt);
    }

}
