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

#include "ForwardingTable.h"
#include "XMLUtils.h"

Define_Module(ForwardingTable);

ForwardingTable::ForwardingTable() {


}

ForwardingTable::~ForwardingTable() {


}

void ForwardingTable::initialize(int stage)
{
    if (stage==0)
    {
        // get a pointer to the NotificationBoard module and IInterfaceTable
//        nb = NotificationBoardAccess().get();
        ift = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);

//        IPForward = par("IPForward").boolValue();
//        multicastForward = par("forwardMulticast");

//        nb->subscribe(this, NF_INTERFACE_CREATED);
//        nb->subscribe(this, NF_INTERFACE_DELETED);
//        nb->subscribe(this, NF_INTERFACE_STATE_CHANGED);
//        nb->subscribe(this, NF_INTERFACE_CONFIG_CHANGED);
//        nb->subscribe(this, NF_INTERFACE_IPv4CONFIG_CHANGED);

//        WATCH_PTRVECTOR(FIB)

//        WATCH_PTRVECTOR(routes);
//        WATCH_PTRVECTOR(multicastRoutes);
//        WATCH(IPForward);
//        WATCH(routerId);

    }
    else if (stage==1)
    {
        // L2 modules register themselves in stage 0, so we can only configure
        // the interfaces in stage 1.
        const char *filename = par("forwardingFile");

        // At this point, all L2 modules have registered themselves (added their
        // interface entries). Create the per-interface IPv4 data structures.
//        IInterfaceTable *interfaceTable = getModuleFromPar<InterfaceTable>(par("interfaceTable"), this);
//        for (int i=0; i<interfaceTable->getNumInterfaces(); ++i)
//            configureInterfaceForIPv4(interfaceTable->getInterface(i));
//        configureLoopbackForIPv4();

        // read routing table file (and interface configuration)
//        RoutingTableParser parser(ift, this);
//        if (*filename && parser.readRoutingTableFromFile(filename)==-1)
//            error("Error reading routing table file %s", filename);

       // set routerId if param is not "" (==no routerId) or "auto" (in which case we'll
       // do it later in stage 3, after network configurators configured the interfaces)
       const char *routerIdStr = par("routerId").stringValue();
       if (strcmp(routerIdStr, "") && strcmp(routerIdStr, "auto"))
           routerId = MACAddress(routerIdStr);

    }
    else if (stage==3)
    {
        // routerID selection must be after stage==2 when network autoconfiguration
        // assigns interface addresses
        configureRouterId();

        // we don't use notifications during initialize(), so we do it manually.
        // Should be in stage=3 because autoconfigurator runs in stage=2.
       // updateNetmaskRoutes();

        addDefaultGateway();

//        cXMLElement *ospfConfig = par("ftConfig").xmlValue();
//        if(!ospfConfig)
//            readTableFromXML(ospfConfig);

        //printRoutingTable();
        WATCH_MAP(FIB);
        addDefaultRoutes();

    }
}

void ForwardingTable::addDefaultGateway(){

    string defaultGw = par("defaultGateway");

    if(defaultGw == "none")
        return;

    cModule * topologyLevel = getParentModule();
    cModule * gw = topologyLevel->getModuleByPath(defaultGw.c_str());
    if(! (gw->getSubmodule("mac")))
        opp_error("module %s doesn't have submodule mac",defaultGw.c_str());

    defaultGw = gw->getSubmodule("mac")->par("address").stringValue();

    MACAddress srcAddr;
    srcAddr.setAddress(defaultGw.c_str());

    addL2FwdRule(DEFAULT_PREFIX, srcAddr, MACAddress::BROADCAST_ADDRESS, true, 0, false);
}

ForwardingTable::FIB_TABLE::iterator ForwardingTable::getDefaultGateway(){

    return lookup(DEFAULT_PREFIX);
}

void ForwardingTable::readTableFromXML(const cXMLElement *ftable)
{
    ASSERT(ftable);
    ASSERT(!strcmp(ftable->getTagName(), "ftable"));
    cXMLElementList list = ftable->getChildrenByTagName("fentry");
    for (cXMLElementList::iterator it=list.begin(); it != list.end(); it++)
        readItemFromXML(*it);
}

void ForwardingTable::readItemFromXML(const cXMLElement *fitem)
{
    ASSERT(fitem);
    ASSERT(!strcmp(fitem->getTagName(), "fentry") );

    string prefix = xmlutils::getParameterStrValue(fitem,"prefix");
    string nextHop = xmlutils::getParameterStrValue(fitem,"nextHop");
    string accessFrom = xmlutils::getParameterStrValue(fitem,"accessFrom");

    cModule * topologyLevel = getParentModule();      // climb up to the network level of the hierarchy
    cModule * localNetif = topologyLevel->getModuleByRelativePath(accessFrom.c_str());
    cModule * nextHopNetif = topologyLevel->getModuleByRelativePath(nextHop.c_str());

    if (    (nextHopNetif == NULL) ||
                        ((localNetif == NULL))  )
    {
        std::cerr //DBGPRT(EVAUX, Err, this->getFullPath())
                << " Insert Forwarding Rule by XML: "
                << ". Forgetting an invalid forwarding rule"
                << std::endl;
        std::cerr //DBGPRT(AUX, Detail, this->getFullPath())
                << "\n\t Node interface: " << ((nextHopNetif) ? accessFrom : nextHop ) << " does not exist in current topology."
                << std::endl;

         // parse next line
    }
    else if ( ! (nextHopNetif->getSubmodule("mac")) )
    {
        std::cerr //DBGPRT(EVAUX, Err, this->getFullPath())
                << " Insert Forwarding Rule by XML: "
                << ". Forgetting an invalid forwarding rule"
                << std::endl;
       std::cerr// DBGPRT(AUX, Detail, this->getFullPath())
                << "\n\t Node " << nextHop << " does not have a MAC submodule."
                << std::endl;


    }

//    bool ForwardingTable::addL2FwdRule(const char *contentName, MACAddress srcAddr,
//            MACAddress dstAddr, bool isLocal, int hops, bool isAdv)


}

void ForwardingTable::configureRouterId()
{
    if (routerId.isUnspecified())  // not yet configured
    {
        if (!strcmp(par("routerId").stringValue(), "auto"))  // non-"auto" cases already handled in stage 1
        {
            // choose highest interface address as routerId
            for (int i=0; i < ift->getNumInterfaces(); ++i)
            {
                InterfaceEntry *ie = ift->getInterface(i);
                if (!ie->isLoopback() && ie->getMacAddress().getInt() > routerId.getInt())
                    routerId = ie->getMacAddress();
            }
        }
    }
    else // already configured
    {
        routerId = MACAddress("0::0");
//        // if there is no interface with routerId yet, assign it to the loopback address;
//        // TODO find out if this is a good practice, in which situations it is useful etc.
//        if (getInterfaceByAddress(routerId)==NULL)
//        {
//            InterfaceEntry *lo0 = ift->getFirstLoopbackInterface();
//            lo0->ipv4Data()->setIPAddress(routerId);
//            lo0->ipv4Data()->setNetmask(IPv4Address::ALLONES_ADDRESS);
//        }
    }
}

void ForwardingTable::setRouterId(MACAddress mac)
{
    routerId = mac;
}


void ForwardingTable::addDefaultRoutes(){

    addL2FwdRule("/broadcast",MACAddress::BROADCAST_ADDRESS,MACAddress::BROADCAST_ADDRESS,true,0,false);
    addL2FwdRule(getRouterNamePrefix().c_str(), MACAddress::UNSPECIFIED_ADDRESS, MACAddress::UNSPECIFIED_ADDRESS,true,0,true);

    addDefaultGateway();
}

MACAddress ForwardingTable::getRouterId()
{
    return routerId;
}

string ForwardingTable::getRouterName(){

   // char name[64];
   // sprintf(name,"router#%d",getParentModule()->getId());

   // string routerName(name);

    string routerName = getParentModule()->getName();

    return routerName;
}

string ForwardingTable::getRouterNamePrefix(){

    char name[64];
    sprintf(name,"/%s",getParentModule()->getName());

    string routerName(name);
    return routerName;
}

void ForwardingTable::receiveChangeNotification(int category, const cObject *details)
{
    if (simulation.getContextType()==CTX_INITIALIZE)
        return;  // ignore notifications during initialize

    Enter_Method_Silent();
    printNotificationBanner(category, details);


    if (category==NF_INTERFACE_CREATED)
    {
        // add netmask route for the new interface
        //      updateNetmaskRoutes();
    }
    else if (category==NF_INTERFACE_DELETED)
    {
        // remove all routes that point to that interface
        //      InterfaceEntry *entry = check_and_cast<InterfaceEntry*>(details);
        //       deleteInterfaceRoutes(entry);
    }
    else if (category==NF_INTERFACE_STATE_CHANGED)
    {
        //       invalidateCache();
    }
    else if (category==NF_INTERFACE_CONFIG_CHANGED)
    {
        //        invalidateCache();
    }
    else if (category==NF_INTERFACE_IPv4CONFIG_CHANGED)
    {
        // if anything IPv4-related changes in the interfaces, interface netmask
        // based routes have to be re-built.
        //       updateNetmaskRoutes();
    }
}

bool ForwardingTable::isInTable(chunk_t content) {

    //   std::string content = contentName;
    bool is_in_table = false;
    FIB_TABLE::iterator fib_entry;

    for (;;) {

        fib_entry = FIB.find(content);
          if (fib_entry != FIB.end()) {
              is_in_table = true;
              break;
          }

        content = Util::getPrefixContentName(content);

        if (content == "") {

   //         content = "/";
   //         fib_entry = FIB.find(content);
            fib_entry = FIB.end();
            break;
        }


    }

    return is_in_table;

}



ForwardingTable::FIB_TABLE::iterator ForwardingTable::lookup(std::string content) {

 //   std::string content = contentName;
    FIB_TABLE::iterator fib_entry;

    while (true) {

        fib_entry = FIB.find(content);
          if (fib_entry != FIB.end()) {
              break;
          }

        content = Util::getPrefixContentName(content);

        if (strcmp(content.c_str(),"") == 0) {
   //         content = "/";
   //         fib_entry = FIB.find(content);
            fib_entry = FIB.end();
            break;
        }else{
            continue;
        }
    }

    return fib_entry;
}

void ForwardingTable::clear(){
    FIB.clear();
    addDefaultRoutes();
}

ForwardingTable::FIB_TABLE ForwardingTable::getTable(){
    return FIB;
}

ForwardingTable::FIB_TABLE * ForwardingTable::getTablePtr(){
    return &FIB;
}


//Return true if the operation was an update and false if the operation was an add.
bool ForwardingTable::addOrUpdateL2FwdRule(const char *contentName, MACAddress srcAddr,
        MACAddress dstAddr, bool isLocal, int hops, bool isAdv) {

    bool operation;

    chunk_t chunk = std::string(contentName);
    FIB_TABLE::iterator fibIt = FIB.find(chunk);

    string content = contentName;
    if(content[0] != '/' ||  *content.rbegin() == '/')
      error("In ForwardingTable: inconsistent prefix");

    if (fibIt != FIB.end()) {

        fib_entry entry;
        entry.src = srcAddr;
        entry.dst = dstAddr;
        entry.hops = hops;
        entry.isAdv = isAdv;
        entry.isLocal = isLocal;
        entry.time = simTime();
        FIB[chunk] = entry;


        operation = false;
    }else{
        addL2FwdRule(contentName,srcAddr,dstAddr,isLocal,hops,isAdv);
        operation = true;
    }

    return operation;
}

/** Add a FIB rule using L2 ID (MAC address). Return success/fail */
bool ForwardingTable::addL2FwdRule(const char *contentName, MACAddress srcAddr,
        MACAddress dstAddr, bool isLocal, int hops, bool isAdv) {

    chunk_t chunk = std::string(contentName);
    FIB_TABLE::iterator fibIt = FIB.find(chunk);

    string content = contentName;
    if(content[0] != '/' ||  *content.rbegin() == '/')
      error("In ForwardingTable: inconsistent prefix");

    //DBGPRT(EVAUX, Info, this->getFullPath()) << "Adding FIB Entry\n"
//    PRINT_ERR << "******************************\n" << getParentModule()->getName()
//            <<": prefix: " << contentName
//            << " Source: " << srcAddr.str().c_str() << " Destination: "
//            << dstAddr.str().c_str() << " Time: " << simTime()
//            << " FIB[" << chunk <<":  " <<  fibIt->second << endl;

    if (fibIt == FIB.end() ||
            ( //(FIB[chunk].time != 0) &&
                    (simTime() - FIB[chunk].time > FIB_ENTRY_TIMEOUT))) {
        fib_entry entry;
        entry.src = srcAddr;
        entry.dst = dstAddr;
        entry.hops = hops;
        entry.isAdv = isAdv;
        entry.isLocal = isLocal;
        entry.time = simTime();
        FIB[chunk] = entry;
        return true;
    }

    return false;
}
void ForwardingTable::printForwardingTable(){

    FIB_TABLE::iterator fibIt;
    fib_entry entry;
    std::cerr << "[FORWARDING TABLE]:" << getParentModule()->getName() << std::endl;
    std::cerr << "Content   |       src       |        dst       |     time    |    isLocal   \n";
    for(fibIt = FIB.begin(); fibIt != FIB.end(); fibIt++){

        entry = (*fibIt).second;

        std::cerr << (*fibIt).first << " " <<
                entry.src << " " <<
                entry.dst << "\t\t " <<
                entry.time << "\t\t " <<
                entry.isLocal << std::endl;
    }
}

void ForwardingTable::handleMessage(cMessage *){

    throw cRuntimeError("This module doesn't process messages");
}
