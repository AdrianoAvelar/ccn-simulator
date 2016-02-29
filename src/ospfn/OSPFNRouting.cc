//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <string>
#include <map>
#include <stdlib.h>
#include <memory.h>

#include "OSPFNRouting.h"

Define_Module (OSPFNRouting);

OSPFNRouting::OSPFNRouting() {
    ospfnRouter = NULL;
}

OSPFNRouting::~OSPFNRouting() {
    delete ospfnRouter;
}

void OSPFNRouting::initialize(int stage) {
    // we have to wait for stage 2 until interfaces get registered(stage 0)
    // and routerId gets assigned(stage 3)
    if (stage == 0) {


    } else if (stage == 4) {
        ft = getModuleFromPar<ForwardingTable>(par("forwardingTableModule"), this);
        appId = CCN_OSPFN_APP;
        ccnLayer = getModuleFromPar<Ccn>(par("ccndModule"), this);

        registerMyselfInCcnLayer();

      // Get routerId
        ospfnRouter = new OSPFN::Router(ft->getRouterName(), this);
        ospfnRouter->setForwardingTable(ft);

        loadInterfaceParameters();

        cModule *routingModule = getContainingNode(this);
        routingModule->subscribe(NF_ADDED_PREFIX_TO_CACHE, this);
        routingModule->subscribe(NF_L2_ASSOCIATED_NEWAP,this);

    }
}

void OSPFNRouting::registerMyselfInCcnLayer() {

    if (gateSize("ipOut") == 0) {
        error("This application cannot be unconnected");
    }

    cGate *mygate = gate("ipIn");
    ccnLayer->registerApp(appId, mygate);
}

void OSPFNRouting::handleMessage(cMessage *msg) {
     ospfnRouter->getMessageHandler()->messageReceived(msg);
}

void OSPFNRouting::loadInterfaceParameters() {

    int numEthernetMacs = 0, numMacIds = 0, numWifiMacs = 0;
    vector<MACAddress> macIds;

    cModule *mdlNetIf = NULL, *mdlNode = NULL;
    mdlNode = getParentModule();
    MACAddress mac;
    //std::cerr << "Ccn::initialize: mdlNode (after): " << mdlNode->getFullName() << endl;
    for (int i = 0; (mdlNetIf = mdlNode->getSubmodule("eth", i)); i++) {
        if (mdlNetIf->getSubmodule("mac"))
        {
            mac.setAddress(mdlNetIf->getSubmodule("mac")->par("address"));
            macIds.push_back(mac);
        }

    }

    //Wireless CCN
    //mdlNode = getParentModule();
    for (int i = 0; (mdlNetIf = mdlNode->getSubmodule("wlan", i)); i++) {
        if (mdlNetIf->getSubmodule("mac"))
        {
            mac.setAddress(mdlNetIf->getSubmodule("mac")->par("address"));
            macIds.push_back(mac);
        }

    }

    OSPFN::Interface* intf ;//= new OSPFN::Interface();
    for (uint i = 0; i < macIds.size(); i++) {

        intf = new OSPFN::Interface();
        intf->setType(OSPFN::Interface::POINTTOPOINT);
        intf->setHelloInterval(par("helloInterval"));
        intf->setRetransmissionInterval(par("retransmissionInterval"));
        intf->setMACAddress(macIds[i]);
        ospfnRouter->addInterface(intf);
        intf->addBroadcastFaceToForwardingTable();

        intf->processEvent(OSPFN::Interface::INTERFACE_UP);
    }

}

void OSPFNRouting::sendPacket(cPacket* packet) {
    send(packet, "ipOut");
}

OSPFN::Router* OSPFNRouting::getRouter(){
    return ospfnRouter;
}


void OSPFNRouting::receiveSignal(cComponent *source, int signalID, cObject *obj)
{
    Enter_Method_Silent();
    printNotificationBanner(signalID, obj);

    // host associated. link is up. change the state to init.
    if (signalID == NF_ADDED_PREFIX_TO_CACHE) {
        std::vector<chunk_t> prefixList = ccnLayer->getPrefixList();
              std::vector<chunk_t>::iterator it;
          for (it = prefixList.begin(); it != prefixList.end(); it++) {
              ospfnRouter->addToPrefixTable((*it),MACAddress::UNSPECIFIED_ADDRESS,MACAddress::UNSPECIFIED_ADDRESS,true,0,true);
          }

          ospfnRouter->rebuildForwardingTable();

    }else if(signalID == NF_L2_ASSOCIATED_NEWAP) {

        std::cerr << "OSPFNRouting:: time : " << simTime() << std::endl;
        ospfnRouter->clearNeighborhood();
        ospfnRouter->clearPrefixTable();
        ospfnRouter->rebuildForwardingTable();
        ospfnRouter->floodHello();
    }
}


