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



//#include "IPv4Datagram_m.h"
#include "OSPFNMessageHandler.h"
//#include "OSPFArea.h"
#include "OSPFNNeighborState.h"
#include "OSPFNNeighborStateDown.h"

#include "OSPFNNeighbor.h"

//
//// FIXME!!! Should come from a global unique number generator module.
unsigned long OSPFN::Neighbor::ddSequenceNumberInitSeed = 0;
//
OSPFN::Neighbor::Neighbor(std::string neighbor) :
    updateRetransmissionTimerActive(false),
    requestRetransmissionTimerActive(false),
    firstAdjacencyInited(false),
    ddSequenceNumber(0),
    neighborID(neighbor)//,
//    neighborPriority(0),
//    neighborAddress(OSPFN::NULL_IPV4ADDRESS),
//    neighborsDesignatedRouter(OSPFN::NULL_DESIGNATEDROUTERID),
//    neighborsBackupDesignatedRouter(OSPFN::NULL_DESIGNATEDROUTERID),
//    designatedRoutersSetUp(false),
    ,neighborsRouterDeadInterval(40)
   , lastTransmittedDDPacket(NULL)
{
   // memset(&lastReceivedDDPacket, 0, sizeof(OSPFN::Neighbor::DDPacketID));
    // setting only I and M bits is invalid -> good initializer
//    lastReceivedDDPacket.ddOptions.I_Init = true;
//    lastReceivedDDPacket.ddOptions.M_More = true;
    inactivityTimer = new OSPFNTimer();
    inactivityTimer->setTimerKind(NEIGHBOR_INACTIVITY_TIMER);
    inactivityTimer->setContextPointer(this);
    inactivityTimer->setName("OSPFN::Neighbor::NeighborInactivityTimer");
    pollTimer = new OSPFNTimer();
    pollTimer->setTimerKind(NEIGHBOR_POLL_TIMER);
    pollTimer->setContextPointer(this);
    pollTimer->setName("OSPFN::Neighbor::NeighborPollTimer");
    ddRetransmissionTimer = new OSPFNTimer();
    ddRetransmissionTimer->setTimerKind(NEIGHBOR_DD_RETRANSMISSION_TIMER);
    ddRetransmissionTimer->setContextPointer(this);
    ddRetransmissionTimer->setName("OSPFN::Neighbor::NeighborDDRetransmissionTimer");
    updateRetransmissionTimer = new OSPFNTimer();
    updateRetransmissionTimer->setTimerKind(NEIGHBOR_UPDATE_RETRANSMISSION_TIMER);
    updateRetransmissionTimer->setContextPointer(this);
    updateRetransmissionTimer->setName("OSPFN::Neighbor::Neighbor::NeighborUpdateRetransmissionTimer");
    requestRetransmissionTimer = new OSPFNTimer();
    requestRetransmissionTimer->setTimerKind(NEIGHBOR_REQUEST_RETRANSMISSION_TIMER);
    requestRetransmissionTimer->setContextPointer(this);
    requestRetransmissionTimer->setName("OSPFN::Neighbor::NeighborRequestRetransmissionTimer");
    state = new OSPFN::NeighborStateDown();
    previousState = NULL;
}
//
OSPFN::Neighbor::~Neighbor()
{
    reset();
    OSPFN::MessageHandler * messageHandler = parentInterface->getRouter()->getMessageHandler();
    messageHandler->clearTimer(inactivityTimer);
    messageHandler->clearTimer(pollTimer);
    delete inactivityTimer;
    delete pollTimer;
    delete ddRetransmissionTimer;
    delete updateRetransmissionTimer;
    delete requestRetransmissionTimer;
    if (previousState != NULL) {
        delete previousState;
    }
    delete state;
}
//
void OSPFN::Neighbor::changeState(NeighborState* newState, NeighborState* currentState)
{
    if (previousState != NULL) {
        delete previousState;
    }
    state = newState;
    previousState = currentState;
}
//
void OSPFN::Neighbor::processEvent(OSPFN::NeighborEventType event)
{
    state->processEvent(this, event);
}
//
void OSPFN::Neighbor::reset()
{
//    for (std::list<OSPFLSA*>::iterator retIt = linkStateRetransmissionList.begin();
//         retIt != linkStateRetransmissionList.end();
//         retIt++)
//    {
//        delete (*retIt);
//    }
//    linkStateRetransmissionList.clear();
//
//    std::list<OSPFLSAHeader*>::iterator it;
//    for (it = databaseSummaryList.begin(); it != databaseSummaryList.end(); it++) {
//        delete (*it);
//    }
//    databaseSummaryList.clear();
//    for (it = linkStateRequestList.begin(); it != linkStateRequestList.end(); it++)
//    {
//        delete (*it);
//    }
//    linkStateRequestList.clear();
//
    parentInterface->getRouter()->getMessageHandler()->clearTimer(ddRetransmissionTimer);
    clearUpdateRetransmissionTimer();
    clearRequestRetransmissionTimer();

    if (lastTransmittedDDPacket != NULL) {
        delete lastTransmittedDDPacket;
        lastTransmittedDDPacket = NULL;
    }
}
//
void OSPFN::Neighbor::initFirstAdjacency()
{
    ddSequenceNumber = getUniqueULong();
    firstAdjacencyInited = true;
}
//
unsigned long OSPFN::Neighbor::getUniqueULong()
{
    // FIXME!!! Should come from a global unique number generator module.
    return (ddSequenceNumberInitSeed++);
}
//
OSPFN::NeighborStateType OSPFN::Neighbor::getState() const
{
    return state->getState();
}

const char* OSPFN::Neighbor::getStateString(OSPFN::NeighborStateType stateType)
{
    switch (stateType) {
        case DOWN_STATE:           return "Down";
        case ATTEMPT_STATE:        return "Attempt";
        case INIT_STATE:           return "Init";
        case TWOWAY_STATE:         return "TwoWay";
        case EXCHANGE_START_STATE: return "ExchangeStart";
        case EXCHANGE_STATE:       return "Exchange";
        case LOADING_STATE:        return "Loading";
        case FULL_STATE:           return "Full";
        default:                   ASSERT(false); break;
    }
    return "";
}

//bool OSPFN::Neighbor::isLinkStateRequestListEmpty(){
//
//    std::vector<adv_prefix> prefix_vec = parentInterface->getRouter()->getPrefixesToAdvertise();
//    int size = prefix_vec.size();
//    if(size > 0)
//        return false;
//    else
//        return true;
//
//    //parentInterface->isLinkStateRequestListEmpty();
//}


bool OSPFN::Neighbor::retransmitDatabaseDescriptionPacket()
{
    opp_error("OSPFN::Neighbor::retransmitDatabaseDescriptionPacket()");
//    if (lastTransmittedDDPacket != NULL) {
//        OSPFNDatabaseDescriptionPacket* ddPacket = new OSPFNDatabaseDescriptionPacket(*lastTransmittedDDPacket);
//        OSPFN::MessageHandler* messageHandler = parentInterface->getRouter()->getMessageHandler();
//        int ttl = (parentInterface->getType() == OSPFN::Interface::VIRTUAL) ? VIRTUAL_LINK_TTL : 1;
//
//        if (parentInterface->getType() == OSPFN::Interface::POINTTOPOINT) {
//            messageHandler->sendPacket(ddPacket, IPv4Address::ALL_OSPF_ROUTERS_MCAST, parentInterface->getIfIndex(), ttl);
//        } else {
//            messageHandler->sendPacket(ddPacket, neighborAddress, parentInterface->getIfIndex(), ttl);
//        }
//
//        return true;
//    } else {
//        return false;
//    }
}
//
//void OSPFN::Neighbor::createDatabaseSummary()
//{
//    OSPFN::Area* area = parentInterface->getArea();
//    unsigned long routerLSACount = area->getRouterLSACount();
//
//    /* Note: OSPF specification says:
//     * "LSAs whose age is equal to MaxAge are instead added to the neighbor's
//     *  Link state retransmission list."
//     * But this task has been already done during the aging of the database. (???)
//     * So we'll skip this.
//     */
//    for (unsigned long i = 0; i < routerLSACount; i++) {
//        if (area->getRouterLSA(i)->getHeader().getLsAge() < MAX_AGE) {
//            OSPFLSAHeader* routerLSA = new OSPFLSAHeader(area->getRouterLSA(i)->getHeader());
//            databaseSummaryList.push_back(routerLSA);
//        }
//    }
//
//    unsigned long networkLSACount = area->getNetworkLSACount();
//    for (unsigned long j = 0; j < networkLSACount; j++) {
//        if (area->getNetworkLSA(j)->getHeader().getLsAge() < MAX_AGE) {
//            OSPFLSAHeader* networkLSA = new OSPFLSAHeader(area->getNetworkLSA(j)->getHeader());
//            databaseSummaryList.push_back(networkLSA);
//        }
//    }
//
//    unsigned long summaryLSACount = area->getSummaryLSACount();
//    for (unsigned long k = 0; k < summaryLSACount; k++) {
//        if (area->getSummaryLSA(k)->getHeader().getLsAge() < MAX_AGE) {
//            OSPFLSAHeader* summaryLSA = new OSPFLSAHeader(area->getSummaryLSA(k)->getHeader());
//            databaseSummaryList.push_back(summaryLSA);
//        }
//    }
//
//    if ((parentInterface->getType() != OSPFN::Interface::VIRTUAL) &&
//        (area->getExternalRoutingCapability()))
//    {
//        OSPFN::Router* router = area->getRouter();
//        unsigned long asExternalLSACount = router->getASExternalLSACount();
//
//        for (unsigned long m = 0; m < asExternalLSACount; m++) {
//            if (router->getASExternalLSA(m)->getHeader().getLsAge() < MAX_AGE) {
//                OSPFLSAHeader* asExternalLSA = new OSPFLSAHeader(router->getASExternalLSA(m)->getHeader());
//                databaseSummaryList.push_back(asExternalLSA);
//            }
//        }
//    }
//}
//

void OSPFN::Neighbor::sendDatabaseDescriptionPacket()
{
    OSPFNDatabaseDescriptionPacket* ddPacket = new OSPFNDatabaseDescriptionPacket("DatabaseDescription");

    ddPacket->setType(OSPFN_DATABASE_DESCRIPTION_PACKET);
    ddPacket->setDdSequenceNumber(ddSequenceNumber);
    //OSPFN::MessageHandler* messageHandler = parentInterface->getRouter()->getMessageHandler();

    chunk_t destination = getNeighborID();
    ddPacket->setDestination(destination.c_str());
    ddPacket->setRouterID(parentInterface->getRouter()->getRouterID().c_str());

    std::vector<adv_prefix> prefix_vec = parentInterface->getRouter()->getPrefixesToAdvertise();
        int size = prefix_vec.size();
        if(size > 0){
            ddPacket->setLsaHeadersArraySize(size);
            for(int i = 0; i < size; i++){
                ddPacket->setLsaHeaders(i,prefix_vec[i].prefix.c_str());
            }
        }

    parentInterface->sendOSPFNPacket(ddPacket,destination );

    //messageHandler->sendPacket(ddPacket, getNeighborID(), parentInterface->getIfIndex(), ttl);
//    }

    if (lastTransmittedDDPacket != NULL) {
        delete lastTransmittedDDPacket;
    }
    lastTransmittedDDPacket = new OSPFNDatabaseDescriptionPacket(*ddPacket);
}

void OSPFN::Neighbor::sendLinkStateRequestPacket(std::vector<chunk_t> desired_prefixs){

    OSPFNLinkStateRequestPacket* requestPacket = new OSPFNLinkStateRequestPacket();
    requestPacket->setType(OSPFN_LINKSTATE_REQUEST_PACKET);

    int size = desired_prefixs.size();
    if(size > 0){
        requestPacket->setLSAsArraySize(size);

        for(int i = 0; i < size; i++){
            requestPacket->setLSAs(i,desired_prefixs[i].c_str());
           // PRINT_ERR << "PREFIX: " <<prefix_vec[i].prefix.c_str() << " hops: " << prefix_vec[i].hops << ENDL ;
        }
    }

    chunk_t destination = getNeighborID();
    requestPacket->setDestination(destination.c_str());
    requestPacket->setRouterID(parentInterface->getRouter()->getRouterID().c_str());

    parentInterface->sendOSPFNPacket(requestPacket,destination);
    //messageHandler->sendPacket(requestPacket->dup(), neighborAddress, parentInterface->getIfIndex(), ttl);
}

//void OSPFN::Neighbor::sendLinkStateRequestPacket(std::vector<chunk_t> desired_prefixs){
//
//    OSPFNLinkStateRequestPacket* requestPacket = new OSPFNLinkStateRequestPacket();
//    requestPacket->setType(OSPFN_LINKSTATE_REQUEST_PACKET);
//
//    std::vector<adv_prefix> prefix_vec = parentInterface->getRouter()->getPrefixesToAdvertise();
//    int size = prefix_vec.size();
//    if(size > 0){
//        requestPacket->setLSAsArraySize(size);
//        requestPacket->setHopsArraySize(size);
//
//        for(int i = 0; i < size; i++){
//            requestPacket->setLSAs(i,prefix_vec[i].prefix.c_str());
//            requestPacket->setHops(i,prefix_vec[i].hops);
//           // PRINT_ERR << "PREFIX: " <<prefix_vec[i].prefix.c_str() << " hops: " << prefix_vec[i].hops << ENDL ;
//        }
//    }
//
//    chunk_t destination = getNeighborID();
//    requestPacket->setDestination(destination.c_str());
//    requestPacket->setRouterID(parentInterface->getRouter()->getRouterID().c_str());
//
//    parentInterface->sendOSPFNPacket(requestPacket,destination);
//    //messageHandler->sendPacket(requestPacket->dup(), neighborAddress, parentInterface->getIfIndex(), ttl);
//}

//void OSPFN::Neighbor::sendLinkStateRequestPacket()
//{
//    OSPFLinkStateRequestPacket* requestPacket = new OSPFLinkStateRequestPacket();
//
//    requestPacket->setType(LINKSTATE_REQUEST_PACKET);
//    requestPacket->setRouterID(IPv4Address(parentInterface->getArea()->getRouter()->getRouterID()));
//    requestPacket->setAreaID(IPv4Address(parentInterface->getArea()->getAreaID()));
//    requestPacket->setAuthenticationType(parentInterface->getAuthenticationType());
//    OSPFN::AuthenticationKeyType authKey = parentInterface->getAuthenticationKey();
//    for (int i = 0; i < 8; i++) {
//        requestPacket->setAuthentication(i, authKey.bytes[i]);
//    }
//
//
//    long maxPacketSize = (((IP_MAX_HEADER_BYTES + OSPF_HEADER_LENGTH + OSPF_REQUEST_LENGTH) > parentInterface->getMTU()) ?
//                          IPV4_DATAGRAM_LENGTH :
//                          parentInterface->getMTU()) - IP_MAX_HEADER_BYTES;
//    long packetSize = OSPF_HEADER_LENGTH;
//
//    if (linkStateRequestList.empty()) {
//        requestPacket->setRequestsArraySize(0);
//    } else {
//        std::list<OSPFLSAHeader*>::iterator it = linkStateRequestList.begin();
//
//        while ((it != linkStateRequestList.end()) && (packetSize <= (maxPacketSize - OSPF_REQUEST_LENGTH))) {
//            unsigned long requestCount = requestPacket->getRequestsArraySize();
//            OSPFLSAHeader* requestHeader = (*it);
//            LSARequest request;
//
//            request.lsType = requestHeader->getLsType();
//            request.linkStateID = requestHeader->getLinkStateID();
//            request.advertisingRouter = requestHeader->getAdvertisingRouter();
//
//            requestPacket->setRequestsArraySize(requestCount + 1);
//            requestPacket->setRequests(requestCount, request);
//
//            packetSize += OSPF_REQUEST_LENGTH;
//            it++;
//        }
//    }
//
//    requestPacket->setByteLength(packetSize);
//
//    OSPFN::MessageHandler* messageHandler = parentInterface->getArea()->getRouter()->getMessageHandler();
//    int ttl = (parentInterface->getType() == OSPFN::Interface::VIRTUAL) ? VIRTUAL_LINK_TTL : 1;
//    if (parentInterface->getType() == OSPFN::Interface::POINTTOPOINT) {
//        messageHandler->sendPacket(requestPacket, IPv4Address::ALL_OSPF_ROUTERS_MCAST, parentInterface->getIfIndex(), ttl);
//    } else {
//        messageHandler->sendPacket(requestPacket, neighborAddress, parentInterface->getIfIndex(), ttl);
//    }
//}
//
bool OSPFN::Neighbor::needAdjacency()
{
    return true;
//    OSPFN::Interface::OSPFInterfaceType interfaceType = parentInterface->getType();
//    OSPFN::RouterID routerID = parentInterface->getArea()->getRouter()->getRouterID();
//    OSPFN::DesignatedRouterID dRouter = parentInterface->getDesignatedRouter();
//    OSPFN::DesignatedRouterID backupDRouter = parentInterface->getBackupDesignatedRouter();
//
//    if ((interfaceType == OSPFN::Interface::POINTTOPOINT) ||
//        (interfaceType == OSPFN::Interface::POINTTOMULTIPOINT) ||
//        (interfaceType == OSPFN::Interface::VIRTUAL) ||
//        (dRouter.routerID == routerID) ||
//        (backupDRouter.routerID == routerID) ||
//        ((neighborsDesignatedRouter.routerID == dRouter.routerID) ||
//         (!designatedRoutersSetUp &&
//          (neighborsDesignatedRouter.ipInterfaceAddress == dRouter.ipInterfaceAddress))) ||
//        ((neighborsBackupDesignatedRouter.routerID == backupDRouter.routerID) ||
//         (!designatedRoutersSetUp &&
//          (neighborsBackupDesignatedRouter.ipInterfaceAddress == backupDRouter.ipInterfaceAddress))))
//    {
//        return true;
//    } else {
//        return false;
//    }
}
//
///**
// * If the LSA is already on the retransmission list then it is replaced, else
// * a copy of the LSA is added to the end of the retransmission list.
// * @param lsa [in] The LSA to be added.
// */
//void OSPFN::Neighbor::addToRetransmissionList(OSPFLSA* lsa)
//{
//    std::list<OSPFLSA*>::iterator it;
//    for (it = linkStateRetransmissionList.begin(); it != linkStateRetransmissionList.end(); it++) {
//        if (((*it)->getHeader().getLinkStateID() == lsa->getHeader().getLinkStateID()) &&
//            ((*it)->getHeader().getAdvertisingRouter().getInt() == lsa->getHeader().getAdvertisingRouter().getInt()))
//        {
//            break;
//        }
//    }
//
//    OSPFLSA* lsaCopy = NULL;
//    switch (lsa->getHeader().getLsType()) {
//        case ROUTERLSA_TYPE:
//            lsaCopy = new OSPFRouterLSA(*(check_and_cast<OSPFRouterLSA*> (lsa)));
//            break;
//        case NETWORKLSA_TYPE:
//            lsaCopy = new OSPFNetworkLSA(*(check_and_cast<OSPFNetworkLSA*> (lsa)));
//            break;
//        case SUMMARYLSA_NETWORKS_TYPE:
//        case SUMMARYLSA_ASBOUNDARYROUTERS_TYPE:
//            lsaCopy = new OSPFSummaryLSA(*(check_and_cast<OSPFSummaryLSA*> (lsa)));
//            break;
//        case AS_EXTERNAL_LSA_TYPE:
//            lsaCopy = new OSPFASExternalLSA(*(check_and_cast<OSPFASExternalLSA*> (lsa)));
//            break;
//        default:
//            ASSERT(false); // error
//            break;
//    }
//
//    if (it != linkStateRetransmissionList.end()) {
//        delete (*it);
//        *it = static_cast<OSPFLSA*> (lsaCopy);
//    } else {
//        linkStateRetransmissionList.push_back(static_cast<OSPFLSA*> (lsaCopy));
//    }
//}
//
//void OSPFN::Neighbor::removeFromRetransmissionList(OSPFN::LSAKeyType lsaKey)
//{
//    std::list<OSPFLSA*>::iterator it = linkStateRetransmissionList.begin();
//    while (it != linkStateRetransmissionList.end()) {
//        if (((*it)->getHeader().getLinkStateID() == lsaKey.linkStateID) &&
//            ((*it)->getHeader().getAdvertisingRouter() == lsaKey.advertisingRouter))
//        {
//            delete (*it);
//            it = linkStateRetransmissionList.erase(it);
//        } else {
//            it++;
//        }
//    }
//}
//
//bool OSPFN::Neighbor::isLinkStateRequestListEmpty(OSPFN::LSAKeyType lsaKey) const
//{
//    for (std::list<OSPFLSA*>::const_iterator it = linkStateRetransmissionList.begin(); it != linkStateRetransmissionList.end(); it++) {
//        const OSPFLSA* lsa = *it;
//        if ((lsa->getHeader().getLinkStateID() == lsaKey.linkStateID) &&
//            (lsa->getHeader().getAdvertisingRouter() == lsaKey.advertisingRouter))
//        {
//            return true;
//        }
//    }
//    return false;
//}
//
//OSPFLSA* OSPFN::Neighbor::findOnRetransmissionList(OSPFN::LSAKeyType lsaKey)
//{
//    for (std::list<OSPFLSA*>::iterator it = linkStateRetransmissionList.begin(); it != linkStateRetransmissionList.end(); it++) {
//        if (((*it)->getHeader().getLinkStateID() == lsaKey.linkStateID) &&
//            ((*it)->getHeader().getAdvertisingRouter() == lsaKey.advertisingRouter))
//        {
//            return (*it);
//        }
//    }
//    return NULL;
//}
//
//void OSPFN::Neighbor::startUpdateRetransmissionTimer()
//{
//    MessageHandler* messageHandler = parentInterface->getArea()->getRouter()->getMessageHandler();
//    messageHandler->startTimer(updateRetransmissionTimer, parentInterface->getRetransmissionInterval());
//    updateRetransmissionTimerActive = true;
//}
//
void OSPFN::Neighbor::clearUpdateRetransmissionTimer()
{
    MessageHandler* messageHandler = parentInterface->getRouter()->getMessageHandler();
    messageHandler->clearTimer(updateRetransmissionTimer);
    updateRetransmissionTimerActive = false;
}
//
//void OSPFN::Neighbor::addToRequestList(OSPFLSAHeader* lsaHeader)
//{
//    linkStateRequestList.push_back(new OSPFLSAHeader(*lsaHeader));
//}
//
//void OSPFN::Neighbor::removeFromRequestList(OSPFN::LSAKeyType lsaKey)
//{
//    std::list<OSPFLSAHeader*>::iterator it = linkStateRequestList.begin();
//    while (it != linkStateRequestList.end()) {
//        if (((*it)->getLinkStateID() == lsaKey.linkStateID) &&
//            ((*it)->getAdvertisingRouter() == lsaKey.advertisingRouter))
//        {
//            delete (*it);
//            it = linkStateRequestList.erase(it);
//        } else {
//            it++;
//        }
//    }
//
//    if ((getState() == OSPFN::Neighbor::LOADING_STATE) && (linkStateRequestList.empty())) {
//        clearRequestRetransmissionTimer();
//        processEvent(OSPFN::Neighbor::LOADING_DONE);
//    }
//}
//
//bool OSPFN::Neighbor::isLSAOnRequestList(OSPFN::LSAKeyType lsaKey) const
//{
//    for (std::list<OSPFLSAHeader*>::const_iterator it = linkStateRequestList.begin(); it != linkStateRequestList.end(); it++) {
//        const OSPFLSAHeader* lsaHeader = *it;
//        if ((lsaHeader->getLinkStateID() == lsaKey.linkStateID) &&
//            (lsaHeader->getAdvertisingRouter() == lsaKey.advertisingRouter))
//        {
//            return true;
//        }
//    }
//    return false;
//}
//
//OSPFLSAHeader* OSPFN::Neighbor::findOnRequestList(OSPFN::LSAKeyType lsaKey)
//{
//    for (std::list<OSPFLSAHeader*>::iterator it = linkStateRequestList.begin(); it != linkStateRequestList.end(); it++) {
//        if (((*it)->getLinkStateID() == lsaKey.linkStateID) &&
//            ((*it)->getAdvertisingRouter() == lsaKey.advertisingRouter))
//        {
//            return (*it);
//        }
//    }
//    return NULL;
//}
//
void OSPFN::Neighbor::startRequestRetransmissionTimer()
{
    MessageHandler* messageHandler = parentInterface->getRouter()->getMessageHandler();
    messageHandler->startTimer(requestRetransmissionTimer, parentInterface->getRetransmissionInterval());
    requestRetransmissionTimerActive = true;
}
//
void OSPFN::Neighbor::clearRequestRetransmissionTimer()
{
    MessageHandler* messageHandler = parentInterface->getRouter()->getMessageHandler();
    messageHandler->clearTimer(requestRetransmissionTimer);
    requestRetransmissionTimerActive = false;
}
//
//void OSPFN::Neighbor::addToTransmittedLSAList(OSPFN::LSAKeyType lsaKey)
//{
//    TransmittedLSA transmit;
//
//    transmit.lsaKey = lsaKey;
//    transmit.age = 0;
//
//    transmittedLSAs.push_back(transmit);
//}
//
//bool OSPFN::Neighbor::isOnTransmittedLSAList(OSPFN::LSAKeyType lsaKey) const
//{
//    for (std::list<TransmittedLSA>::const_iterator it = transmittedLSAs.begin(); it != transmittedLSAs.end(); it++) {
//        if ((it->lsaKey.linkStateID == lsaKey.linkStateID) &&
//            (it->lsaKey.advertisingRouter == lsaKey.advertisingRouter))
//        {
//            return true;
//        }
//    }
//    return false;
//}
//
//void OSPFN::Neighbor::ageTransmittedLSAList()
//{
//    std::list<TransmittedLSA>::iterator it = transmittedLSAs.begin();
//    while ((it != transmittedLSAs.end()) && (it->age == MIN_LS_ARRIVAL)) {
//        transmittedLSAs.pop_front();
//        it = transmittedLSAs.begin();
//    }
//    for (it = transmittedLSAs.begin(); it != transmittedLSAs.end(); it++) {
//        it->age++;
//    }
//}
//
//void OSPFN::Neighbor::retransmitUpdatePacket()
//{
//    OSPFLinkStateUpdatePacket* updatePacket = new OSPFLinkStateUpdatePacket();
//
//    updatePacket->setType(LINKSTATE_UPDATE_PACKET);
//    updatePacket->setRouterID(IPv4Address(parentInterface->getArea()->getRouter()->getRouterID()));
//    updatePacket->setAreaID(IPv4Address(parentInterface->getArea()->getAreaID()));
//    updatePacket->setAuthenticationType(parentInterface->getAuthenticationType());
//    OSPFN::AuthenticationKeyType authKey = parentInterface->getAuthenticationKey();
//    for (int i = 0; i < 8; i++) {
//        updatePacket->setAuthentication(i, authKey.bytes[i]);
//    }
//
//    bool packetFull = false;
//    unsigned short lsaCount = 0;
//    unsigned long packetLength = IP_MAX_HEADER_BYTES + OSPF_LSA_HEADER_LENGTH;
//    std::list<OSPFLSA*>::iterator it = linkStateRetransmissionList.begin();
//
//    while (!packetFull && (it != linkStateRetransmissionList.end())) {
//        LSAType lsaType = static_cast<LSAType> ((*it)->getHeader().getLsType());
//        OSPFRouterLSA* routerLSA = (lsaType == ROUTERLSA_TYPE) ? dynamic_cast<OSPFRouterLSA*> (*it) : NULL;
//        OSPFNetworkLSA* networkLSA = (lsaType == NETWORKLSA_TYPE) ? dynamic_cast<OSPFNetworkLSA*> (*it) : NULL;
//        OSPFSummaryLSA* summaryLSA = ((lsaType == SUMMARYLSA_NETWORKS_TYPE) ||
//                                            (lsaType == SUMMARYLSA_ASBOUNDARYROUTERS_TYPE)) ? dynamic_cast<OSPFSummaryLSA*> (*it) : NULL;
//        OSPFASExternalLSA* asExternalLSA = (lsaType == AS_EXTERNAL_LSA_TYPE) ? dynamic_cast<OSPFASExternalLSA*> (*it) : NULL;
//        long lsaSize = 0;
//        bool includeLSA = false;
//
//        switch (lsaType) {
//            case ROUTERLSA_TYPE:
//                if (routerLSA != NULL) {
//                    lsaSize = calculateLSASize(routerLSA);
//                }
//                break;
//            case NETWORKLSA_TYPE:
//                if (networkLSA != NULL) {
//                    lsaSize = calculateLSASize(networkLSA);
//                }
//                break;
//            case SUMMARYLSA_NETWORKS_TYPE:
//            case SUMMARYLSA_ASBOUNDARYROUTERS_TYPE:
//                if (summaryLSA != NULL) {
//                    lsaSize = calculateLSASize(summaryLSA);
//                }
//                break;
//            case AS_EXTERNAL_LSA_TYPE:
//                if (asExternalLSA != NULL) {
//                    lsaSize = calculateLSASize(asExternalLSA);
//                }
//                break;
//            default: break;
//        }
//
//        if (packetLength + lsaSize < parentInterface->getMTU()) {
//            includeLSA = true;
//            lsaCount++;
//        } else {
//            if ((lsaCount == 0) && (packetLength + lsaSize < IPV4_DATAGRAM_LENGTH)) {
//                includeLSA = true;
//                lsaCount++;
//                packetFull = true;
//            }
//        }
//
//        if (includeLSA) {
//            packetLength += lsaSize;
//            switch (lsaType) {
//                case ROUTERLSA_TYPE:
//                    if (routerLSA != NULL) {
//                        unsigned int routerLSACount = updatePacket->getRouterLSAsArraySize();
//
//                        updatePacket->setRouterLSAsArraySize(routerLSACount + 1);
//                        updatePacket->setRouterLSAs(routerLSACount, *routerLSA);
//
//                        unsigned short lsAge = updatePacket->getRouterLSAs(routerLSACount).getHeader().getLsAge();
//                        if (lsAge < MAX_AGE - parentInterface->getTransmissionDelay()) {
//                            updatePacket->getRouterLSAs(routerLSACount).getHeader().setLsAge(lsAge + parentInterface->getTransmissionDelay());
//                        } else {
//                            updatePacket->getRouterLSAs(routerLSACount).getHeader().setLsAge(MAX_AGE);
//                        }
//                    }
//                    break;
//                case NETWORKLSA_TYPE:
//                    if (networkLSA != NULL) {
//                        unsigned int networkLSACount = updatePacket->getNetworkLSAsArraySize();
//
//                        updatePacket->setNetworkLSAsArraySize(networkLSACount + 1);
//                        updatePacket->setNetworkLSAs(networkLSACount, *networkLSA);
//
//                        unsigned short lsAge = updatePacket->getNetworkLSAs(networkLSACount).getHeader().getLsAge();
//                        if (lsAge < MAX_AGE - parentInterface->getTransmissionDelay()) {
//                            updatePacket->getNetworkLSAs(networkLSACount).getHeader().setLsAge(lsAge + parentInterface->getTransmissionDelay());
//                        } else {
//                            updatePacket->getNetworkLSAs(networkLSACount).getHeader().setLsAge(MAX_AGE);
//                        }
//                    }
//                    break;
//                case SUMMARYLSA_NETWORKS_TYPE:
//                case SUMMARYLSA_ASBOUNDARYROUTERS_TYPE:
//                    if (summaryLSA != NULL) {
//                        unsigned int summaryLSACount = updatePacket->getSummaryLSAsArraySize();
//
//                        updatePacket->setSummaryLSAsArraySize(summaryLSACount + 1);
//                        updatePacket->setSummaryLSAs(summaryLSACount, *summaryLSA);
//
//                        unsigned short lsAge = updatePacket->getSummaryLSAs(summaryLSACount).getHeader().getLsAge();
//                        if (lsAge < MAX_AGE - parentInterface->getTransmissionDelay()) {
//                            updatePacket->getSummaryLSAs(summaryLSACount).getHeader().setLsAge(lsAge + parentInterface->getTransmissionDelay());
//                        } else {
//                            updatePacket->getSummaryLSAs(summaryLSACount).getHeader().setLsAge(MAX_AGE);
//                        }
//                    }
//                    break;
//                case AS_EXTERNAL_LSA_TYPE:
//                    if (asExternalLSA != NULL) {
//                        unsigned int asExternalLSACount = updatePacket->getAsExternalLSAsArraySize();
//
//                        updatePacket->setAsExternalLSAsArraySize(asExternalLSACount + 1);
//                        updatePacket->setAsExternalLSAs(asExternalLSACount, *asExternalLSA);
//
//                        unsigned short lsAge = updatePacket->getAsExternalLSAs(asExternalLSACount).getHeader().getLsAge();
//                        if (lsAge < MAX_AGE - parentInterface->getTransmissionDelay()) {
//                            updatePacket->getAsExternalLSAs(asExternalLSACount).getHeader().setLsAge(lsAge + parentInterface->getTransmissionDelay());
//                        } else {
//                            updatePacket->getAsExternalLSAs(asExternalLSACount).getHeader().setLsAge(MAX_AGE);
//                        }
//                    }
//                    break;
//                default: break;
//            }
//        }
//
//        it++;
//    }
//
//    updatePacket->setByteLength(packetLength - IP_MAX_HEADER_BYTES);
//
//    OSPFN::MessageHandler* messageHandler = parentInterface->getArea()->getRouter()->getMessageHandler();
//    int ttl = (parentInterface->getType() == OSPFN::Interface::VIRTUAL) ? VIRTUAL_LINK_TTL : 1;
//    messageHandler->sendPacket(updatePacket, neighborAddress, parentInterface->getIfIndex(), ttl);
//}
//
//void OSPFN::Neighbor::deleteLastSentDDPacket()
//{
//    if (lastTransmittedDDPacket != NULL) {
//        delete lastTransmittedDDPacket;
//        lastTransmittedDDPacket = NULL;
//    }
//}

