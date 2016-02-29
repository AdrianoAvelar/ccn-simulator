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


#include "OSPFNNeighborStateInit.h"

//#include "MessageHandler.h"
//#include "OSPFArea.h"
//#include "OSPFInterface.h"
//#include "OSPFNeighborStateDown.h"
#include "OSPFNNeighborStateExchangeStart.h"
//#include "OSPFNeighborStateTwoWay.h"
//#include "OSPFRouter.h"

#include "OSPFNNeighborStateDown.h"
#include "OSPFNMessageHandler.h"
#include "OSPFNInterface.h"
#include "OSPFNRouter.h"
#include "OSPFNcommon.h"

void OSPFN::NeighborStateInit::processEvent(OSPFN::Neighbor* neighbor, OSPFN::NeighborEventType event)
{
//    if ((event == OSPFN::KILL_NEIGHBOR) || (event == OSPFN::LINK_DOWN)) {
//        MessageHandler* messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
//        neighbor->reset();
//        messageHandler->clearTimer(neighbor->getInactivityTimer());
//        changeState(neighbor, new OSPFN::StateDown, this);
//    }
//    if (event == OSPFN::INACTIVITY_TIMER) {
//        neighbor->reset();
//        if (neighbor->getInterface()->getType() == OSPFN::Interface::NBMA) {
//            MessageHandler* messageHandler = neighbor->getInterface()->getArea()->getRouter()->getMessageHandler();
//            messageHandler->startTimer(neighbor->getPollTimer(), neighbor->getInterface()->getPollInterval());
//        }
//        changeState(neighbor, new OSPFN::StateDown, this);
//    }
    if (event == OSPFN::HELLO_RECEIVED) {
        MessageHandler* messageHandler = neighbor->getInterface()->getRouter()->getMessageHandler();
        messageHandler->clearTimer(neighbor->getInactivityTimer());
        messageHandler->startTimer(neighbor->getInactivityTimer(), neighbor->getRouterDeadInterval());
    }
    if (event == OSPFN::TWOWAY_RECEIVED) {
        if (neighbor->needAdjacency()) {
            MessageHandler* messageHandler = neighbor->getInterface()->getRouter()->getMessageHandler();
            if (!(neighbor->isFirstAdjacencyInited())) {
                neighbor->initFirstAdjacency();
            } else {
                neighbor->incrementDDSequenceNumber();
            }
            neighbor->sendDatabaseDescriptionPacket();
            messageHandler->startTimer(neighbor->getDDRetransmissionTimer(), neighbor->getInterface()->getRetransmissionInterval());
            changeState(neighbor, new OSPFN::NeighborStateExchangeStart, this);
        }
//        else {
//            changeState(neighbor, new OSPFN::StateTwoWay, this);
//        }
    }
}
