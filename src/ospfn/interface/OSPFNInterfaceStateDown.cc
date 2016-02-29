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


#include "OSPFNInterfaceStateDown.h"

#include "OSPFNMessageHandler.h"
//#include "OSPFArea.h"
//#include "OSPFInterfaceStateLoopback.h"
//#include "OSPFInterfaceStateNotDesignatedRouter.h"
#include "OSPFNInterfaceStatePointToPoint.h"
//#include "OSPFInterfaceStateWaiting.h"
#include "OSPFNRouter.h"


void OSPFN::InterfaceStateDown::processEvent(OSPFN::Interface* intf, OSPFN::Interface::InterfaceEventType event)
{
    if (event == OSPFN::Interface::INTERFACE_UP) {

     //OSPFN::MessageHandler* messageHandler = intf->getArea()->getRouter()->getMessageHandler();

        OSPFN::MessageHandler* messageHandler = intf->getRouter()->getMessageHandler();
        double  time = truncnormal(0.1, 0.01);
     //   PRINT_ERR << "Interface UP: " << intf->getInterfaceName() << "send hello at: " << time<< ENDL;
        messageHandler->startTimer(intf->getHelloTimer(), time); // add some deviation to avoid startup collisions
       // messageHandler->startTimer(intf->getAcknowledgementTimer(), intf->getAcknowledgementDelay());

        switch (intf->getType()) {
            case OSPFN::Interface::POINTTOPOINT:
            case OSPFN::Interface::POINTTOMULTIPOINT:
            case OSPFN::Interface::VIRTUAL:
                changeState(intf, new OSPFN::InterfaceStatePointToPoint, this);
                break;
//            case OSPFN::Interface::NBMA:
//                if (intf->getRouterPriority() == 0) {
//                    changeState(intf, new OSPFN::InterfaceStateNotDesignatedRouter, this);
//                } else {
//                    changeState(intf, new OSPFN::InterfaceStateWaiting, this);
//                    messageHandler->startTimer(intf->getWaitTimer(), intf->getRouterDeadInterval());
//
//                    long neighborCount = intf->getNeighborCount();
//                    for (long i = 0; i < neighborCount; i++) {
//                        OSPFN::Neighbor* neighbor = intf->getNeighbor(i);
//                        if (neighbor->getPriority() > 0) {
//                            neighbor->processEvent(OSPFN::Neighbor::START);
//                        }
//                    }
//                }
//                break;
//
//            case OSPFN::Interface::BROADCAST:
//                if (intf->getRouterPriority() == 0) {
//                    changeState(intf, new OSPFN::InterfaceStateNotDesignatedRouter, this);
//                } else {
//                    changeState(intf, new OSPFN::InterfaceStateWaiting, this);
//                    messageHandler->startTimer(intf->getWaitTimer(), intf->getRouterDeadInterval());
//                }
//                break;

            default:
                break;
        }
    }
//    if (event == OSPFN::Interface::LOOP_INDICATION) {
//        intf->reset();
//        changeState(intf, new OSPFN::InterfaceStateLoopback, this);
//    }
}

