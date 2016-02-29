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

#include "OSPFNLinkStateRequestHandler.h"

#include "OSPFNNeighbor.h"
#include "OSPFNRouter.h"


OSPFN::LinkStateRequestHandler::LinkStateRequestHandler(OSPFN::Router* containingRouter) :
    OSPFN::IMessageHandler(containingRouter)
{
}

void OSPFN::LinkStateRequestHandler::processPacket(OSPFNPacket* packet)//, OSPFN::Interface* intf, OSPFN* neighbor)
{
    //router->getMessageHandler()->printEvent("Link State Request packet received", intf, neighbor);

    Ieee802Ctrl *macCtx = check_and_cast<Ieee802Ctrl *>( packet->removeControlInfo());

       MACAddress srcAddress, destAddress;
       srcAddress = macCtx->getSrc();
       destAddress = macCtx->getDest();

       Interface* intf = router->getInterfaceByMac(destAddress);
       if (intf == NULL)
           opp_error("The interface for mac cannot be found.");

       //    std::cerr << " OSPFN::HelloHandler::processPacket: " << std::endl;
       //    std::cerr << macCtx->getSrc() << " " << macCtx->getDest() ;
       //    std::cerr << std::endl;

       OSPFNLinkStateRequestPacket* lsaReqPacket = check_and_cast<OSPFNLinkStateRequestPacket*>(packet);
       bool shouldRebuildRoutingTable = false;
       OSPFN::Neighbor* neighbor = NULL;

       OSPFN::Interface::OSPFInterfaceType interfaceType = intf->getType();

       /***** ORIGINAL  *******/

       // router->getMessageHandler()->printEvent("Database Description packet received", intf, neighbor);
   //    OSPFDatabaseDescriptionPacket* ddPacket = check_and_cast<OSPFDatabaseDescriptionPacket*> (packet);
       //   OSPFN::NeighborStateType neighborState = neighbor->getState();
   //    if ((ddPacket->getInterfaceMTU() <= intf->getMTU()) &&
   //        (neighborState > OSPFN::ATTEMPT_STATE))
   //    {
       /* If the receiving interface connects to a broadcast, Point-to-
        MultiPoint or NBMA network the source is identified by the IP
        source address found in the Hello's IP header.
        */
       if ((interfaceType == OSPFN::Interface::BROADCAST)
               || (interfaceType == OSPFN::Interface::POINTTOMULTIPOINT)
               || (interfaceType == OSPFN::Interface::NBMA)) {
           neighbor = intf->getNeighborByAddress(srcAddress);
       } else {
           /* If the receiving interface connects to a point-to-point link or a virtual link,
            the source is identified by the Router ID found in the Hello's OSPF packet header.
            */
           neighbor = intf->getNeighborByID(lsaReqPacket->getRouterID());
       }

       if (neighbor != NULL) {

       }
    OSPFN::NeighborStateType neighborState = neighbor->getState();

    bool rebuildForwardingTable = false;

    if ((neighborState == OSPFN::EXCHANGE_STATE) ||
        (neighborState == OSPFN::LOADING_STATE) ||
        (neighborState == OSPFN::FULL_STATE) ||
        (neighborState == OSPFN::EXCHANGE_START_STATE))

    {

//         if (neighbor->getState() >= OSPFN::EXCHANGE_START_STATE){

             int lsaCount = lsaReqPacket->getLSAsArraySize();
             std::vector<chunk_t> lsa_req_v;
             for (int i = 0; i < lsaCount; i++) {
                 lsa_req_v.push_back(lsaReqPacket->getLSAs(i));

                // intf->addNewPrefixFromNeighbor(lsaReqPacket->getLSAs(i), srcAddress, destAddress,lsaReqPacket->getHops(i)+1);
                // rebuildForwardingTable = true;
             }
//         }


        OSPFNLinkStateAcknowledgementPacket* lsaReply = intf->createLinkStateAckPacket(lsa_req_v);

        if (lsaReply != NULL) {
             intf->sendOSPFNPacket(lsaReply,neighbor->getNeighborID());
        }
    }

    if(rebuildForwardingTable)
        intf->getRouter()->rebuildForwardingTable();

//        OSPFLinkStateRequestPacket* lsRequestNPacket = check_and_cast<OSPFNLinkStateRequestPacket*> (packet);
//
//        unsigned long requestCount = lsRequestPacket->getRequestsArraySize();
//        bool error = false;
//        std::vector<OSPFLSA*> lsas;
//
//        EV << "  Processing packet contents:\n";
//
//        for (unsigned long i = 0; i < requestCount; i++) {
//            LSARequest& request = lsRequestPacket->getRequests(i);
//            OSPFN::LSAKeyType lsaKey;
//
//            EV << "    LSARequest: type=" << request.lsType
//               << ", LSID=" << request.linkStateID
//               << ", advertisingRouter=" << request.advertisingRouter
//               << "\n";
//
//            lsaKey.linkStateID = request.linkStateID;
//            lsaKey.advertisingRouter = request.advertisingRouter;
//
//            OSPFLSA* lsaInDatabase = router->findLSA(static_cast<LSAType> (request.lsType), lsaKey, intf->getArea()->getAreaID());
//
//            if (lsaInDatabase != NULL) {
//                lsas.push_back(lsaInDatabase);
//            } else {
//                error = true;
//                neighbor->processEvent(OSPFN::BAD_LINK_STATE_REQUEST);
//                break;
//            }
//        }
//
//        if (!error) {
//            int updatesCount = lsas.size();
//            int ttl = (intf->getType() == OSPFN::Interface::VIRTUAL) ? VIRTUAL_LINK_TTL : 1;
//            OSPFN::MessageHandler* messageHandler = router->getMessageHandler();
//
//            for (int j = 0; j < updatesCount; j++) {
//                OSPFLinkStateUpdatePacket* updatePacket = intf->createUpdatePacket(lsas[j]);
//                if (updatePacket != NULL) {
//                    if (intf->getType() == OSPFN::Interface::BROADCAST) {
//                        if ((intf->getState() == OSPFN::Interface::DESIGNATED_ROUTER_STATE) ||
//                            (intf->getState() == OSPFN::Interface::BACKUP_STATE) ||
//                            (intf->getDesignatedRouter() == OSPFN::NULL_DESIGNATEDROUTERID))
//                        {
//                            messageHandler->sendPacket(updatePacket, IPv4Address::ALL_OSPF_ROUTERS_MCAST, intf->getIfIndex(), ttl);
//                        } else {
//                            messageHandler->sendPacket(updatePacket, IPv4Address::ALL_OSPF_DESIGNATED_ROUTERS_MCAST, intf->getIfIndex(), ttl);
//                        }
//                    } else {
//                        if (intf->getType() == OSPFN::Interface::POINTTOPOINT) {
//                            messageHandler->sendPacket(updatePacket, IPv4Address::ALL_OSPF_ROUTERS_MCAST, intf->getIfIndex(), ttl);
//                        } else {
//                            messageHandler->sendPacket(updatePacket, neighbor->getAddress(), intf->getIfIndex(), ttl);
//                        }
//                    }
//
//                }
//            }
//            // These update packets should not be placed on retransmission lists
//        }
    }

