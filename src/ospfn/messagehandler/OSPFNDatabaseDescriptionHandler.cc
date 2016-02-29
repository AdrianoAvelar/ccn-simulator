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

#include "OSPFNDatabaseDescriptionHandler.h"

//#include "OSPFArea.h"
#include "OSPFNInterface.h"
#include "OSPFNNeighbor.h"
#include "OSPFNRouter.h"

OSPFN::DatabaseDescriptionHandler::DatabaseDescriptionHandler(
        OSPFN::Router* containingRouter)
:        OSPFN::IMessageHandler(containingRouter) {
}

void OSPFN::DatabaseDescriptionHandler::processPacket(OSPFNPacket* packet){//,Interface* intf, Neighbor* neighbor)


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

    OSPFNDatabaseDescriptionPacket* ddPacket = check_and_cast<OSPFNDatabaseDescriptionPacket*>(packet);
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
        neighbor = intf->getNeighborByID(ddPacket->getRouterID());
    }

    if (neighbor != NULL) {

        OSPFN::NeighborStateType neighborState = neighbor->getState();
        switch (neighborState) {
        case OSPFN::TWOWAY_STATE:
            break;
        case OSPFN::INIT_STATE:
            neighbor->processEvent(OSPFN::TWOWAY_RECEIVED);
            break;
        case OSPFN::EXCHANGE_START_STATE:
        {
            neighbor->processEvent(OSPFN::NEGOTIATION_DONE);

//            Verificar dentros dos LSAHearders do ddPacket se existe algum do interesse.
//            Caso tenha, enviar um linkState. Envia de qualquer jeito o LSReqPacket vazio.


            neighbor->sendDatabaseDescriptionPacket();

            std::vector<chunk_t> lsas_vec;
            int lsas = ddPacket->getLsaHeadersArraySize();
            for(int i = 0; i < lsas; i++){
                lsas_vec.push_back(ddPacket->getLsaHeaders(i));
            }

            std::vector<chunk_t> desired_lsas = intf->getRouter()->getDesiredPrefix(lsas_vec);

            if(desired_lsas.size() > 0){
                neighbor->sendLinkStateRequestPacket(desired_lsas);
                neighbor->clearRequestRetransmissionTimer();
                neighbor->startRequestRetransmissionTimer();
            }

//                {
//                    OSPFDDOptions& ddOptions = ddPacket->getDdOptions();
//
//                    if (ddOptions.I_Init && ddOptions.M_More && ddOptions.MS_MasterSlave &&
//                        (ddPacket->getLsaHeadersArraySize() == 0))
//                    {
//                        if (neighbor->getNeighborID() > router->getRouterID()) {
//                            OSPFN::DDPacketID packetID;
//                            packetID.ddOptions = ddOptions;
//                            packetID.options = ddPacket->getOptions();
//                            packetID.sequenceNumber = ddPacket->getDdSequenceNumber();
//
//                            neighbor->setOptions(packetID.options);
//                            neighbor->setDatabaseExchangeRelationship(OSPFN::SLAVE);
//                            neighbor->setDDSequenceNumber(packetID.sequenceNumber);
//                            neighbor->setLastReceivedDDPacket(packetID);
//
//                            if (!processDDPacket(ddPacket, intf, neighbor, true)) {
//                                break;
//                            }
//
//                            neighbor->processEvent(OSPFN::NEGOTIATION_DONE);
//                            if (!neighbor->isLinkStateRequestListEmpty() &&
//                                !neighbor->isRequestRetransmissionTimerActive())
//                            {
//                                neighbor->sendLinkStateRequestPacket();
//                                neighbor->clearRequestRetransmissionTimer();
//                                neighbor->startRequestRetransmissionTimer();
//                            }
//                        } else {
//                            neighbor->sendDatabaseDescriptionPacket(true);
//                        }
//                    }
//                    if (!ddOptions.I_Init && !ddOptions.MS_MasterSlave &&
//                        (ddPacket->getDdSequenceNumber() == neighbor->getDDSequenceNumber()) &&
//                        (neighbor->getNeighborID() < router->getRouterID()))
//                    {
//                        OSPFN::DDPacketID packetID;
//                        packetID.ddOptions = ddOptions;
//                        packetID.options = ddPacket->getOptions();
//                        packetID.sequenceNumber = ddPacket->getDdSequenceNumber();
//
//                        neighbor->setOptions(packetID.options);
//                        neighbor->setDatabaseExchangeRelationship(OSPFN::MASTER);
//                        neighbor->setLastReceivedDDPacket(packetID);
//
//                        if (!processDDPacket(ddPacket, intf, neighbor, true)) {
//                            break;
//                        }
//
//                        neighbor->processEvent(OSPFN::NEGOTIATION_DONE);
//                        if (!neighbor->isLinkStateRequestListEmpty() &&
//                            !neighbor->isRequestRetransmissionTimerActive())
//                        {
//                            neighbor->sendLinkStateRequestPacket();
//                            neighbor->clearRequestRetransmissionTimer();
//                            neighbor->startRequestRetransmissionTimer();
//                        }
//                    }
//                }
            break;
        } case OSPFN::EXCHANGE_STATE:
//                {
//                    OSPFN::DDPacketID packetID;
//                    packetID.ddOptions = ddPacket->getDdOptions();
//                    packetID.options = ddPacket->getOptions();
//                    packetID.sequenceNumber = ddPacket->getDdSequenceNumber();
//
//                    if (packetID != neighbor->getLastReceivedDDPacket()) {
//                        if ((packetID.ddOptions.MS_MasterSlave &&
//                             (neighbor->getDatabaseExchangeRelationship() != OSPFN::SLAVE)) ||
//                            (!packetID.ddOptions.MS_MasterSlave &&
//                             (neighbor->getDatabaseExchangeRelationship() != OSPFN::MASTER)) ||
//                            packetID.ddOptions.I_Init ||
//                            (packetID.options != neighbor->getLastReceivedDDPacket().options))
//                        {
//                            neighbor->processEvent(OSPFN::SEQUENCE_NUMBER_MISMATCH);
//                        } else {
//                            if (((neighbor->getDatabaseExchangeRelationship() == OSPFN::MASTER) &&
//                                 (packetID.sequenceNumber == neighbor->getDDSequenceNumber())) ||
//                                ((neighbor->getDatabaseExchangeRelationship() == OSPFN::SLAVE) &&
//                                 (packetID.sequenceNumber == (neighbor->getDDSequenceNumber() + 1))))
//                            {
//                                neighbor->setLastReceivedDDPacket(packetID);
//                                if (!processDDPacket(ddPacket, intf, neighbor, false)) {
//                                    break;
//                                }
//                                if (!neighbor->isLinkStateRequestListEmpty() &&
//                                    !neighbor->isRequestRetransmissionTimerActive())
//                                {
//                                    neighbor->sendLinkStateRequestPacket();
//                                    neighbor->clearRequestRetransmissionTimer();
//                                    neighbor->startRequestRetransmissionTimer();
//                                }
//                            } else {
//                                neighbor->processEvent(OSPFN::SEQUENCE_NUMBER_MISMATCH);
//                            }
//                        }
//                    } else {
//                        if (neighbor->getDatabaseExchangeRelationship() == OSPFN::SLAVE) {
//                            neighbor->retransmitDatabaseDescriptionPacket();
//                        }
//                    }
//                }
            break;
        case OSPFN::LOADING_STATE:
        case OSPFN::FULL_STATE:
//                {
//                    OSPFN::DDPacketID packetID;
//                    packetID.ddOptions = ddPacket->getDdOptions();
//                    packetID.options = ddPacket->getOptions();
//                    packetID.sequenceNumber = ddPacket->getDdSequenceNumber();
//
//                    if ((packetID != neighbor->getLastReceivedDDPacket()) ||
//                        (packetID.ddOptions.I_Init))
//                    {
//                        neighbor->processEvent(OSPFN::SEQUENCE_NUMBER_MISMATCH);
//                    } else {
//                        if (neighbor->getDatabaseExchangeRelationship() == OSPFN::SLAVE) {
//                            if (!neighbor->retransmitDatabaseDescriptionPacket()) {
//                                neighbor->processEvent(OSPFN::SEQUENCE_NUMBER_MISMATCH);
//                            }
//                        }
//                    }
//                }
            break;
        default:
            break;
        }
        //  }
    }

}

bool OSPFN::DatabaseDescriptionHandler::processDDPacket(
        OSPFNDatabaseDescriptionPacket* ddPacket){//, OSPFN::Interface* intf, OSPFN::Neighbor* neighbor, bool inExchangeStart) {
//    EV << "  Processing packet contents(ddOptions="
//       << ((ddPacket->getDdOptions().I_Init) ? "I " : "_ ")
//       << ((ddPacket->getDdOptions().M_More) ? "M " : "_ ")
//       << ((ddPacket->getDdOptions().MS_MasterSlave) ? "MS" : "__")
//       << "; seqNumber="
//       << ddPacket->getDdSequenceNumber()
//       << "):\n";
//
//    unsigned int headerCount = ddPacket->getLsaHeadersArraySize();
//
//    for (unsigned int i = 0; i < headerCount; i++) {
//        OSPFLSAHeader& currentHeader = ddPacket->getLsaHeaders(i);
//        LSAType lsaType = static_cast<LSAType> (currentHeader.getLsType());
//
//        EV << "    ";
//        printLSAHeader(currentHeader, ev.getOStream());
//
//        if ((lsaType < ROUTERLSA_TYPE) || (lsaType > AS_EXTERNAL_LSA_TYPE) ||
//            ((lsaType == AS_EXTERNAL_LSA_TYPE) && (!intf->getArea()->getExternalRoutingCapability())))
//        {
//            EV << " Error!\n";
//            neighbor->processEvent(OSPFN::SEQUENCE_NUMBER_MISMATCH);
//            return false;
//        } else {
//            OSPFN::LSAKeyType lsaKey;
//
//            lsaKey.linkStateID = currentHeader.getLinkStateID();
//            lsaKey.advertisingRouter = currentHeader.getAdvertisingRouter();
//
//            OSPFLSA* lsaInDatabase = router->findLSA(lsaType, lsaKey, intf->getArea()->getAreaID());
//
//            //{OSPFN} begin:
//            IPv4ControlInfo* controlInfo = check_and_cast<IPv4ControlInfo *> (ddPacket->getControlInfo());
//
//            int psize = ddPacket->getPrefixsArraySize();
//            if(psize){
//                Prefix prefixs[psize];
//                for(int i = 0; i < psize; i++){
//                    prefixs[i] = ddPacket->getPrefixs(i);
//                }
//                router->addNeighborPrefix(prefixs,psize, controlInfo);
//            }
//            //{OSPFN} end:
//
//            // operator< and operator== on OSPFLSAHeaders determines which one is newer(less means older)
//            if ((lsaInDatabase == NULL) || (lsaInDatabase->getHeader() < currentHeader)) {
//                EV << " (newer)";
//                neighbor->addToRequestList(&currentHeader);
//            }
//        }
//        EV << "\n";
//    }
//
//    if (neighbor->getDatabaseExchangeRelationship() == OSPFN::MASTER) {
//        neighbor->incrementDDSequenceNumber();
//        if ((neighbor->getDatabaseSummaryListCount() == 0) && !ddPacket->getDdOptions().M_More) {
//            neighbor->processEvent(OSPFN::EXCHANGE_DONE);  // does nothing in ExchangeStart
//        } else {
//            if (!inExchangeStart) {
//                neighbor->sendDatabaseDescriptionPacket();
//            }
//        }
//    } else {
//        neighbor->setDDSequenceNumber(ddPacket->getDdSequenceNumber());
//        if (!inExchangeStart) {
//            neighbor->sendDatabaseDescriptionPacket();
//        }
//        if (!ddPacket->getDdOptions().M_More &&
//            (neighbor->getDatabaseSummaryListCount() == 0))
//        {
//            neighbor->processEvent(OSPFN::EXCHANGE_DONE);  // does nothing in ExchangeStart
//        }
//    }
    return true;
}
