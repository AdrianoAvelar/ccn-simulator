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

#include "OSPFNHelloHandler.h"

//#include "IPv4ControlInfo.h"
//#include "OSPFArea.h"
#include "OSPFNInterface.h"
#include "OSPFNNeighbor.h"
#include "OSPFNRouter.h"
#include "OSPFNPacket_m.h"

OSPFN::HelloHandler::HelloHandler(OSPFN::Router* containingRouter) :
    OSPFN::IMessageHandler(containingRouter)
{
}

void OSPFN::HelloHandler::processPacket(OSPFNPacket* packet){//, OSPFN::Interface* iface, OSPFN::Neighbor* unused){

    Ieee802Ctrl *macCtx = check_and_cast<Ieee802Ctrl *>(packet->removeControlInfo());

    MACAddress srcAddress, destAddress;
    srcAddress = macCtx->getSrc();
    destAddress =  macCtx->getDest();

    Interface* intf = router->getInterfaceByMac(destAddress);
    if(intf == NULL){
        router->dumpInterfaces();
        opp_error("The interface for mac: %s cannot be found in %s.",
                destAddress.str().c_str(),
                router->getMessageHandler()->getOSPFNModule()->getParentModule()->getName());
    }

    OSPFNHelloPacket* helloPacket = check_and_cast<OSPFNHelloPacket*> (packet);
    bool shouldRebuildRoutingTable = false;
    OSPFN::Neighbor* neighbor = NULL;

//    std::cerr << " OSPFN::HelloHandler::processPacket: " << std::endl;
//    std::cerr << macCtx->getSrc() << " " << macCtx->getDest();
//    std::cerr << std::endl;
//    std::cerr << helloPacket->getRouterID() << endl;

    OSPFN::Interface::OSPFInterfaceType interfaceType = intf->getType();

    /* If the receiving interface connects to a broadcast, Point-to-
           MultiPoint or NBMA network the source is identified by the IP
           source address found in the Hello's IP header.
         */
        if ((interfaceType == OSPFN::Interface::BROADCAST) ||
            (interfaceType == OSPFN::Interface::POINTTOMULTIPOINT) ||
            (interfaceType == OSPFN::Interface::NBMA))
        {
            neighbor = intf->getNeighborByAddress(srcAddress);
        } else {
            /* If the receiving interface connects to a point-to-point link or a virtual link,
               the source is identified by the Router ID found in the Hello's OSPF packet header.
             */
            neighbor = intf->getNeighborByID(helloPacket->getRouterID());
        }

        if (neighbor != NULL) {


            //Segundo a RFC, caso o stado seja INIT e o evento seja o RECEBIMENTO DE UM HELLO.
            //Nada muda.
//            PRINT_ERR << "Hello Received, neighbor state is :" << neighbor->getStateString(neighbor->getState());
//            opp_error("Já existe um vizinho cadastrado para esse hello");
        }else{
            shouldRebuildRoutingTable = true;
            //vizinho novo
           neighbor = new OSPFN::Neighbor(helloPacket->getRouterID());
           //neighbor->setPriority(helloPacket->getRouterPriority());

           neighbor->setNeighborID(helloPacket->getRouterID()); //Set PREFIX
//           neighbor->setAddress(srcAddress);

           neighbor->setSrcAddr(srcAddress);
           neighbor->setDestAddr(destAddress);
           //neighbor->setRouterDeadInterval(helloPacket->getRouterDeadInterval());

       //    router->getMessageHandler()->printEvent("Hello packet received", intf, neighbor);

           intf->addNeighbor(neighbor);
        }

        neighbor->processEvent(OSPFN::HELLO_RECEIVED);

        unsigned int neighborsNeighborCount = helloPacket->getNeighborArraySize();
        unsigned int i;
        /* The list of neighbors contained in the Hello Packet is
           examined.  If the router itself appears in this list, the
           neighbor state machine should be executed with the event TWOWAY_RECEIVED.
         */
        MACAddress interfaceAddress = intf->getMACAddress();

        for (i = 0; i < neighborsNeighborCount; i++) {
            if (helloPacket->getNeighbor(i) == interfaceAddress) {
                neighbor->processEvent(OSPFN::TWOWAY_RECEIVED);
                break;
            }
        }
        /* Otherwise, the neighbor state machine should
           be executed with the event ONEWAY_RECEIVED, and the processing
           of the packet stops.
         */
        if (i == neighborsNeighborCount) {
            neighbor->processEvent(OSPFN::ONEWAY_RECEIVED);
        }

//        neighbor->processEvent(OSPFN::Neighbor::HELLO_RECEIVED);
//        if ((interfaceType == OSPFN::Interface::NBMA) &&
//            (intf->getRouterPriority() == 0) &&
//            (neighbor->getState() >= OSPFN::Neighbor::INIT_STATE))
//        {
//            intf->sendHelloPacket(neighbor->getAddress());
//        }

        if (shouldRebuildRoutingTable) {
            router->rebuildForwardingTable();
        }
}

//void OSPFN::HelloHandler::processPacket(OSPFNPacket* packet, OSPFN::Interface* intf, OSPFN::Neighbor* unused)
//{

//    OSPFHelloPacket* helloPacket = check_and_cast<OSPFHelloPacket*> (packet);
//    bool shouldRebuildRoutingTable = false;
//
//    /* The values of the Network Mask, HelloInterval,
//       and RouterDeadInterval fields in the received Hello packet must
//       be checked against the values configured for the receiving
//       interface.  Any mismatch causes processing to stop and the
//       packet to be dropped.
//     */
//    if ((intf->getHelloInterval() == helloPacket->getHelloInterval()) &&
//        (intf->getRouterDeadInterval() == helloPacket->getRouterDeadInterval()))
//    {
//        OSPFN::Interface::OSPFInterfaceType interfaceType = intf->getType();
//        /* There is one exception to the above rule: on point-to-point
//           networks and on virtual links, the Network Mask in the received
//           Hello Packet should be ignored.
//         */
//        if (!((interfaceType != OSPFN::Interface::POINTTOPOINT) &&
//              (interfaceType != OSPFN::Interface::VIRTUAL) &&
//              (intf->getAddressRange().mask != helloPacket->getNetworkMask())
//             )
//           )
//        {
//            /* The setting of the E-bit found in the Hello Packet's Options field must match this area's
//               ExternalRoutingCapability.
//             */
//            if (intf->getArea()->getExternalRoutingCapability() == helloPacket->getOptions().E_ExternalRoutingCapability) {
//                IPv4ControlInfo* controlInfo = check_and_cast<IPv4ControlInfo *> (helloPacket->getControlInfo());
//                IPv4Address srcAddress = controlInfo->getSrcAddr();
//                bool neighborChanged = false;
//                bool neighborsDRStateChanged = false;
//                bool drChanged = false;
//                bool backupSeen = false;
//                OSPFN::Neighbor* neighbor;
//
//                /* If the receiving interface connects to a broadcast, Point-to-
//                   MultiPoint or NBMA network the source is identified by the IP
//                   source address found in the Hello's IP header.
//                 */
//                if ((interfaceType == OSPFN::Interface::BROADCAST) ||
//                    (interfaceType == OSPFN::Interface::POINTTOMULTIPOINT) ||
//                    (interfaceType == OSPFN::Interface::NBMA))
//                {
//                    neighbor = intf->getNeighborByAddress(srcAddress);
//                } else {
//                    /* If the receiving interface connects to a point-to-point link or a virtual link,
//                       the source is identified by the Router ID found in the Hello's OSPF packet header.
//                     */
//                    neighbor = intf->getNeighborByID(helloPacket->getRouterID());
//                }
//
//                if (neighbor != NULL) {
//                    router->getMessageHandler()->printEvent("Hello packet received", intf, neighbor);
//
//                    IPv4Address designatedAddress = neighbor->getDesignatedRouter().ipInterfaceAddress;
//                    IPv4Address backupAddress = neighbor->getBackupDesignatedRouter().ipInterfaceAddress;
//                    char newPriority = helloPacket->getRouterPriority();
//                    IPv4Address source = controlInfo->getSrcAddr();
//                    IPv4Address newDesignatedRouter = helloPacket->getDesignatedRouter();
//                    IPv4Address newBackupRouter = helloPacket->getBackupDesignatedRouter();
//                    OSPFN::DesignatedRouterID dRouterID;
//
//                    if ((interfaceType == OSPFN::Interface::VIRTUAL) &&
//                        (neighbor->getState() == OSPFN::Neighbor::DOWN_STATE))
//                    {
//                        neighbor->setPriority(helloPacket->getRouterPriority());
//                        neighbor->setRouterDeadInterval(helloPacket->getRouterDeadInterval());
//                    }
//
//                    /* If a change in the neighbor's Router Priority field
//                       was noted, the receiving interface's state machine is
//                       scheduled with the event NEIGHBOR_CHANGE.
//                     */
//                    if (neighbor->getPriority() != newPriority) {
//                        neighborChanged = true;
//                    }
//
//                    /* If the neighbor is both declaring itself to be Designated
//                       Router(Hello Packet's Designated Router field = Neighbor IP
//                       address) and the Backup Designated Router field in the
//                       packet is equal to 0.0.0.0 and the receiving interface is in
//                       state Waiting, the receiving interface's state machine is
//                       scheduled with the event BACKUP_SEEN.
//                     */
//                    if ((newDesignatedRouter == source) &&
//                        (newBackupRouter == OSPFN::NULL_IPV4ADDRESS) &&
//                        (intf->getState() == OSPFN::Interface::WAITING_STATE))
//                    {
//                        backupSeen = true;
//                    } else {
//                        /* Otherwise, if the neighbor is declaring itself to be Designated Router and it
//                           had not previously, or the neighbor is not declaring itself
//                           Designated Router where it had previously, the receiving
//                           interface's state machine is scheduled with the event
//                           NEIGHBOR_CHANGE.
//                         */
//                        if (((newDesignatedRouter == source) &&
//                             (newDesignatedRouter != designatedAddress)) ||
//                            ((newDesignatedRouter != source) &&
//                             (source == designatedAddress)))
//                        {
//                            neighborChanged = true;
//                            neighborsDRStateChanged = true;
//                        }
//                    }
//
//                    /* If the neighbor is declaring itself to be Backup Designated
//                       Router(Hello Packet's Backup Designated Router field =
//                       Neighbor IP address) and the receiving interface is in state
//                       Waiting, the receiving interface's state machine is
//                       scheduled with the event BACKUP_SEEN.
//                     */
//                    if ((newBackupRouter == source) &&
//                        (intf->getState() == OSPFN::Interface::WAITING_STATE))
//                    {
//                        backupSeen = true;
//                    } else {
//                        /* Otherwise, if the neighbor is declaring itself to be Backup Designated Router
//                           and it had not previously, or the neighbor is not declaring
//                           itself Backup Designated Router where it had previously, the
//                           receiving interface's state machine is scheduled with the
//                           event NEIGHBOR_CHANGE.
//                         */
//                        if (((newBackupRouter == source) &&
//                             (newBackupRouter != backupAddress)) ||
//                            ((newBackupRouter != source) &&
//                             (source == backupAddress)))
//                        {
//                            neighborChanged = true;
//                        }
//                    }
//
//                    neighbor->setNeighborID(helloPacket->getRouterID());
//                    neighbor->setPriority(newPriority);
//                    neighbor->setAddress(srcAddress);
//                    dRouterID.routerID = newDesignatedRouter;
//                    dRouterID.ipInterfaceAddress = newDesignatedRouter;
//                    if (newDesignatedRouter != designatedAddress) {
//                        designatedAddress = dRouterID.ipInterfaceAddress;
//                        drChanged = true;
//                    }
//                    neighbor->setDesignatedRouter(dRouterID);
//                    dRouterID.routerID = newBackupRouter;
//                    dRouterID.ipInterfaceAddress = newBackupRouter;
//                    if (newBackupRouter != backupAddress) {
//                        backupAddress = dRouterID.ipInterfaceAddress;
//                        drChanged = true;
//                    }
//                    neighbor->setBackupDesignatedRouter(dRouterID);
//                    if (drChanged) {
//                        neighbor->setupDesignatedRouters(false);
//                    }
//
//                    /* If the neighbor router's Designated or Backup Designated Router
//                       has changed it's necessary to look up the Router IDs belonging to the
//                       new addresses.
//                     */
//                    if (!neighbor->designatedRoutersAreSetUp()) {
//                        OSPFN::Neighbor* designated = intf->getNeighborByAddress(designatedAddress);
//                        OSPFN::Neighbor* backup = intf->getNeighborByAddress(backupAddress);
//
//                        if (designated != NULL) {
//                            dRouterID.routerID = designated->getNeighborID();
//                            dRouterID.ipInterfaceAddress = designated->getAddress();
//                            neighbor->setDesignatedRouter(dRouterID);
//                        }
//                        if (backup != NULL) {
//                            dRouterID.routerID = backup->getNeighborID();
//                            dRouterID.ipInterfaceAddress = backup->getAddress();
//                            neighbor->setBackupDesignatedRouter(dRouterID);
//                        }
//                        if ((designated != NULL) && (backup != NULL)) {
//                            neighbor->setupDesignatedRouters(true);
//                        }
//                    }
//                } else {
//                    OSPFN::DesignatedRouterID dRouterID;
//                    bool designatedSetUp = false;
//                    bool backupSetUp = false;
//
//                    neighbor = new OSPFN::Neighbor(helloPacket->getRouterID());
//                    neighbor->setPriority(helloPacket->getRouterPriority());
//                    neighbor->setAddress(srcAddress);
//                    neighbor->setRouterDeadInterval(helloPacket->getRouterDeadInterval());
//
//                    router->getMessageHandler()->printEvent("Hello packet received", intf, neighbor);
//
//                    dRouterID.routerID = helloPacket->getDesignatedRouter();
//                    dRouterID.ipInterfaceAddress = dRouterID.routerID;
//
//                    OSPFN::Neighbor* designated = intf->getNeighborByAddress(dRouterID.ipInterfaceAddress);
//
//                    // Get the Designated Router ID from the corresponding Neighbor Object.
//                    if (designated != NULL) {
//                        if (designated->getNeighborID() != dRouterID.routerID) {
//                            dRouterID.routerID = designated->getNeighborID();
//                        }
//                        designatedSetUp = true;
//                    }
//                    neighbor->setDesignatedRouter(dRouterID);
//
//                    dRouterID.routerID = helloPacket->getBackupDesignatedRouter();
//                    dRouterID.ipInterfaceAddress = dRouterID.routerID;
//
//                    OSPFN::Neighbor* backup = intf->getNeighborByAddress(dRouterID.ipInterfaceAddress);
//
//                    // Get the Backup Designated Router ID from the corresponding Neighbor Object.
//                    if (backup != NULL) {
//                        if (backup->getNeighborID() != dRouterID.routerID) {
//                            dRouterID.routerID = backup->getNeighborID();
//                        }
//                        backupSetUp = true;
//                    }
//                    neighbor->setBackupDesignatedRouter(dRouterID);
//                    if (designatedSetUp && backupSetUp) {
//                        neighbor->setupDesignatedRouters(true);
//                    }
//                    intf->addNeighbor(neighbor);
//                }
//
//                neighbor->processEvent(OSPFN::Neighbor::HELLO_RECEIVED);
//                if ((interfaceType == OSPFN::Interface::NBMA) &&
//                    (intf->getRouterPriority() == 0) &&
//                    (neighbor->getState() >= OSPFN::Neighbor::INIT_STATE))
//                {
//                    intf->sendHelloPacket(neighbor->getAddress());
//                }
//
//                IPv4Address interfaceAddress = intf->getAddressRange().address;
//                unsigned int neighborsNeighborCount = helloPacket->getNeighborArraySize();
//                unsigned int i;
//                /* The list of neighbors contained in the Hello Packet is
//                   examined.  If the router itself appears in this list, the
//                   neighbor state machine should be executed with the event TWOWAY_RECEIVED.
//                 */
//                for (i = 0; i < neighborsNeighborCount; i++) {
//                    if (helloPacket->getNeighbor(i) == interfaceAddress) {
//                        neighbor->processEvent(OSPFN::Neighbor::TWOWAY_RECEIVED);
//                        break;
//                    }
//                }
//                /* Otherwise, the neighbor state machine should
//                   be executed with the event ONEWAY_RECEIVED, and the processing
//                   of the packet stops.
//                 */
//                if (i == neighborsNeighborCount) {
//                    neighbor->processEvent(OSPFN::Neighbor::ONEWAY_RECEIVED);
//                }
//
//                if (neighborChanged) {
//                    intf->processEvent(OSPFN::Interface::NEIGHBOR_CHANGE);
//                    /* In some cases neighbors get stuck in TwoWay state after a DR
//                       or Backup change. (calculateDesignatedRouter runs before the
//                       neighbors' signal of DR change + this router does not become
//                       neither DR nor backup -> IS_ADJACENCY_OK does not get called.)
//                       So to make it work(workaround) we'll call IS_ADJACENCY_OK for
//                       all neighbors in TwoWay state from here. This shouldn't break
//                       anything because if the neighbor state doesn't have to change
//                       then needAdjacency returns false and nothing happnes in
//                       IS_ADJACENCY_OK.
//                     */
//                    unsigned int neighborCount = intf->getNeighborCount();
//                    for (i = 0; i < neighborCount; i++) {
//                        OSPFN::Neighbor* stuckNeighbor = intf->getNeighbor(i);
//                        if (stuckNeighbor->getState() == OSPFN::Neighbor::TWOWAY_STATE) {
//                            stuckNeighbor->processEvent(OSPFN::Neighbor::IS_ADJACENCY_OK);
//                        }
//                    }
//
//                    if (neighborsDRStateChanged) {
//                        OSPFN::RouterLSA* routerLSA = intf->getArea()->findRouterLSA(router->getRouterID());
//
//                        if (routerLSA != NULL) {
//                            long sequenceNumber = routerLSA->getHeader().getLsSequenceNumber();
//                            if (sequenceNumber == MAX_SEQUENCE_NUMBER) {
//                                routerLSA->getHeader().setLsAge(MAX_AGE);
//                                intf->getArea()->floodLSA(routerLSA);
//                                routerLSA->incrementInstallTime();
//                            } else {
//                                OSPFN::RouterLSA* newLSA = intf->getArea()->originateRouterLSA();
//
//                                newLSA->getHeader().setLsSequenceNumber(sequenceNumber + 1);
//                                shouldRebuildRoutingTable |= routerLSA->update(newLSA);
//                                delete newLSA;
//
//                                intf->getArea()->floodLSA(routerLSA);
//                            }
//                        }
//                    }
//                }
//
//                if (backupSeen) {
//                    intf->processEvent(OSPFN::Interface::BACKUP_SEEN);
//                }
//            }
//        }
//    }
//
//    if (shouldRebuildRoutingTable) {
//        router->rebuildRoutingTable();
//    }
//}
