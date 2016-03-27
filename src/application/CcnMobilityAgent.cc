//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "CcnMobilityAgent.h"
#include "commons.h"
#include "Util.h"
#include "Ieee802Ctrl.h"

Define_Module (CcnMobilityAgent);

CcnMobilityAgent::CcnMobilityAgent() {

    ospfnrouter = 0;
    appId = CCN_MOBILITY_AGENT;
    ageTableTimer = new cMessage("AgeTableTimer");
    ageTableTimer->setKind(AGE_MSG);
}

CcnMobilityAgent::~CcnMobilityAgent() {

   if (ageTableTimer != 0)
       cancelAndDelete(ageTableTimer);
}

void CcnMobilityAgent::registerMyselfInCcnLayer(){

    if(gateSize("ccnOut") == 0)
    {
        error("This application cannot be unconnected");
    }

    Ccn* ccn = getModuleFromPar<Ccn>(par("ccndModule"), this);
    cGate *mygate = gate("ccnIn");
    ccn->registerApp(appId,mygate);
    ccn->registerChunkListener("*",appId);
}

/**
 * Initialization and termination of the module
 */
void CcnMobilityAgent::initialize(int stage) {

    //ft = ForwardingTableAccess().get();


    if(stage == 1){
//        NotificationBoard* nb = NotificationBoardAccess().get();
//        nb->subscribe(this, NF_L2_ASSOCIATED_NEWAP);
        cModule *routingModule = getContainingNode(this);
        routingModule->subscribe(NF_L2_ASSOCIATED_NEWAP,this);

    }else if(stage == 4){
        registerMyselfInCcnLayer();
        scheduleAt(simTime() + AGETIMER, ageTableTimer);

    }else if(stage == 5){
        OSPFNRouting* r = getModuleFromPar<OSPFNRouting>(par("ospfn"), this);

          ospfnrouter = r->getRouter();
    }

//    WATCH_MAP(sessionsMap);
}

void CcnMobilityAgent::handleMessage(cMessage *msg) {


    if(msg->isSelfMessage() && msg->getKind() == AGE_MSG){
        handleSelfMessage(msg);
    }
    else{
        CcnAppMessage *appmsg = check_and_cast<CcnAppMessage *>(msg);
        if(appmsg){
            cMessage *insideMsg = appmsg->getEncapsulatedPacket();
            MobilityAppMessage *mobMsg = dynamic_cast<MobilityAppMessage *>(insideMsg);
            if(mobMsg){
                processMobilityMessage(appmsg,mobMsg);
            }else
                processPacket(appmsg);

           // delete mobMsg;
          //  if (insideMsg != 0)
          //      delete insideMsg;
//            if(mobMsg){
//                delete mobMsg;
//                processMobilityMessage(appmsg,mobMsg);
//                delete mobMsg;
  //          }
//            else
//                processPacket(appmsg);
        }
        delete msg;
   }


}

void CcnMobilityAgent::handleSelfMessage(cMessage *msg){

    if(ageTableTimer == msg){
        ageTable();
    }else
        delete msg;
}

void CcnMobilityAgent::ageTable(){

    if(sessionsMap.size() == 0)
        return;

    ACTIVE_MAP::iterator it;


    for(it = sessionsMap.begin(); it != sessionsMap.end();){
        if( simTime() - it->second.time > EXPIRED_TIME_LIMIT){
            sessionsMap.erase(it++);
        }else
            it++;
        if(sessionsMap.size() == 0)
            break;
    }

    scheduleAt(simTime() + AGETIMER, ageTableTimer);
}

void CcnMobilityAgent::processMobilityMessage(CcnAppMessage* appmsg, MobilityAppMessage *mobmsg){

    if(ospfnrouter == 0)
        opp_error("pointer to ospfn router is null");
    Ieee802Ctrl *macCtx = check_and_cast<Ieee802Ctrl *>(appmsg->removeControlInfo());
    MACAddress srcAddr = macCtx->getDest();
    MACAddress dstAddr = macCtx->getSrc();

    //PRINT_ERR << "Module: "<< ft->getRouterName() << " begin {\n";
    int contentArraySize = mobmsg->getContentsArraySize();
    chunk_t contentName;
    std::vector<chunk_t> retContentVector;
    bool updateTable = false;

    for(int k = 0; k < contentArraySize; k++){
        contentName = mobmsg->getContents(k);
        retContentVector.push_back(contentName);
//        PRINT_ERR << " c:" << contentName << " src: " << srcAddr << " dst: " << dstAddr << endl;
       // ft->addOrUpdateL2FwdRule(contentName.c_str(), srcAddr, dstAddr, false,1,true);
        ospfnrouter->addOrUpdatePrefixTableEntry(contentName.c_str(), dstAddr, srcAddr, false,1,true);
        updateTable = true;
    }

    if(updateTable)
        ospfnrouter->rebuildForwardingTable();
//    PRINT_ERR << "} end;\n";

    //Forwarding VirtualInterest if this module is not the destination of virtual interest
//    if(ft->getRouterNamePrefix() != appmsg->getContentName())
//        sendVirtualInterest(appmsg->getContentName(),retContentVector);
}

void CcnMobilityAgent::processPacket(CcnAppMessage *pkt){

    Ieee802Ctrl *macCtx = check_and_cast<Ieee802Ctrl *>(pkt->removeControlInfo());
    //Broadcast messages usually not used for communication.
    if( macCtx->getDest() == MACAddress::BROADCAST_ADDRESS)
        return;

    chunk_t senderName = pkt->getConsumer();
    chunk_t contentName = Util::getPrefixContentName(pkt->getContentName());

    ACTIVE_MAP::iterator it;
    it = sessionsMap.find(senderName);

    if (it != sessionsMap.end()){
           bool exist = false;
           for(uint i = 0; i < it->second.contents.size(); i++){
               if(it->second.contents[i] == contentName){
                    it->second.time = simTime().dbl();
                    exist = true;
                    break;
               }
           }
           if(!exist)
               it->second.contents.push_back(contentName);
  }else{
        ActiveSession session;
        session.name = senderName;
        session.time = simTime().dbl();
        session.contents.push_back(contentName);
        sessionsMap[senderName] = session;
    }
}

void CcnMobilityAgent::notifyConsumers(){

    if(sessionsMap.size() == 0)
        return;

    ACTIVE_MAP::iterator it;
    for(it = sessionsMap.begin(); it != sessionsMap.end(); it++){
        sendVirtualInterest(it->first, it->second.contents);
    }
}

void CcnMobilityAgent::sendVirtualInterest(chunk_t name, std::vector<chunk_t>& contents){

    CcnAppMessage * ccn_i = new CcnAppMessage("Interest");
    ccn_i->setType(CCN_APP_INTEREST);
    ccn_i->setSeqNr(1);
    ccn_i->setNumChunks(1);
    ccn_i->setChunkSize(normal(500, 250));
    ccn_i->setAppId(appId);
    ccn_i->setContentName(name.c_str());

    MobilityAppMessage *mobMsg = new MobilityAppMessage("VirtualInterest");
    int asize = contents.size();
    mobMsg->setContentsArraySize(asize);
    for(int k = 0; k < asize ; k++){
        mobMsg->setContents(k,contents[k].c_str());
    }
    ccn_i->encapsulate(mobMsg);
    send(ccn_i, "ccnOut");
}

//void CcnMobilityAgent::receiveChangeNotification(int category, const cObject *details) {
//
//    if (simulation.getContextType() == CTX_INITIALIZE)
//        return;  // ignore notifications during initialize
//
//    Enter_Method_Silent();
//    printNotificationBanner(category, details);
//
//    if (category == NF_L2_ASSOCIATED_NEWAP) {
//
//        std::cerr << "simtime: handover: " << simTime() << endl;
//        notifyConsumers();
////        isMobileHost = true;
////        //In the new network, the forwarding table is not necessary.
////
////        //the neighborhood table either.
////        neighborhood->clear();
////        prefixTable.clear();
////        rebuildForwardingTable();
////
////        scheduleEvent(FLOOD_HELLO_PACKET, simTime() + 0.1);
//
//    }
//}


void CcnMobilityAgent::receiveSignal(cComponent *source, int signalID,  cObject *obj) {
    Enter_Method_Silent();
    printNotificationBanner(signalID, obj);

    if (signalID == NF_L2_ASSOCIATED_NEWAP) {

        std::cerr << "CcnMobilityAgent::simtime: handover: " << simTime() << endl;
        notifyConsumers();
        std::cerr << "CcnMobilityAgent::simtime: handover: " << simTime() << endl;
        notifyConsumers();
        //        isMobileHost = true;
        //        //In the new network, the forwarding table is not necessary.
        //
        //        //the neighborhood table either.
        //        neighborhood->clear();
        //        prefixTable.clear();
        //        rebuildForwardingTable();
        //
        //        scheduleEvent(FLOOD_HELLO_PACKET, simTime() + 0.1);
    }
}
