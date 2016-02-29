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


#include "OSPFNLinkStateAcknowledgementHandler.h"

#include "OSPFNRouter.h"


OSPFN::LinkStateAcknowledgementHandler::LinkStateAcknowledgementHandler(OSPFN::Router* containingRouter) :
    OSPFN::IMessageHandler(containingRouter)
{
}

void OSPFN::LinkStateAcknowledgementHandler::processPacket(OSPFNPacket* packet)//, OSPFN::Interface* intf, OSPFN::Neighbor* neighbor)
{
//    router->getMessageHandler()->printEvent("Link State Acknowledgement packet received", intf, neighbor);

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

       OSPFNLinkStateAcknowledgementPacket* lsAckPacket = check_and_cast<OSPFNLinkStateAcknowledgementPacket*>(packet);
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
           neighbor = intf->getNeighborByID(lsAckPacket->getRouterID());
       }

       bool rebuildForwardingTable = false;
       if (neighbor != NULL) {

           if (neighbor->getState() >= OSPFN::EXCHANGE_START_STATE){

               int lsaCount = lsAckPacket->getLSAsArraySize();
               for (int i = 0; i < lsaCount; i++) {
                   intf->addNewPrefixFromNeighbor(lsAckPacket->getLSAs(i), srcAddress, destAddress, lsAckPacket->getHops(i)+1);
                   rebuildForwardingTable = true;

               }
           }
       }

       if(rebuildForwardingTable)
           intf->getRouter()->rebuildForwardingTable();

//    if (neighbor->getState() >= OSPFN::Neighbor::EXCHANGE_STATE) {
//        OSPFLinkStateAcknowledgementPacket* lsAckPacket = check_and_cast<OSPFLinkStateAcknowledgementPacket*> (packet);
//
//        int lsaCount = lsAckPacket->getLsaHeadersArraySize();
//
//        EV << "  Processing packet contents:\n";
//
//        for (int i = 0; i < lsaCount; i++) {
//            OSPFLSAHeader& lsaHeader = lsAckPacket->getLsaHeaders(i);
//            OSPFLSA* lsaOnRetransmissionList;
//            OSPFN::LSAKeyType lsaKey;
//
//            EV << "    ";
//            printLSAHeader(lsaHeader, ev.getOStream());
//            EV << "\n";
//
//            lsaKey.linkStateID = lsaHeader.getLinkStateID();
//            lsaKey.advertisingRouter = lsaHeader.getAdvertisingRouter();
//
//            if ((lsaOnRetransmissionList = neighbor->findOnRetransmissionList(lsaKey)) != NULL) {
//                if (operator==(lsaHeader, lsaOnRetransmissionList->getHeader())) {
//                    neighbor->removeFromRetransmissionList(lsaKey);
//                } else {
//                    EV << "Got an Acknowledgement packet for an unsent Update packet.\n";
//                }
//            }
//        }
//        if (neighbor->isLinkStateRetransmissionListEmpty()) {
//            neighbor->clearUpdateRetransmissionTimer();
//        }
//    }
}

