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


#include "OSPFNNeighborStateFull.h"

#include "MessageHandler.h"
//#include "OSPFNArea.h"
#include "OSPFNInterface.h"
#include "OSPFNNeighborStateDown.h"
#include "OSPFNNeighborStateExchangeStart.h"
#include "OSPFNNeighborStateInit.h"
//#include "OSPFNNeighborStateTwoWay.h"
#include "OSPFNRouter.h"


void OSPFN::NeighborStateFull::processEvent(OSPFN::Neighbor* neighbor, OSPFN::NeighborEventType event)
{
    if ((event == OSPFN::KILL_NEIGHBOR) || (event == OSPFN::LINK_DOWN)) {
        MessageHandler* messageHandler = neighbor->getInterface()->getRouter()->getMessageHandler();
        neighbor->reset();
        messageHandler->clearTimer(neighbor->getInactivityTimer());
        changeState(neighbor, new OSPFN::NeighborStateDown, this);
    }
    if (event == OSPFN::INACTIVITY_TIMER) {
        neighbor->reset();
        if (neighbor->getInterface()->getType() == OSPFN::Interface::NBMA) {
            MessageHandler* messageHandler = neighbor->getInterface()->getRouter()->getMessageHandler();
            messageHandler->startTimer(neighbor->getPollTimer(), neighbor->getInterface()->getPollInterval());
        }
        changeState(neighbor, new OSPFN::NeighborStateDown, this);
    }
    if (event == OSPFN::ONEWAY_RECEIVED) {
        neighbor->reset();
        changeState(neighbor, new OSPFN::NeighborStateInit, this);
    }
    if (event == OSPFN::HELLO_RECEIVED) {
        MessageHandler* messageHandler = neighbor->getInterface()->getRouter()->getMessageHandler();
        messageHandler->clearTimer(neighbor->getInactivityTimer());
        messageHandler->startTimer(neighbor->getInactivityTimer(), neighbor->getRouterDeadInterval());
        changeState(neighbor, new OSPFN::NeighborStateInit, this);
    }
    if (event == OSPFN::IS_ADJACENCY_OK) {
//        if (!neighbor->needAdjacency()) {
//            neighbor->reset();
//            changeState(neighbor, new OSPFN::NeighborStateTwoWay, this);
//        }
    }
    if ((event == OSPFN::SEQUENCE_NUMBER_MISMATCH) || (event == OSPFN::BAD_LINK_STATE_REQUEST)) {
        opp_error("OSPFN::NeighborStateFull::processEvent| SEQUENCE_NUMBER_MISMATCH");
        MessageHandler* messageHandler = neighbor->getInterface()->getRouter()->getMessageHandler();
        neighbor->reset();
        neighbor->incrementDDSequenceNumber();
        //neighbor->sendDatabaseDescriptionPacket(true);
        messageHandler->startTimer(neighbor->getDDRetransmissionTimer(), neighbor->getInterface()->getRetransmissionInterval());
        changeState(neighbor, new OSPFN::NeighborStateExchangeStart, this);
    }
//    if (event == OSPFN::UPDATE_RETRANSMISSION_TIMER) {
//        neighbor->retransmitUpdatePacket();
//        neighbor->startUpdateRetransmissionTimer();
//    }
//    if (event == OSPFN::DD_RETRANSMISSION_TIMER) {
//        neighbor->deleteLastSentDDPacket();
//    }
}
