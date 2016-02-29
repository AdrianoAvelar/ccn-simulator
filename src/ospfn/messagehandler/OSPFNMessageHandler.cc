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

#include "OSPFNMessageHandler.h"

//#include "ICMPMessage.h"
#include "OSPFNRouter.h"

//
OSPFN::MessageHandler::MessageHandler(OSPFN::Router* containingRouter,
        cSimpleModule* containingModule) :
        OSPFN::IMessageHandler(containingRouter),
        ospfModule(containingModule),
        helloHandler(containingRouter),
        ddHandler(containingRouter),
    lsRequestHandler(containingRouter),
//    lsUpdateHandler(containingRouter),
    lsAckHandler(containingRouter)
{
}
//
void OSPFN::MessageHandler::messageReceived(cMessage* message) {
    if (message->isSelfMessage()) {
        handleTimer (check_and_cast<OSPFNTimer*>(message));
    } else {

            CcnAppMessage * ccnAppPkt = check_and_cast<CcnAppMessage *>(message);
            Ieee802Ctrl *macCtx = check_and_cast<Ieee802Ctrl *>(ccnAppPkt->removeControlInfo());
            OSPFNPacket* packet = check_and_cast<OSPFNPacket*> (ccnAppPkt->decapsulate());
            packet->setControlInfo(macCtx);

            EV << "Received packet: (" << packet->getClassName() << ")" << packet->getName() << "\n";

            processPacket(packet);

            delete ccnAppPkt;
            delete packet;
//
//
//        if (packet->getRouterID() == router->getRouterID()) {
//            EV << "This packet is from ourselves, discarding.\n";
//            delete message;
//        } else {
//            processPacket(packet);
//        }
        }


    }
//
void OSPFN::MessageHandler::handleTimer(OSPFNTimer* timer) {
    switch (timer->getTimerKind()) {
        case INTERFACE_HELLO_TIMER:
        {
            OSPFN::Interface* intf;
            if (! (intf = reinterpret_cast <OSPFN::Interface*> (timer->getContextPointer()))) {
                // should not reach this point
                EV << "Discarding invalid InterfaceHelloTimer.\n";
                delete timer;
            } else {
          //     printEvent("Hello Timer expired", intf);
                intf->processEvent(OSPFN::Interface::HELLO_TIMER);
            }
        }
        break;
        case INTERFACE_WAIT_TIMER:
        {
            OSPFN::Interface* intf;
            if (! (intf = reinterpret_cast <OSPFN::Interface*> (timer->getContextPointer()))) {
                // should not reach this point
                EV << "Discarding invalid InterfaceWaitTimer.\n";
                delete timer;
            } else {
                //     printEvent("Wait Timer expired", intf);
                intf->processEvent(OSPFN::Interface::WAIT_TIMER);
            }
        }
        break;
        case INTERFACE_ACKNOWLEDGEMENT_TIMER:
        {
            OSPFN::Interface* intf;
            if (! (intf = reinterpret_cast <OSPFN::Interface*> (timer->getContextPointer()))) {
                // should not reach this point
                EV << "Discarding invalid InterfaceAcknowledgementTimer.\n";
                delete timer;
            } else {
                //       printEvent("Acknowledgement Timer expired", intf);
                intf->processEvent(OSPFN::Interface::ACKNOWLEDGEMENT_TIMER);
            }
        }
        break;
        case NEIGHBOR_INACTIVITY_TIMER:
        {
            OSPFN::Neighbor* neighbor;
            if (! (neighbor = reinterpret_cast <OSPFN::Neighbor*> (timer->getContextPointer()))) {
                // should not reach this point
                EV << "Discarding invalid NeighborInactivityTimer.\n";
                delete timer;
            } else {
//                    printEvent("Inactivity Timer expired", neighbor->getInterface(), neighbor);
//                    neighbor->processEvent(OSPFN::Neighbor::INACTIVITY_TIMER);
            }
        }
        break;
        case NEIGHBOR_POLL_TIMER:
        {
            OSPFN::Neighbor* neighbor;
            if (! (neighbor = reinterpret_cast <OSPFN::Neighbor*> (timer->getContextPointer()))) {
                // should not reach this point
                EV << "Discarding invalid NeighborInactivityTimer.\n";
                delete timer;
            } else {
//                    printEvent("Poll Timer expired", neighbor->getInterface(), neighbor);
//                    neighbor->processEvent(OSPFN::Neighbor::POLL_TIMER);
            }
        }
        break;
        case NEIGHBOR_DD_RETRANSMISSION_TIMER:
        {
            OSPFN::Neighbor* neighbor;
            if (! (neighbor = reinterpret_cast <OSPFN::Neighbor*> (timer->getContextPointer()))) {
                // should not reach this point
                EV << "Discarding invalid NeighborDDRetransmissionTimer.\n";
                delete timer;
            } else {
//                    printEvent("Database Description Retransmission Timer expired", neighbor->getInterface(), neighbor);
//                    neighbor->processEvent(OSPFN::Neighbor::DD_RETRANSMISSION_TIMER);
            }
        }
        break;
        case NEIGHBOR_UPDATE_RETRANSMISSION_TIMER:
        {
            OSPFN::Neighbor* neighbor;
            if (! (neighbor = reinterpret_cast <OSPFN::Neighbor*> (timer->getContextPointer()))) {
                // should not reach this point
                EV << "Discarding invalid NeighborUpdateRetransmissionTimer.\n";
                delete timer;
            } else {
//                    printEvent("Update Retransmission Timer expired", neighbor->getInterface(), neighbor);
//                    neighbor->processEvent(OSPFN::Neighbor::UPDATE_RETRANSMISSION_TIMER);
            }
        }
        break;
        case NEIGHBOR_REQUEST_RETRANSMISSION_TIMER:
        {
            OSPFN::Neighbor* neighbor;
            if (! (neighbor = reinterpret_cast <OSPFN::Neighbor*> (timer->getContextPointer()))) {
                // should not reach this point
                EV << "Discarding invalid NeighborRequestRetransmissionTimer.\n";
                delete timer;
            } else {
//                    printEvent("Request Retransmission Timer expired", neighbor->getInterface(), neighbor);
//                    neighbor->processEvent(OSPFN::Neighbor::REQUEST_RETRANSMISSION_TIMER);
            }
        }
        break;
        case DATABASE_AGE_TIMER:
        {
            //      printEvent("Ageing the database");
            //    router->ageDatabase();
        }
        break;
        default: break;
    }
}
//
//void OSPFN::MessageHandler::processPacket(OSPFPacket* packet, OSPFN::Interface* unused1, OSPFN::Neighbor* unused2)
void OSPFN::MessageHandler::processPacket(OSPFNPacket* packet ){//, Interface* unused1 = NULL, Neighbor* unused2 = NULL) {

    OSPFPacketType packetType = static_cast<OSPFPacketType> (packet->getType());

    if (packet->getVersion() == 2) {
        switch (packetType) {
        case OSPFN_HELLO_PACKET:
            helloHandler.processPacket(packet);
            break;
        case OSPFN_DATABASE_DESCRIPTION_PACKET:
   //         if (neighbor != NULL) {
                ddHandler.processPacket(packet);
     //       }
            break;
        case OSPFN_LINKSTATE_REQUEST_PACKET:
//            if (neighbor != NULL) {
                lsRequestHandler.processPacket(packet);//, intf, neighbor);
//            }
            break;
        case OSPFN_LINKSTATE_UPDATE_PACKET:
//            if (neighbor != NULL) {
//                lsUpdateHandler.processPacket(packet, intf, neighbor);
//            }
            break;
        case OSPFN_LINKSTATE_ACKNOWLEDGEMENT_PACKET:
//            if (neighbor != NULL) {
                lsAckHandler.processPacket(packet);//, intf, neighbor);
//            }
            break;
        default:
            break;
        }
    }
}


// see RFC 2328 8.2

// packet version must be OSPF version 2
//    if (packet->getVersion() == 2) {
//        IPv4ControlInfo* controlInfo = check_and_cast<IPv4ControlInfo *> (packet->getControlInfo());
//        int interfaceId = controlInfo->getInterfaceId();
//        OSPFN::AreaID areaID = packet->getAreaID();
//        OSPFN::Area* area = router->getAreaByID(areaID);
//
//        if (area != NULL) {
//            // packet Area ID must either match the Area ID of the receiving interface or...
//            OSPFN::Interface* intf = area->getInterface(interfaceId);
//
//            if (intf == NULL) {
//                // it must be the backbone area and...
//                if (areaID == BACKBONE_AREAID) {
//                    if (router->getAreaCount() > 1) {
//                        // it must be a virtual link and the source router's router ID must be the endpoint of this virtual link and...
//                        intf = area->findVirtualLink(packet->getRouterID());
//
//                        if (intf != NULL) {
//                            OSPFN::Area* virtualLinkTransitArea = router->getAreaByID(intf->getTransitAreaID());
//
//                            if (virtualLinkTransitArea != NULL) {
//                                // the receiving interface must attach to the virtual link's configured transit area
//                                OSPFN::Interface* virtualLinkInterface = virtualLinkTransitArea->getInterface(interfaceId);
//
//                                if (virtualLinkInterface == NULL) {
//                                    intf = NULL;
//                                }
//                            } else {
//                                intf = NULL;
//                            }
//                        }
//                    }
//                }
//            }
//            if (intf != NULL) {
//                IPv4Address destinationAddress = controlInfo->getDestAddr();
//                IPv4Address allDRouters = IPv4Address::ALL_OSPF_DESIGNATED_ROUTERS_MCAST;
//                OSPFN::Interface::InterfaceStateType interfaceState = intf->getState();
//
//                // if destination address is ALL_D_ROUTERS the receiving interface must be in DesignatedRouter or Backup state
//                if (
//                    ((destinationAddress == allDRouters) &&
//                     (
//                      (interfaceState == OSPFN::Interface::DESIGNATED_ROUTER_STATE) ||
//                      (interfaceState == OSPFN::Interface::BACKUP_STATE)
//                     )
//                    ) ||
//                    (destinationAddress != allDRouters)
//                   )
//                {
//                    // packet authentication
//                    if (authenticatePacket(packet)) {
//                        OSPFPacketType packetType = static_cast<OSPFPacketType> (packet->getType());
//                        OSPFN::Neighbor* neighbor = NULL;
//
//                        // all packets except HelloPackets are sent only along adjacencies, so a Neighbor must exist
//                        if (packetType != HELLO_PACKET) {
//                            switch (intf->getType()) {
//                                case OSPFN::Interface::BROADCAST:
//                                case OSPFN::Interface::NBMA:
//                                case OSPFN::Interface::POINTTOMULTIPOINT:
//                                    neighbor = intf->getNeighborByAddress(controlInfo->getSrcAddr());
//                                    break;
//                                case OSPFN::Interface::POINTTOPOINT:
//                                case OSPFN::Interface::VIRTUAL:
//                                    neighbor = intf->getNeighborByID(packet->getRouterID());
//                                    break;
//                                default: break;
//                            }
//                        }
//                        switch (packetType) {
//                            case HELLO_PACKET:
//                                helloHandler.processPacket(packet, intf);
//                                break;
//                            case DATABASE_DESCRIPTION_PACKET:
//                                if (neighbor != NULL) {
//                                    ddHandler.processPacket(packet, intf, neighbor);
//                                }
//                                break;
//                            case LINKSTATE_REQUEST_PACKET:
//                                if (neighbor != NULL) {
//                                    lsRequestHandler.processPacket(packet, intf, neighbor);
//                                }
//                                break;
//                            case LINKSTATE_UPDATE_PACKET:
//                                if (neighbor != NULL) {
//                                    lsUpdateHandler.processPacket(packet, intf, neighbor);
//                                }
//                                break;
//                            case LINKSTATE_ACKNOWLEDGEMENT_PACKET:
//                                if (neighbor != NULL) {
//                                    lsAckHandler.processPacket(packet, intf, neighbor);
//                                }
//                                break;
//                            default: break;
//                        }
//                    }
//                }
//            }
//        }
//    }
//    delete packet;

//
//void OSPFN::MessageHandler::sendPacket(OSPFNPrefixAdv* packet){
//
//    ospfModule->send(packet, "ipOut");
//
//}
//

void OSPFN::MessageHandler::send(cPacket* packet) {
    ospfModule->send(packet, "ipOut");
}

void OSPFN::MessageHandler::sendPacket(OSPFNPacket* packet, string destination, int outputIfIndex, short ttl)
{

//    IPv4ControlInfo *ipControlInfo = new IPv4ControlInfo();
//    ipControlInfo->setProtocol(IP_PROT_OSPF);
//    ipControlInfo->setDestAddr(destination);
//    ipControlInfo->setTimeToLive(ttl);
//    ipControlInfo->setInterfaceId(outputIfIndex);
//
//    packet->setControlInfo(ipControlInfo);
    switch (packet->getType()) {
        case OSPFN_HELLO_PACKET:
            {
                packet->setKind(HELLO_PACKET);
                packet->setName("OSPF_HelloPacket");

                OSPFHelloPacket* helloPacket = check_and_cast<OSPFHelloPacket*> (packet);
               // printHelloPacket(helloPacket, destination, outputIfIndex);
            }
            break;
        case OSPFN_DATABASE_DESCRIPTION_PACKET:
            {
                packet->setKind(DATABASE_DESCRIPTION_PACKET);
                packet->setName("OSPF_DDPacket");

                OSPFDatabaseDescriptionPacket* ddPacket = check_and_cast<OSPFDatabaseDescriptionPacket*> (packet);
              //  printDatabaseDescriptionPacket(ddPacket, destination, outputIfIndex);
            }
            break;
        case OSPFN_LINKSTATE_REQUEST_PACKET:
            {
                packet->setKind(LINKSTATE_REQUEST_PACKET);
                packet->setName("OSPF_LSReqPacket");

                OSPFLinkStateRequestPacket* requestPacket = check_and_cast<OSPFLinkStateRequestPacket*> (packet);
               // printLinkStateRequestPacket(requestPacket, destination, outputIfIndex);
            }
            break;
        case OSPFN_LINKSTATE_UPDATE_PACKET:
            {
                packet->setKind(LINKSTATE_UPDATE_PACKET);
                packet->setName("OSPF_LSUpdPacket");

                OSPFLinkStateUpdatePacket* updatePacket = check_and_cast<OSPFLinkStateUpdatePacket*> (packet);
           //     printLinkStateUpdatePacket(updatePacket, destination, outputIfIndex);
            }
            break;
        case OSPFN_LINKSTATE_ACKNOWLEDGEMENT_PACKET:
            {
                packet->setKind(LINKSTATE_ACKNOWLEDGEMENT_PACKET);
                packet->setName("OSPF_LSAckPacket");

                OSPFLinkStateAcknowledgementPacket* ackPacket = check_and_cast<OSPFLinkStateAcknowledgementPacket*> (packet);
             //   printLinkStateAcknowledgementPacket(ackPacket, destination, outputIfIndex);
            }
            break;
        default: break;
    }

    ospfModule->send(packet, "ipOut");
}
//
void OSPFN::MessageHandler::clearTimer(OSPFNTimer* timer) {
    ospfModule->cancelEvent(timer);
}

void OSPFN::MessageHandler::startTimer(OSPFNTimer* timer, simtime_t delay) {

    ospfModule->scheduleAt(simTime() + delay, timer);
}

//
//void OSPFN::MessageHandler::printEvent(const char* eventString,
//        const OSPFN::Interface* onInterface,
//        const OSPFN::Neighbor* forNeighbor /*= NULL*/) const {
//    EV << eventString;
//    if ((onInterface != NULL) || (forNeighbor != NULL)) {
//        EV << ": ";
//    }
////    if (forNeighbor != NULL) {
////        EV << "neighbor["
////           << forNeighbor->getNeighborID()
////           << "] (state: "
////           << forNeighbor->getStateString(forNeighbor->getState())
////           << "); ";
////    }
//    if (onInterface != NULL) {
//        EV << "interface[" << static_cast<short>(onInterface->getIfIndex())
//                  << "] ";
//        switch (onInterface->getType()) {
//        case OSPFN::Interface::POINTTOPOINT:
//            EV << "(PointToPoint)";
//            break;
//        case OSPFN::Interface::BROADCAST:
//            EV << "(Broadcast)";
//            break;
//        case OSPFN::Interface::NBMA:
//            EV << "(NBMA).\n";
//            break;
//        case OSPFN::Interface::POINTTOMULTIPOINT:
//            EV << "(PointToMultiPoint)";
//            break;
//        case OSPFN::Interface::VIRTUAL:
//            EV << "(Virtual)";
//            break;
//        default:
//            EV << "(Unknown)";
//            break;
//        }
//        EV << " (state: "
//                  << onInterface->getStateString(onInterface->getState())
//                  << ")";
//    }
//    EV << ".\n";
//}
//
//void OSPFN::MessageHandler::printHelloPacket(const OSPFHelloPacket* helloPacket, IPv4Address destination, int outputIfIndex) const
//{
//    EV << "Sending Hello packet to " << destination << " on interface[" << outputIfIndex << "] with contents:\n";
//    EV << "  netMask=" << helloPacket->getNetworkMask() << "\n";
//    EV << "  DR=" << helloPacket->getDesignatedRouter() << "\n";
//    EV << "  BDR=" << helloPacket->getBackupDesignatedRouter() << "\n";
//
//    EV << "  neighbors:\n";
//
//    unsigned int neighborCount = helloPacket->getNeighborArraySize();
//    for (unsigned int i = 0; i < neighborCount; i++) {
//        EV << "    " << helloPacket->getNeighbor(i) << "\n";
//    }
//}
//
//void OSPFN::MessageHandler::printDatabaseDescriptionPacket(const OSPFDatabaseDescriptionPacket* ddPacket, IPv4Address destination, int outputIfIndex) const
//{
//    EV << "Sending Database Description packet to " << destination << " on interface[" << outputIfIndex << "] with contents:\n";
//
//    const OSPFDDOptions& ddOptions = ddPacket->getDdOptions();
//    EV << "  ddOptions="
//       << ((ddOptions.I_Init) ? "I " : "_ ")
//       << ((ddOptions.M_More) ? "M " : "_ ")
//       << ((ddOptions.MS_MasterSlave) ? "MS" : "__")
//       << "\n";
//    EV << "  seqNumber=" << ddPacket->getDdSequenceNumber() << "\n";
//    EV << "  LSA headers:\n";
//
//    unsigned int lsaCount = ddPacket->getLsaHeadersArraySize();
//    for (unsigned int i = 0; i < lsaCount; i++) {
//        EV << "    ";
//        printLSAHeader(ddPacket->getLsaHeaders(i), ev.getOStream());
//        EV << "\n";
//    }
//}
//
//void OSPFN::MessageHandler::printLinkStateRequestPacket(const OSPFLinkStateRequestPacket* requestPacket, IPv4Address destination, int outputIfIndex) const
//{
//    EV << "Sending Link State Request packet to " << destination << " on interface[" << outputIfIndex << "] with requests:\n";
//
//    unsigned int requestCount = requestPacket->getRequestsArraySize();
//    for (unsigned int i = 0; i < requestCount; i++) {
//        const LSARequest& request = requestPacket->getRequests(i);
//        EV << "  type=" << request.lsType
//           << ", LSID=" << request.linkStateID
//           << ", advertisingRouter=" << request.advertisingRouter << "\n";
//    }
//}
//
//void OSPFN::MessageHandler::printLinkStateUpdatePacket(const OSPFLinkStateUpdatePacket* updatePacket, IPv4Address destination, int outputIfIndex) const
//{
//    EV << "Sending Link State Update packet to " << destination << " on interface[" << outputIfIndex << "] with updates:\n";
//
//    unsigned int i = 0;
//    unsigned int updateCount = updatePacket->getRouterLSAsArraySize();
//
//    for (i = 0; i < updateCount; i++) {
//        const OSPFRouterLSA& lsa = updatePacket->getRouterLSAs(i);
//        EV << "  ";
//        printLSAHeader(lsa.getHeader(), ev.getOStream());
//        EV << "\n";
//
//        EV << "  bits="
//           << ((lsa.getV_VirtualLinkEndpoint()) ? "V " : "_ ")
//           << ((lsa.getE_ASBoundaryRouter()) ? "E " : "_ ")
//           << ((lsa.getB_AreaBorderRouter()) ? "B" : "_")
//           << "\n";
//        EV << "  links:\n";
//
//        unsigned int linkCount = lsa.getLinksArraySize();
//        for (unsigned int j = 0; j < linkCount; j++) {
//            const Link& link = lsa.getLinks(j);
//            EV << "    ID=" << link.getLinkID();
//            EV << ", data="
//               << link.getLinkData() << " (" << IPv4Address(link.getLinkData()) << ")"
//               << ", type=";
//            switch (link.getType()) {
//                case POINTTOPOINT_LINK:  EV << "PointToPoint";   break;
//                case TRANSIT_LINK:       EV << "Transit";        break;
//                case STUB_LINK:          EV << "Stub";           break;
//                case VIRTUAL_LINK:       EV << "Virtual";        break;
//                default:                 EV << "Unknown";        break;
//            }
//            EV << ", cost=" << link.getLinkCost() << "\n";
//        }
//    }
//
//    updateCount = updatePacket->getNetworkLSAsArraySize();
//    for (i = 0; i < updateCount; i++) {
//        const OSPFNetworkLSA& lsa = updatePacket->getNetworkLSAs(i);
//        EV << "  ";
//        printLSAHeader(lsa.getHeader(), ev.getOStream());
//        EV << "\n";
//
//        EV << "  netMask=" << lsa.getNetworkMask() << "\n";
//        EV << "  attachedRouters:\n";
//
//        unsigned int routerCount = lsa.getAttachedRoutersArraySize();
//        for (unsigned int j = 0; j < routerCount; j++) {
//            EV << "    " << lsa.getAttachedRouters(j) << "\n";
//        }
//    }
//
//    updateCount = updatePacket->getSummaryLSAsArraySize();
//    for (i = 0; i < updateCount; i++) {
//        const OSPFSummaryLSA& lsa = updatePacket->getSummaryLSAs(i);
//        EV << "  ";
//        printLSAHeader(lsa.getHeader(), ev.getOStream());
//        EV << "\n";
//        EV << "  netMask=" << lsa.getNetworkMask() << "\n";
//        EV << "  cost=" << lsa.getRouteCost() << "\n";
//    }
//
//    updateCount = updatePacket->getAsExternalLSAsArraySize();
//    for (i = 0; i < updateCount; i++) {
//        const OSPFASExternalLSA& lsa = updatePacket->getAsExternalLSAs(i);
//        EV << "  ";
//        printLSAHeader(lsa.getHeader(), ev.getOStream());
//        EV << "\n";
//
//        const OSPFASExternalLSAContents& contents = lsa.getContents();
//        EV << "  netMask=" <<  contents.getNetworkMask() << "\n";
//        EV << "  bits=" << ((contents.getE_ExternalMetricType()) ? "E\n" : "_\n");
//        EV << "  cost=" << contents.getRouteCost() << "\n";
//        EV << "  forward=" << contents.getForwardingAddress() << "\n";
//    }
//}
//
//void OSPFN::MessageHandler::printLinkStateAcknowledgementPacket(const OSPFLinkStateAcknowledgementPacket* ackPacket, IPv4Address destination, int outputIfIndex) const
//{
//    EV << "Sending Link State Acknowledgement packet to " << destination << " on interface[" << outputIfIndex << "] with acknowledgements:\n";
//
//    unsigned int lsaCount = ackPacket->getLsaHeadersArraySize();
//    for (unsigned int i = 0; i < lsaCount; i++) {
//        EV << "    ";
//        printLSAHeader(ackPacket->getLsaHeaders(i), ev.getOStream());
//        EV << "\n";
//    }
//}

