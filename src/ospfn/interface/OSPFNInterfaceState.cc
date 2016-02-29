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


#include <map>

#include "OSPFNInterfaceState.h"

//#include "OSPFArea.h"
#include "OSPFNInterface.h"
//#include "OSPFInterfaceStateBackup.h"
//#include "OSPFInterfaceStateDesignatedRouter.h"
//#include "OSPFInterfaceStateNotDesignatedRouter.h"
#include "OSPFNRouter.h"


void OSPFN::InterfaceState::changeState(OSPFN::Interface* intf, OSPFN::InterfaceState* newState, OSPFN::InterfaceState* currentState)
{
    OSPFN::Interface::InterfaceStateType oldState = currentState->getState();
    OSPFN::Interface::InterfaceStateType nextState = newState->getState();
    OSPFN::Interface::OSPFInterfaceType intfType = intf->getType();
    bool shouldRebuildRoutingTable = false;

    intf->changeState(newState, currentState);


    if ((oldState == OSPFN::Interface::DOWN_STATE) ||
        (nextState == OSPFN::Interface::DOWN_STATE) ||
        (oldState == OSPFN::Interface::LOOPBACK_STATE) ||
        (nextState == OSPFN::Interface::LOOPBACK_STATE) ||
        (oldState == OSPFN::Interface::DESIGNATED_ROUTER_STATE) ||
        (nextState == OSPFN::Interface::DESIGNATED_ROUTER_STATE) ||
        ((intfType == OSPFN::Interface::POINTTOPOINT) &&
         ((oldState == OSPFN::Interface::POINTTOPOINT_STATE) ||
          (nextState == OSPFN::Interface::POINTTOPOINT_STATE))) ||
        (((intfType == OSPFN::Interface::BROADCAST) ||
          (intfType == OSPFN::Interface::NBMA)) &&
         ((oldState == OSPFN::Interface::WAITING_STATE) ||
          (nextState == OSPFN::Interface::WAITING_STATE))))
    {

        //intf->getRouter()->floodHello();

    }
//        OSPFN::RouterLSA* routerLSA = intf->getArea()->findRouterLSA(intf->getArea()->getRouter()->getRouterID());
//
//        if (routerLSA != NULL) {
//            long sequenceNumber = routerLSA->getHeader().getLsSequenceNumber();
//            if (sequenceNumber == MAX_SEQUENCE_NUMBER) {
//                routerLSA->getHeader().setLsAge(MAX_AGE);
//                intf->getArea()->floodLSA(routerLSA);
//                routerLSA->incrementInstallTime();
//            } else {
//                OSPFN::RouterLSA* newLSA = intf->getArea()->originateRouterLSA();
//
//                newLSA->getHeader().setLsSequenceNumber(sequenceNumber + 1);
//                shouldRebuildRoutingTable |= routerLSA->update(newLSA);
//                delete newLSA;
//
//                intf->getArea()->floodLSA(routerLSA);
//            }
//        } else {  // (lsa == NULL) -> This must be the first time any interface is up...
//            OSPFN::RouterLSA* newLSA = intf->getArea()->originateRouterLSA();
//
//            shouldRebuildRoutingTable |= intf->getArea()->installRouterLSA(newLSA);
//
//            routerLSA = intf->getArea()->findRouterLSA(intf->getArea()->getRouter()->getRouterID());
//
//            intf->getArea()->setSPFTreeRoot(routerLSA);
//            intf->getArea()->floodLSA(newLSA);
//
//            delete newLSA;
//        }
//    }
//
//    if (nextState == OSPFN::Interface::DESIGNATED_ROUTER_STATE) {
//        OSPFN::NetworkLSA* newLSA = intf->getArea()->originateNetworkLSA(intf);
//        if (newLSA != NULL) {
//            shouldRebuildRoutingTable |= intf->getArea()->installNetworkLSA(newLSA);
//
//            intf->getArea()->floodLSA(newLSA);
//            delete newLSA;
//        } else {    // no neighbors on the network -> old NetworkLSA must be flushed
//            OSPFN::NetworkLSA* oldLSA = intf->getArea()->findNetworkLSA(intf->getAddressRange().address);
//
//            if (oldLSA != NULL) {
//                oldLSA->getHeader().setLsAge(MAX_AGE);
//                intf->getArea()->floodLSA(oldLSA);
//                oldLSA->incrementInstallTime();
//            }
//        }
//    }
//
//    if (oldState == OSPFN::Interface::DESIGNATED_ROUTER_STATE) {
//        OSPFN::NetworkLSA* networkLSA = intf->getArea()->findNetworkLSA(intf->getAddressRange().address);
//
//        if (networkLSA != NULL) {
//            networkLSA->getHeader().setLsAge(MAX_AGE);
//            intf->getArea()->floodLSA(networkLSA);
//            networkLSA->incrementInstallTime();
//        }
//    }
//
//    if (shouldRebuildRoutingTable) {
//        intf->getRouter()->rebuildRoutingTable();
//    }
}

void OSPFN::InterfaceState::calculateDesignatedRouter(OSPFN::Interface* intf)
{
//    OSPFN::RouterID routerID = intf->parentArea->getRouter()->getRouterID();
//    OSPFN::DesignatedRouterID currentDesignatedRouter = intf->designatedRouter;
//    OSPFN::DesignatedRouterID currentBackupRouter = intf->backupDesignatedRouter;
//
//    unsigned int neighborCount = intf->neighboringRouters.size();
//    unsigned char repeatCount = 0;
//    unsigned int i;
//
//    OSPFN::DesignatedRouterID declaredBackup;
//    unsigned char declaredBackupPriority;
//    OSPFN::RouterID declaredBackupID;
//    bool backupDeclared;
//
//    OSPFN::DesignatedRouterID declaredDesignatedRouter;
//    unsigned char declaredDesignatedRouterPriority;
//    OSPFN::RouterID declaredDesignatedRouterID;
//    bool designatedRouterDeclared;
//
//    do {
//        // calculating backup designated router
//        declaredBackup = OSPFN::NULL_DESIGNATEDROUTERID;
//        declaredBackupPriority = 0;
//        declaredBackupID = OSPFN::NULL_ROUTERID;
//        backupDeclared = false;
//
//        OSPFN::DesignatedRouterID highestRouter = OSPFN::NULL_DESIGNATEDROUTERID;
//        unsigned char highestPriority = 0;
//        OSPFN::RouterID highestID = OSPFN::NULL_ROUTERID;
//
//        for (i = 0; i < neighborCount; i++) {
//            OSPFN::Neighbor* neighbor = intf->neighboringRouters[i];
//            unsigned char neighborPriority = neighbor->getPriority();
//
//            if (neighbor->getState() < OSPFN::Neighbor::TWOWAY_STATE) {
//                continue;
//            }
//            if (neighborPriority == 0) {
//                continue;
//            }
//
//            OSPFN::RouterID neighborID = neighbor->getNeighborID();
//            OSPFN::DesignatedRouterID neighborsDesignatedRouter = neighbor->getDesignatedRouter();
//            OSPFN::DesignatedRouterID neighborsBackupDesignatedRouter = neighbor->getBackupDesignatedRouter();
//
//            if (neighborsDesignatedRouter.routerID != neighborID) {
//                if (neighborsBackupDesignatedRouter.routerID == neighborID) {
//                    if ((neighborPriority > declaredBackupPriority) ||
//                        ((neighborPriority == declaredBackupPriority) &&
//                         (neighborID > declaredBackupID)))
//                    {
//                        declaredBackup = neighborsBackupDesignatedRouter;
//                        declaredBackupPriority = neighborPriority;
//                        declaredBackupID = neighborID;
//                        backupDeclared = true;
//                    }
//                }
//                if (!backupDeclared) {
//                    if ((neighborPriority > highestPriority) ||
//                        ((neighborPriority == highestPriority) &&
//                         (neighborID > highestID)))
//                    {
//                        highestRouter.routerID = neighborID;
//                        highestRouter.ipInterfaceAddress = neighbor->getAddress();
//                        highestPriority = neighborPriority;
//                        highestID = neighborID;
//                    }
//                }
//            }
//        }
//        // also include the router itself in the calculations
//        if (intf->routerPriority > 0) {
//            if (currentDesignatedRouter.routerID != routerID) {
//                if (currentBackupRouter.routerID == routerID) {
//                    if ((intf->routerPriority > declaredBackupPriority) ||
//                        ((intf->routerPriority == declaredBackupPriority) &&
//                         (routerID > declaredBackupID)))
//                    {
//                        declaredBackup.routerID = routerID;
//                        declaredBackup.ipInterfaceAddress = intf->interfaceAddressRange.address;
//                        declaredBackupPriority = intf->routerPriority;
//                        declaredBackupID = routerID;
//                        backupDeclared = true;
//                    }
//
//                }
//                if (!backupDeclared) {
//                    if ((intf->routerPriority > highestPriority) ||
//                        ((intf->routerPriority == highestPriority) &&
//                         (routerID > highestID)))
//                    {
//                        declaredBackup.routerID = routerID;
//                        declaredBackup.ipInterfaceAddress = intf->interfaceAddressRange.address;
//                        declaredBackupPriority = intf->routerPriority;
//                        declaredBackupID = routerID;
//                        backupDeclared = true;
//                    } else {
//                        declaredBackup = highestRouter;
//                        declaredBackupPriority = highestPriority;
//                        declaredBackupID = highestID;
//                        backupDeclared = true;
//                    }
//                }
//            }
//        }
//
//        // calculating backup designated router
//        declaredDesignatedRouter = OSPFN::NULL_DESIGNATEDROUTERID;
//        declaredDesignatedRouterPriority = 0;
//        declaredDesignatedRouterID = OSPFN::NULL_ROUTERID;
//        designatedRouterDeclared = false;
//
//        for (i = 0; i < neighborCount; i++) {
//            OSPFN::Neighbor* neighbor = intf->neighboringRouters[i];
//            unsigned char neighborPriority = neighbor->getPriority();
//
//            if (neighbor->getState() < OSPFN::Neighbor::TWOWAY_STATE) {
//                continue;
//            }
//            if (neighborPriority == 0) {
//                continue;
//            }
//
//            OSPFN::RouterID neighborID = neighbor->getNeighborID();
//            OSPFN::DesignatedRouterID neighborsDesignatedRouter = neighbor->getDesignatedRouter();
//            OSPFN::DesignatedRouterID neighborsBackupDesignatedRouter = neighbor->getBackupDesignatedRouter();
//
//            if (neighborsDesignatedRouter.routerID == neighborID) {
//                if ((neighborPriority > declaredDesignatedRouterPriority) ||
//                    ((neighborPriority == declaredDesignatedRouterPriority) &&
//                     (neighborID > declaredDesignatedRouterID)))
//                {
//                    declaredDesignatedRouter = neighborsDesignatedRouter;
//                    declaredDesignatedRouterPriority = neighborPriority;
//                    declaredDesignatedRouterID = neighborID;
//                    designatedRouterDeclared = true;
//                }
//            }
//        }
//        // also include the router itself in the calculations
//        if (intf->routerPriority > 0) {
//            if (currentDesignatedRouter.routerID == routerID) {
//                if ((intf->routerPriority > declaredDesignatedRouterPriority) ||
//                    ((intf->routerPriority == declaredDesignatedRouterPriority) &&
//                     (routerID > declaredDesignatedRouterID)))
//                {
//                    declaredDesignatedRouter.routerID = routerID;
//                    declaredDesignatedRouter.ipInterfaceAddress = intf->interfaceAddressRange.address;
//                    declaredDesignatedRouterPriority = intf->routerPriority;
//                    declaredDesignatedRouterID = routerID;
//                    designatedRouterDeclared = true;
//                }
//
//            }
//        }
//        if (!designatedRouterDeclared) {
//            declaredDesignatedRouter = declaredBackup;
//            declaredDesignatedRouterPriority = declaredBackupPriority;
//            declaredDesignatedRouterID = declaredBackupID;
//            designatedRouterDeclared = true;
//        }
//
//        // if the router is any kind of DR or is no longer one of them, then repeat
//        if (
//            (
//                (declaredDesignatedRouter.routerID != OSPFN::NULL_ROUTERID) &&
//                ((
//                    (currentDesignatedRouter.routerID == routerID) &&
//                    (declaredDesignatedRouter.routerID != routerID)
//                ) ||
//                (
//                    (currentDesignatedRouter.routerID != routerID) &&
//                    (declaredDesignatedRouter.routerID == routerID)
//                ))
//            ) ||
//            (
//                (declaredBackup.routerID != OSPFN::NULL_ROUTERID) &&
//                ((
//                    (currentBackupRouter.routerID == routerID) &&
//                    (declaredBackup.routerID != routerID)
//                ) ||
//                (
//                    (currentBackupRouter.routerID != routerID) &&
//                    (declaredBackup.routerID == routerID)
//                ))
//            )
//        )
//        {
//            currentDesignatedRouter = declaredDesignatedRouter;
//            currentBackupRouter = declaredBackup;
//            repeatCount++;
//        } else {
//            repeatCount += 2;
//        }
//
//    } while (repeatCount < 2);
//
//    OSPFN::RouterID routersOldDesignatedRouterID = intf->designatedRouter.routerID;
//    OSPFN::RouterID routersOldBackupID = intf->backupDesignatedRouter.routerID;
//
//    intf->designatedRouter = declaredDesignatedRouter;
//    intf->backupDesignatedRouter = declaredBackup;
//
//    bool wasBackupDesignatedRouter = (routersOldBackupID == routerID);
//    bool wasDesignatedRouter = (routersOldDesignatedRouterID == routerID);
//    bool wasOther = (intf->getState() == OSPFN::Interface::NOT_DESIGNATED_ROUTER_STATE);
//    bool wasWaiting = (!wasBackupDesignatedRouter && !wasDesignatedRouter && !wasOther);
//    bool isBackupDesignatedRouter = (declaredBackup.routerID == routerID);
//    bool isDesignatedRouter = (declaredDesignatedRouter.routerID == routerID);
//    bool isOther = (!isBackupDesignatedRouter && !isDesignatedRouter);
//
//    if (wasBackupDesignatedRouter) {
//        if (isDesignatedRouter) {
//            changeState(intf, new OSPFN::InterfaceStateDesignatedRouter, this);
//        }
//        if (isOther) {
//            changeState(intf, new OSPFN::InterfaceStateNotDesignatedRouter, this);
//        }
//    }
//    if (wasDesignatedRouter) {
//        if (isBackupDesignatedRouter) {
//            changeState(intf, new OSPFN::InterfaceStateBackup, this);
//        }
//        if (isOther) {
//            changeState(intf, new OSPFN::InterfaceStateNotDesignatedRouter, this);
//        }
//    }
//    if (wasOther) {
//        if (isDesignatedRouter) {
//            changeState(intf, new OSPFN::InterfaceStateDesignatedRouter, this);
//        }
//        if (isBackupDesignatedRouter) {
//            changeState(intf, new OSPFN::InterfaceStateBackup, this);
//        }
//    }
//    if (wasWaiting) {
//        if (isDesignatedRouter) {
//            changeState(intf, new OSPFN::InterfaceStateDesignatedRouter, this);
//        }
//        if (isBackupDesignatedRouter) {
//            changeState(intf, new OSPFN::InterfaceStateBackup, this);
//        }
//        if (isOther) {
//            changeState(intf, new OSPFN::InterfaceStateNotDesignatedRouter, this);
//        }
//    }
//
//    for (i = 0; i < neighborCount; i++) {
//        if ((intf->interfaceType == OSPFN::Interface::NBMA) &&
//            ((!wasBackupDesignatedRouter && isBackupDesignatedRouter) ||
//             (!wasDesignatedRouter && isDesignatedRouter)))
//        {
//            if (intf->neighboringRouters[i]->getPriority() == 0) {
//                intf->neighboringRouters[i]->processEvent(OSPFN::Neighbor::START);
//            }
//        }
//        if ((declaredDesignatedRouter.routerID != routersOldDesignatedRouterID) ||
//            (declaredBackup.routerID != routersOldBackupID))
//        {
//            if (intf->neighboringRouters[i]->getState() >= OSPFN::Neighbor::TWOWAY_STATE) {
//                intf->neighboringRouters[i]->processEvent(OSPFN::Neighbor::IS_ADJACENCY_OK);
//            }
//        }
//    }
}
