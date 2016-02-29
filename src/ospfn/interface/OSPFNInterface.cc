//
// Copyright (C) 2006 Andras Babos and Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include <vector>
#include <memory.h>

#include "OSPFNInterface.h"

//#include "InterfaceTableAccess.h"
//#include "IPv4Datagram_m.h"
//#include "IPv4InterfaceData.h"
#include "IOSPFNMessageHandler.h"
//#include "OSPFArea.h"
#include "OSPFNInterfaceStateDown.h"
#include "OSPFNRouter.h"
#include "CcnAppMessage_m.h"
#include "OSPFNRouting.h"
class OSPFNRouting;

OSPFN::Interface::Interface(OSPFN::Interface::OSPFInterfaceType ifType) :
    interfaceType(ifType),
//    ifIndex(0),
//    mtu(0),
//    interfaceAddressRange(OSPFN::NULL_IPV4ADDRESSRANGE),
//    areaID(OSPFN::BACKBONE_AREAID),
//    transitAreaID(OSPFN::BACKBONE_AREAID),
      helloInterval(5),
//    pollInterval(120),
//    routerDeadInterval(40),
//    interfaceTransmissionDelay(1),
      routerPriority(0),
//    designatedRouter(OSPFN::NULL_DESIGNATEDROUTERID),
//    backupDesignatedRouter(OSPFN::NULL_DESIGNATEDROUTERID),
//    interfaceOutputCost(1),
    retransmissionInterval(5),
    acknowledgementDelay(2)
//    authenticationType(OSPFN::NULL_TYPE),
//    parentArea(NULL)
{
    parentRouter = NULL;
    this->macaddress = MACAddress::UNSPECIFIED_ADDRESS;
    macName = "";
    state = new OSPFN::InterfaceStateDown;
    previousState = NULL;
    helloTimer = new OSPFNTimer();
    helloTimer->setTimerKind(INTERFACE_HELLO_TIMER);
    helloTimer->setContextPointer(this);
    helloTimer->setName("OSPFN::Interface::InterfaceHelloTimer");
    waitTimer = new OSPFNTimer();
    waitTimer->setTimerKind(INTERFACE_WAIT_TIMER);
    waitTimer->setContextPointer(this);
    waitTimer->setName("OSPFN::Interface::InterfaceWaitTimer");
    acknowledgementTimer = new OSPFNTimer();
    acknowledgementTimer->setTimerKind(INTERFACE_ACKNOWLEDGEMENT_TIMER);
    acknowledgementTimer->setContextPointer(this);
    acknowledgementTimer->setName("OSPFN::Interface::InterfaceAcknowledgementTimer");
//    memset(authenticationKey.bytes, 0, 8 * sizeof(char));
}

OSPFN::Interface::~Interface()
{
    MessageHandler* messageHandler = getRouter()->getMessageHandler();
    messageHandler->clearTimer(helloTimer);
    delete helloTimer;
    messageHandler->clearTimer(waitTimer);
    delete waitTimer;
    messageHandler->clearTimer(acknowledgementTimer);
    delete acknowledgementTimer;
    if (previousState != NULL) {
        delete previousState;
    }
    delete state;
    long neighborCount = neighboringRouters.size();
   for (long i = 0; i < neighborCount; i++) {
        delete neighboringRouters[i];
    }
   neighboringRouters.clear();
}

void OSPFN::Interface::clearNeighborhood(){
    long neighborCount = neighboringRouters.size();

    for (long i = 0; i < neighborCount; i++) {
          delete neighboringRouters[i];

    }
    neighboringRouters.clear();

    neighboringRoutersByID.clear();
    neighboringRoutersByAddress.clear();

}
//
//void OSPFN::Interface::setIfIndex(int index)
//{
//    ifIndex = index;
//    if (interfaceType == OSPFN::Interface::UNKNOWN_TYPE) {
//        InterfaceEntry* routingInterface = InterfaceTableAccess().get()->getInterfaceById(ifIndex);
//        interfaceAddressRange.address = routingInterface->ipv4Data()->getIPAddress();
//        interfaceAddressRange.mask = routingInterface->ipv4Data()->getNetmask();
//        mtu = routingInterface->getMTU();
//    }
//}
//
void OSPFN::Interface::changeState(OSPFN::InterfaceState* newState, OSPFN::InterfaceState* currentState)
{
    if (previousState != NULL) {
        delete previousState;
    }
    state = newState;
    previousState = currentState;
}

void OSPFN::Interface::processEvent(OSPFN::Interface::InterfaceEventType event)
{
    state->processEvent(this, event);
}

void OSPFN::Interface::addNewPrefixFromNeighbor(chunk_t prefix, MACAddress src, MACAddress dest, int hops){

    parentRouter->addToPrefixTable(prefix,src,dest,false,hops,true);

    //New prefix, advise this new prefix.
//    parentRouter->getMessageHandler()->clearTimer(getHelloTimer());
//    parentRouter->getMessageHandler()->startTimer(getHelloTimer(), 0.1);

}

OSPFNLinkStateAcknowledgementPacket* OSPFN::Interface::createLinkStateAckPacket(std::vector<chunk_t> lsa_req_v){

    OSPFNLinkStateAcknowledgementPacket* packet = new OSPFNLinkStateAcknowledgementPacket("LSAPacket");
    packet->setType(OSPFN_LINKSTATE_ACKNOWLEDGEMENT_PACKET);
//    int size = retransmissionLSAList.size();

    std::vector<adv_prefix> prefix_vec = parentRouter->getPrefixesToAdvertise(lsa_req_v);
    int size = prefix_vec.size();
    if(size > 0){
        packet->setLSAsArraySize(size);
        packet->setHopsArraySize(size);


        for(int i = 0; i < size; i++){
            packet->setLSAs(i,prefix_vec[i].prefix.c_str());
            packet->setHops(i,prefix_vec[i].hops);
        }

        return packet;
    }
    delete packet;
    return NULL;
}

void OSPFN::Interface::addBroadcastFaceToForwardingTable(){
    if(macaddress == MACAddress::UNSPECIFIED_ADDRESS)
        opp_error("Calling addFaceToForwardingTable before set interface MAC Address.");
    else if(parentRouter == NULL)
        opp_error("You have to add the interface into a Router first. 'ospfnRouter->addInterface(interface)'");

    char content_name[64];
    sprintf(content_name, "/%s/%s", ALL_OSPFN_ROUTERS_MCAST, getInterfaceName().c_str());

    parentRouter->addToPrefixTable(content_name, MACAddress::BROADCAST_ADDRESS ,macaddress,true,0,false );
    parentRouter->rebuildForwardingTable();
}

bool OSPFN::Interface::floodHello(){

//    OSPFNRouting* routing = reinterpret_cast<OSPFNRouting*>(getRouter()->getMessageHandler()->getOSPFNModule()) ;
//
//    if(routing->getCurrentTime()- parentRouter->lastFlood < floodInterval)
//        return false;

    sendHelloPacket(ALL_OSPFN_ROUTERS_MCAST);

//    parentRouter->lastFlood = routing->getCurrentTime().dbl();

    return true;
}

void OSPFN::Interface::sendHelloPacket(chunk_t destination){

   CcnAppMessage * ccn_i = new CcnAppMessage("ospfn:/Hello");
   ccn_i->setType(CCN_APP_INTEREST);
   ccn_i->setAppId(CCN_OSPFN_APP);
   ccn_i->setSeqNr(1);

   char content_name[64];

   OSPFNHelloPacket *ospfnpkt = new OSPFNHelloPacket();
   ospfnpkt->setDestination(destination.c_str());
   ospfnpkt->setRouterID(getRouter()->getRouterID().c_str());


   int neighborRoutersSize = neighboringRouters.size();
   ospfnpkt->setNeighborArraySize(neighborRoutersSize);
   for ( int i = 0; i < neighborRoutersSize ; i++){
       ospfnpkt->setNeighbor(i,neighboringRouters[i]->getAddress());
   }

   ccn_i->encapsulate(ospfnpkt);

   if(destination == ALL_NEIGHBOR_ROUTERS){
       int neighborRoutersSize = neighboringRouters.size();
       for ( int i = 0; i < neighborRoutersSize ; i++){
              ospfnpkt->setNeighbor(i,neighboringRouters[i]->getAddress());
              sprintf(content_name, "/%s/%s/hello", neighboringRouters[i]->getNeighborID().c_str(), getInterfaceName().c_str());
              ccn_i->setContentName(content_name);
              getRouter()->getMessageHandler()->send(ccn_i->dup());
       }
   }else {
       sprintf(content_name, "/%s/%s/hello", destination.c_str(), getInterfaceName().c_str());
       ccn_i->setContentName(content_name);
       getRouter()->getMessageHandler()->send(ccn_i->dup());
   }

   delete ccn_i;
}

string OSPFN::Interface::getPacketTypeName(int type){

    switch(type){
        case OSPFN_HELLO_PACKET : return "hello";
        case OSPFN_DATABASE_DESCRIPTION_PACKET : return "db_description";
        case OSPFN_LINKSTATE_REQUEST_PACKET : return "lsa_req";
        case OSPFN_LINKSTATE_UPDATE_PACKET : return "lsa_upd";
        case OSPFN_LINKSTATE_ACKNOWLEDGEMENT_PACKET : return "lsa_ack";
        default : return "none";
    }

}
void OSPFN::Interface::sendOSPFNPacket(OSPFNPacket *ospfnpkt, chunk_t destination){

   string packetName = "ospfn:/"+getPacketTypeName(ospfnpkt->getType());

   CcnAppMessage * ccn_i = new CcnAppMessage(packetName.c_str());
   ccn_i->setType(CCN_APP_INTEREST);
   ccn_i->setAppId(CCN_OSPFN_APP);
   ccn_i->setSeqNr(1);

   char content_name[64];
   sprintf(content_name, "/%s/%s/%s", destination.c_str(), getInterfaceName().c_str(),getPacketTypeName(ospfnpkt->getType()).c_str());
   ccn_i->setContentName(content_name);

   ospfnpkt->setDestination(destination.c_str());
   ospfnpkt->setRouterID(getRouter()->getRouterID().c_str());


   ccn_i->encapsulate(ospfnpkt);

   getRouter()->getMessageHandler()->send(ccn_i);
}

std::string OSPFN::Interface::getInterfaceName(){

    if ( macName == ""){
        macName = getMACAddress().str();
            Util::replace(macName,':','_');
    }

    return macName;
}
//
void OSPFN::Interface::reset()
{
    MessageHandler* messageHandler = getRouter()->getMessageHandler();
    messageHandler->clearTimer(helloTimer);
    messageHandler->clearTimer(waitTimer);
    messageHandler->clearTimer(acknowledgementTimer);
    designatedRouter = NULL_DESIGNATEDROUTERID;
    backupDesignatedRouter = NULL_DESIGNATEDROUTERID;
    long neighborCount = neighboringRouters.size();
    for (long i = 0; i < neighborCount; i++) {
        neighboringRouters[i]->processEvent(OSPFN::KILL_NEIGHBOR);
    }
}
//
//void OSPFN::Interface::sendHelloPacket(IPv4Address destination, short ttl)
//{
//    OSPFOptions options;
//    OSPFHelloPacket* helloPacket = new OSPFHelloPacket();
//    std::vector<IPv4Address> neighbors;
//
//    helloPacket->setRouterID(IPv4Address(parentArea->getRouter()->getRouterID()));
//    helloPacket->setAreaID(IPv4Address(parentArea->getAreaID()));
//    helloPacket->setAuthenticationType(authenticationType);
//    for (int i = 0; i < 8; i++) {
//        helloPacket->setAuthentication(i, authenticationKey.bytes[i]);
//    }
//
//    if (((interfaceType == POINTTOPOINT) &&
//         (interfaceAddressRange.address == OSPFN::NULL_IPV4ADDRESS)) ||
//        (interfaceType == VIRTUAL))
//    {
//        helloPacket->setNetworkMask(OSPFN::NULL_IPV4ADDRESS);
//    } else {
//        helloPacket->setNetworkMask(interfaceAddressRange.mask);
//    }
//    memset(&options, 0, sizeof(OSPFOptions));
//    options.E_ExternalRoutingCapability = parentArea->getExternalRoutingCapability();
//    helloPacket->setOptions(options);
//    helloPacket->setHelloInterval(helloInterval);
//    helloPacket->setRouterPriority(routerPriority);
//    helloPacket->setRouterDeadInterval(routerDeadInterval);
//    helloPacket->setDesignatedRouter(designatedRouter.ipInterfaceAddress);
//    helloPacket->setBackupDesignatedRouter(backupDesignatedRouter.ipInterfaceAddress);
//    long neighborCount = neighboringRouters.size();
//    for (long j = 0; j < neighborCount; j++) {
//        if (neighboringRouters[j]->getState() >= OSPFN::Neighbor::INIT_STATE) {
//            neighbors.push_back(neighboringRouters[j]->getAddress());
//        }
//    }
//    unsigned int initedNeighborCount = neighbors.size();
//    helloPacket->setNeighborArraySize(initedNeighborCount);
//    for (unsigned int k = 0; k < initedNeighborCount; k++) {
//        helloPacket->setNeighbor(k, neighbors[k]);
//    }
//
//    helloPacket->setByteLength(OSPF_HEADER_LENGTH + OSPF_HELLO_HEADER_LENGTH + initedNeighborCount*4);
//
//    parentArea->getRouter()->getMessageHandler()->sendPacket(helloPacket, destination, ifIndex, ttl);
//}
//
//void OSPFN::Interface::sendLSAcknowledgement(OSPFLSAHeader* lsaHeader, IPv4Address destination)
//{
//    OSPFOptions options;
//    OSPFLinkStateAcknowledgementPacket* lsAckPacket = new OSPFLinkStateAcknowledgementPacket();
//
//    lsAckPacket->setType(LINKSTATE_ACKNOWLEDGEMENT_PACKET);
//    lsAckPacket->setRouterID(IPv4Address(parentArea->getRouter()->getRouterID()));
//    lsAckPacket->setAreaID(IPv4Address(parentArea->getAreaID()));
//    lsAckPacket->setAuthenticationType(authenticationType);
//    for (int i = 0; i < 8; i++) {
//        lsAckPacket->setAuthentication(i, authenticationKey.bytes[i]);
//    }
//
//    lsAckPacket->setLsaHeadersArraySize(1);
//    lsAckPacket->setLsaHeaders(0, *lsaHeader);
//
//    lsAckPacket->setByteLength(OSPF_HEADER_LENGTH + OSPF_LSA_HEADER_LENGTH);
//
//    int ttl = (interfaceType == OSPFN::Interface::VIRTUAL) ? VIRTUAL_LINK_TTL : 1;
//    parentArea->getRouter()->getMessageHandler()->sendPacket(lsAckPacket, destination, ifIndex, ttl);
//}
//
//
OSPFN::Neighbor* OSPFN::Interface::getNeighborByID(string neighborID)
{
    std::map<string, OSPFN::Neighbor*>::iterator neighborIt = neighboringRoutersByID.find(neighborID);
    if (neighborIt != neighboringRoutersByID.end()) {
        return (neighborIt->second);
    }
    else {
        return NULL;
    }
}
//
OSPFN::Neighbor* OSPFN::Interface::getNeighborByAddress(MACAddress address)
{
    std::map<MACAddress, OSPFN::Neighbor*>::iterator neighborIt =
            neighboringRoutersByAddress.find(address);

    if (neighborIt != neighboringRoutersByAddress.end()) {
        return (neighborIt->second);
    }
    else {
        return NULL;
    }
}

void OSPFN::Interface::addNeighborToPrefixTable(OSPFN::Neighbor* neighbor){

   string prefix = neighbor->getNeighborID();
//   PRINT_ERR << "Adicionando à tabela de prefixo: prefix:"
//           << prefix << " src:"<< neighbor->getSrcAddr() <<" dest:" << neighbor->getDestAddr() << ENDL;
   parentRouter->addToPrefixTable(prefix, neighbor->getSrcAddr(),neighbor->getDestAddr(),false,1,true);
}

void OSPFN::Interface::addPrefixToRetransmissionList(chunk_t prefix){

    retransmissionLSAList.push_back(prefix);
}
//
void OSPFN::Interface::addNeighbor(OSPFN::Neighbor* neighbor)
{

    addNeighborToPrefixTable(neighbor);

    neighboringRoutersByID[neighbor->getNeighborID()] = neighbor;
    neighboringRoutersByAddress[neighbor->getAddress()] = neighbor;
    neighbor->setInterface(this);
    neighboringRouters.push_back(neighbor);
}
//
OSPFN::Interface::InterfaceStateType OSPFN::Interface::getState() const
{
    return state->getState();
}
//
const char* OSPFN::Interface::getStateString(OSPFN::Interface::InterfaceStateType stateType)
{
    switch (stateType) {
        case DOWN_STATE:                 return "Down";
        case LOOPBACK_STATE:             return "Loopback";
        case WAITING_STATE:              return "Waiting";
        case POINTTOPOINT_STATE:         return "PointToPoint";
        case NOT_DESIGNATED_ROUTER_STATE:  return "NotDesignatedRouter";
        case BACKUP_STATE:               return "Backup";
        case DESIGNATED_ROUTER_STATE:     return "DesignatedRouter";
        default:                        ASSERT(false); break;
    }
    return "";
}
//
//bool OSPFN::Interface::hasAnyNeighborInStates(int states) const
//{
//    long neighborCount = neighboringRouters.size();
//    for (long i = 0; i < neighborCount; i++) {
//        OSPFN::Neighbor::NeighborStateType neighborState = neighboringRouters[i]->getState();
//        if (neighborState & states) {
//            return true;
//        }
//    }
//    return false;
//}
//
//void OSPFN::Interface::removeFromAllRetransmissionLists(OSPFN::LSAKeyType lsaKey)
//{
//    long neighborCount = neighboringRouters.size();
//    for (long i = 0; i < neighborCount; i++) {
//        neighboringRouters[i]->removeFromRetransmissionList(lsaKey);
//    }
//}
//
//bool OSPFN::Interface::isOnAnyRetransmissionList(OSPFN::LSAKeyType lsaKey) const
//{
//    long neighborCount = neighboringRouters.size();
//    for (long i = 0; i < neighborCount; i++) {
//        if (neighboringRouters[i]->isLinkStateRequestListEmpty(lsaKey)) {
//            return true;
//        }
//    }
//    return false;
//}
//
///**
// * @see RFC2328 Section 13.3.
// */
//bool OSPFN::Interface::floodLSA(OSPFLSA* lsa, OSPFN::Interface* intf, OSPFN::Neighbor* neighbor)
//{
//    bool floodedBackOut = false;
//
//    if (
//        (
//         (lsa->getHeader().getLsType() == AS_EXTERNAL_LSA_TYPE) &&
//         (interfaceType != OSPFN::Interface::VIRTUAL) &&
//         (parentArea->getExternalRoutingCapability())
//        ) ||
//        (
//         (lsa->getHeader().getLsType() != AS_EXTERNAL_LSA_TYPE) &&
//         (
//          (
//           (areaID != OSPFN::BACKBONE_AREAID) &&
//           (interfaceType != OSPFN::Interface::VIRTUAL)
//          ) ||
//          (areaID == OSPFN::BACKBONE_AREAID)
//         )
//        )
//       )
//    {
//        long neighborCount = neighboringRouters.size();
//        bool lsaAddedToRetransmissionList = false;
//        OSPFN::LinkStateID linkStateID = lsa->getHeader().getLinkStateID();
//        OSPFN::LSAKeyType lsaKey;
//
//        lsaKey.linkStateID = linkStateID;
//        lsaKey.advertisingRouter = lsa->getHeader().getAdvertisingRouter();
//
//        for (long i = 0; i < neighborCount; i++) {  // (1)
//            if (neighboringRouters[i]->getState() < OSPFN::Neighbor::EXCHANGE_STATE) {   // (1) (a)
//                continue;
//            }
//            if (neighboringRouters[i]->getState() < OSPFN::Neighbor::FULL_STATE) {   // (1) (b)
//                OSPFLSAHeader* requestLSAHeader = neighboringRouters[i]->findOnRequestList(lsaKey);
//                if (requestLSAHeader != NULL) {
//                    // operator< and operator== on OSPFLSAHeaders determines which one is newer(less means older)
//                    if (lsa->getHeader() < (*requestLSAHeader)) {
//                        continue;
//                    }
//                    if (operator==(lsa->getHeader(), (*requestLSAHeader))) {
//                        neighboringRouters[i]->removeFromRequestList(lsaKey);
//                        continue;
//                    }
//                    neighboringRouters[i]->removeFromRequestList(lsaKey);
//                }
//            }
//            if (neighbor == neighboringRouters[i]) {     // (1) (c)
//                continue;
//            }
//            neighboringRouters[i]->addToRetransmissionList(lsa);   // (1) (d)
//            lsaAddedToRetransmissionList = true;
//        }
//        if (lsaAddedToRetransmissionList) {     // (2)
//            if ((intf != this) ||
//                ((neighbor != NULL) &&
//                 (neighbor->getNeighborID() != designatedRouter.routerID) &&
//                 (neighbor->getNeighborID() != backupDesignatedRouter.routerID)))  // (3)
//            {
//                if ((intf != this) || (getState() != OSPFN::Interface::BACKUP_STATE)) {  // (4)
//                    OSPFLinkStateUpdatePacket* updatePacket = createUpdatePacket(lsa);    // (5)
//
//                    if (updatePacket != NULL) {
//                        int ttl = (interfaceType == OSPFN::Interface::VIRTUAL) ? VIRTUAL_LINK_TTL : 1;
//                        OSPFN::MessageHandler* messageHandler = parentArea->getRouter()->getMessageHandler();
//
//                        if (interfaceType == OSPFN::Interface::BROADCAST) {
//                            if ((getState() == OSPFN::Interface::DESIGNATED_ROUTER_STATE) ||
//                                (getState() == OSPFN::Interface::BACKUP_STATE) ||
//                                (designatedRouter == OSPFN::NULL_DESIGNATEDROUTERID))
//                            {
//                                messageHandler->sendPacket(updatePacket, IPv4Address::ALL_OSPF_ROUTERS_MCAST, ifIndex, ttl);
//                                for (long k = 0; k < neighborCount; k++) {
//                                    neighboringRouters[k]->addToTransmittedLSAList(lsaKey);
//                                    if (!neighboringRouters[k]->isUpdateRetransmissionTimerActive()) {
//                                        neighboringRouters[k]->startUpdateRetransmissionTimer();
//                                    }
//                                }
//                            } else {
//                                messageHandler->sendPacket(updatePacket, IPv4Address::ALL_OSPF_DESIGNATED_ROUTERS_MCAST, ifIndex, ttl);
//                                OSPFN::Neighbor* dRouter = getNeighborByID(designatedRouter.routerID);
//                                OSPFN::Neighbor* backupDRouter = getNeighborByID(backupDesignatedRouter.routerID);
//                                if (dRouter != NULL) {
//                                    dRouter->addToTransmittedLSAList(lsaKey);
//                                    if (!dRouter->isUpdateRetransmissionTimerActive()) {
//                                        dRouter->startUpdateRetransmissionTimer();
//                                    }
//                                }
//                                if (backupDRouter != NULL) {
//                                    backupDRouter->addToTransmittedLSAList(lsaKey);
//                                    if (!backupDRouter->isUpdateRetransmissionTimerActive()) {
//                                        backupDRouter->startUpdateRetransmissionTimer();
//                                    }
//                                }
//                            }
//                        } else {
//                            if (interfaceType == OSPFN::Interface::POINTTOPOINT) {
//                                messageHandler->sendPacket(updatePacket, IPv4Address::ALL_OSPF_ROUTERS_MCAST, ifIndex, ttl);
//                                if (neighborCount > 0) {
//                                    neighboringRouters[0]->addToTransmittedLSAList(lsaKey);
//                                    if (!neighboringRouters[0]->isUpdateRetransmissionTimerActive()) {
//                                        neighboringRouters[0]->startUpdateRetransmissionTimer();
//                                    }
//                                }
//                            } else {
//                                for (long m = 0; m < neighborCount; m++) {
//                                    if (neighboringRouters[m]->getState() >= OSPFN::Neighbor::EXCHANGE_STATE) {
//                                        messageHandler->sendPacket(updatePacket, neighboringRouters[m]->getAddress(), ifIndex, ttl);
//                                        neighboringRouters[m]->addToTransmittedLSAList(lsaKey);
//                                        if (!neighboringRouters[m]->isUpdateRetransmissionTimerActive()) {
//                                            neighboringRouters[m]->startUpdateRetransmissionTimer();
//                                        }
//                                    }
//                                }
//                            }
//                        }
//
//                        if (intf == this) {
//                            floodedBackOut = true;
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    return floodedBackOut;
//}
//
//OSPFLinkStateUpdatePacket* OSPFN::Interface::createUpdatePacket(OSPFLSA* lsa)
//{
//    LSAType lsaType = static_cast<LSAType> (lsa->getHeader().getLsType());
//    OSPFRouterLSA* routerLSA = (lsaType == ROUTERLSA_TYPE) ? dynamic_cast<OSPFRouterLSA*> (lsa) : NULL;
//    OSPFNetworkLSA* networkLSA = (lsaType == NETWORKLSA_TYPE) ? dynamic_cast<OSPFNetworkLSA*> (lsa) : NULL;
//    OSPFSummaryLSA* summaryLSA = ((lsaType == SUMMARYLSA_NETWORKS_TYPE) ||
//                                        (lsaType == SUMMARYLSA_ASBOUNDARYROUTERS_TYPE)) ? dynamic_cast<OSPFSummaryLSA*> (lsa) : NULL;
//    OSPFASExternalLSA* asExternalLSA = (lsaType == AS_EXTERNAL_LSA_TYPE) ? dynamic_cast<OSPFASExternalLSA*> (lsa) : NULL;
//
//    if (((lsaType == ROUTERLSA_TYPE) && (routerLSA != NULL)) ||
//        ((lsaType == NETWORKLSA_TYPE) && (networkLSA != NULL)) ||
//        (((lsaType == SUMMARYLSA_NETWORKS_TYPE) || (lsaType == SUMMARYLSA_ASBOUNDARYROUTERS_TYPE)) && (summaryLSA != NULL)) ||
//        ((lsaType == AS_EXTERNAL_LSA_TYPE) && (asExternalLSA != NULL)))
//    {
//        OSPFLinkStateUpdatePacket* updatePacket = new OSPFLinkStateUpdatePacket();
//        long packetLength = OSPF_HEADER_LENGTH + sizeof(uint32_t);  // OSPF header + place for number of advertisements
//
//        updatePacket->setType(LINKSTATE_UPDATE_PACKET);
//        updatePacket->setRouterID(IPv4Address(parentArea->getRouter()->getRouterID()));
//        updatePacket->setAreaID(IPv4Address(areaID));
//        updatePacket->setAuthenticationType(authenticationType);
//        for (int j = 0; j < 8; j++) {
//            updatePacket->setAuthentication(j, authenticationKey.bytes[j]);
//        }
//
//        updatePacket->setNumberOfLSAs(1);
//
//        switch (lsaType) {
//            case ROUTERLSA_TYPE:
//                {
//                    updatePacket->setRouterLSAsArraySize(1);
//                    updatePacket->setRouterLSAs(0, *routerLSA);
//                    unsigned short lsAge = updatePacket->getRouterLSAs(0).getHeader().getLsAge();
//                    if (lsAge < MAX_AGE - interfaceTransmissionDelay) {
//                        updatePacket->getRouterLSAs(0).getHeader().setLsAge(lsAge + interfaceTransmissionDelay);
//                    } else {
//                        updatePacket->getRouterLSAs(0).getHeader().setLsAge(MAX_AGE);
//                    }
//                    packetLength += calculateLSASize(routerLSA);
//                }
//                break;
//            case NETWORKLSA_TYPE:
//                {
//                    updatePacket->setNetworkLSAsArraySize(1);
//                    updatePacket->setNetworkLSAs(0, *networkLSA);
//                    unsigned short lsAge = updatePacket->getNetworkLSAs(0).getHeader().getLsAge();
//                    if (lsAge < MAX_AGE - interfaceTransmissionDelay) {
//                        updatePacket->getNetworkLSAs(0).getHeader().setLsAge(lsAge + interfaceTransmissionDelay);
//                    } else {
//                        updatePacket->getNetworkLSAs(0).getHeader().setLsAge(MAX_AGE);
//                    }
//                    packetLength += calculateLSASize(networkLSA);
//                }
//                break;
//            case SUMMARYLSA_NETWORKS_TYPE:
//            case SUMMARYLSA_ASBOUNDARYROUTERS_TYPE:
//                {
//                    updatePacket->setSummaryLSAsArraySize(1);
//                    updatePacket->setSummaryLSAs(0, *summaryLSA);
//                    unsigned short lsAge = updatePacket->getSummaryLSAs(0).getHeader().getLsAge();
//                    if (lsAge < MAX_AGE - interfaceTransmissionDelay) {
//                        updatePacket->getSummaryLSAs(0).getHeader().setLsAge(lsAge + interfaceTransmissionDelay);
//                    } else {
//                        updatePacket->getSummaryLSAs(0).getHeader().setLsAge(MAX_AGE);
//                    }
//                    packetLength += calculateLSASize(summaryLSA);
//                }
//                break;
//            case AS_EXTERNAL_LSA_TYPE:
//                {
//                    updatePacket->setAsExternalLSAsArraySize(1);
//                    updatePacket->setAsExternalLSAs(0, *asExternalLSA);
//                    unsigned short lsAge = updatePacket->getAsExternalLSAs(0).getHeader().getLsAge();
//                    if (lsAge < MAX_AGE - interfaceTransmissionDelay) {
//                        updatePacket->getAsExternalLSAs(0).getHeader().setLsAge(lsAge + interfaceTransmissionDelay);
//                    } else {
//                        updatePacket->getAsExternalLSAs(0).getHeader().setLsAge(MAX_AGE);
//                    }
//                    packetLength += calculateLSASize(asExternalLSA);
//                }
//                break;
//            default: throw cRuntimeError("Invalid LSA type: %d", lsaType);
//        }
//
//        updatePacket->setByteLength(packetLength);
//
//        return updatePacket;
//    }
//    return NULL;
//}
//
//void OSPFN::Interface::addDelayedAcknowledgement(OSPFLSAHeader& lsaHeader)
//{
//    if (interfaceType == OSPFN::Interface::BROADCAST) {
//        if ((getState() == OSPFN::Interface::DESIGNATED_ROUTER_STATE) ||
//            (getState() == OSPFN::Interface::BACKUP_STATE) ||
//            (designatedRouter == OSPFN::NULL_DESIGNATEDROUTERID))
//        {
//            delayedAcknowledgements[IPv4Address::ALL_OSPF_ROUTERS_MCAST].push_back(lsaHeader);
//        } else {
//            delayedAcknowledgements[IPv4Address::ALL_OSPF_DESIGNATED_ROUTERS_MCAST].push_back(lsaHeader);
//        }
//    } else {
//        long neighborCount = neighboringRouters.size();
//        for (long i = 0; i < neighborCount; i++) {
//            if (neighboringRouters[i]->getState() >= OSPFN::Neighbor::EXCHANGE_STATE) {
//                delayedAcknowledgements[neighboringRouters[i]->getAddress()].push_back(lsaHeader);
//            }
//        }
//    }
//}
//
//void OSPFN::Interface::sendDelayedAcknowledgements()
//{
//    OSPFN::MessageHandler* messageHandler = parentArea->getRouter()->getMessageHandler();
//    long maxPacketSize = ((IP_MAX_HEADER_BYTES + OSPF_HEADER_LENGTH + OSPF_LSA_HEADER_LENGTH) > mtu) ? IPV4_DATAGRAM_LENGTH : mtu;
//
//    for (std::map<IPv4Address, std::list<OSPFLSAHeader> >::iterator delayIt = delayedAcknowledgements.begin();
//         delayIt != delayedAcknowledgements.end();
//         delayIt++)
//    {
//        int ackCount = delayIt->second.size();
//        if (ackCount > 0) {
//            while (!(delayIt->second.empty())) {
//                OSPFLinkStateAcknowledgementPacket* ackPacket = new OSPFLinkStateAcknowledgementPacket();
//                long packetSize = IP_MAX_HEADER_BYTES + OSPF_HEADER_LENGTH;
//
//                ackPacket->setType(LINKSTATE_ACKNOWLEDGEMENT_PACKET);
//                ackPacket->setRouterID(IPv4Address(parentArea->getRouter()->getRouterID()));
//                ackPacket->setAreaID(IPv4Address(areaID));
//                ackPacket->setAuthenticationType(authenticationType);
//                for (int i = 0; i < 8; i++) {
//                    ackPacket->setAuthentication(i, authenticationKey.bytes[i]);
//                }
//
//                while ((!(delayIt->second.empty())) && (packetSize <= (maxPacketSize - OSPF_LSA_HEADER_LENGTH))) {
//                    unsigned long headerCount = ackPacket->getLsaHeadersArraySize();
//                    ackPacket->setLsaHeadersArraySize(headerCount + 1);
//                    ackPacket->setLsaHeaders(headerCount, *(delayIt->second.begin()));
//                    delayIt->second.pop_front();
//                    packetSize += OSPF_LSA_HEADER_LENGTH;
//                }
//
//                ackPacket->setByteLength(packetSize - IP_MAX_HEADER_BYTES);
//
//                int ttl = (interfaceType == OSPFN::Interface::VIRTUAL) ? VIRTUAL_LINK_TTL : 1;
//
//                if (interfaceType == OSPFN::Interface::BROADCAST) {
//                    if ((getState() == OSPFN::Interface::DESIGNATED_ROUTER_STATE) ||
//                        (getState() == OSPFN::Interface::BACKUP_STATE) ||
//                        (designatedRouter == OSPFN::NULL_DESIGNATEDROUTERID))
//                    {
//                        messageHandler->sendPacket(ackPacket, IPv4Address::ALL_OSPF_ROUTERS_MCAST, ifIndex, ttl);
//                    } else {
//                        messageHandler->sendPacket(ackPacket, IPv4Address::ALL_OSPF_DESIGNATED_ROUTERS_MCAST, ifIndex, ttl);
//                    }
//                } else {
//                    if (interfaceType == OSPFN::Interface::POINTTOPOINT) {
//                        messageHandler->sendPacket(ackPacket, IPv4Address::ALL_OSPF_ROUTERS_MCAST, ifIndex, ttl);
//                    } else {
//                        messageHandler->sendPacket(ackPacket, delayIt->first, ifIndex, ttl);
//                    }
//                }
//            }
//        }
//    }
//    messageHandler->startTimer(acknowledgementTimer, acknowledgementDelay);
//}
//
//void OSPFN::Interface::ageTransmittedLSALists()
//{
//    long neighborCount = neighboringRouters.size();
//    for (long i = 0; i < neighborCount; i++) {
//        neighboringRouters[i]->ageTransmittedLSAList();
//    }
//}
