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


#include "OSPFNInterfaceStatePointToPoint.h"

#include "OSPFNMessageHandler.h"
//#include "OSPFArea.h"
#include "OSPFNInterfaceStateDown.h"
//#include "OSPFInterfaceStateLoopback.h"
#include "OSPFNRouter.h"


void OSPFN::InterfaceStatePointToPoint::processEvent(OSPFN::Interface* intf, OSPFN::Interface::InterfaceEventType event)
{
    if (event == OSPFN::Interface::INTERFACE_DOWN) {
        intf->reset();
        changeState(intf, new OSPFN::InterfaceStateDown, this);
    }
    if (event == OSPFN::Interface::LOOP_INDICATION) {
        intf->reset();
        opp_error("OSPFN::InterfaceStatePointToPoint::processEvent:");
       // changeState(intf, new OSPFN::InterfaceStateLoopback, this);
    }
    if (event == OSPFN::Interface::HELLO_TIMER) {

//        if (intf->getType() == OSPFN::Interface::VIRTUAL) {
//            if (intf->getNeighborCount() > 0) {
//                intf->sendHelloPacket(intf->getNeighbor(0)->getAddress(), VIRTUAL_LINK_TTL);
//            }
//        } else {
            intf->floodHello();
//        }
       intf->getRouter()->getMessageHandler()->startTimer(intf->getHelloTimer(), intf->getHelloInterval());
    }
    if (event == OSPFN::Interface::ACKNOWLEDGEMENT_TIMER) {
        opp_error("OSPFN::InterfaceStatePointToPoint::processEvent: ACKNOWLEDGEMENT_TIMER");
//        intf->sendDelayedAcknowledgements();
   }
}

