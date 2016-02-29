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

#include "OSPFNRouter.h"


OSPFN::Router::Router(std::string name, cSimpleModule* containingModule)/* :
 routerID(id),
 rfc1583Compatibility(false) */
{
    routerName = name;
    messageHandler = new OSPFN::MessageHandler(this, containingModule);

    forwardingTable = NULL;
//    ageTimer = new OSPFTimer();
//    ageTimer->setTimerKind(DATABASE_AGE_TIMER);
//    ageTimer->setContextPointer(this);
//    ageTimer->setName("OSPFN::Router::DatabaseAgeTimer");
//    messageHandler->startTimer(ageTimer, 1.0);
    lastFlood = -100;
}

void OSPFN::Router::setForwardingTable(ForwardingTable* ft) {
    this->forwardingTable = ft;
}


ForwardingTable* OSPFN::Router::getForwardingTable() {
    return this->forwardingTable;
}


OSPFN::Interface* OSPFN::Router::getInterfaceByMac(MACAddress &macaddress){

    for(int i = 0; associatedInterfaces.size(); i++){
        if( associatedInterfaces[i]->getMACAddress() == macaddress)
            return associatedInterfaces[i];
    }

    return NULL;
}

void OSPFN::Router::dumpInterfaces(){

    PRINT_ERR << "DumpInterface of " << getMessageHandler()->getOSPFNModule()->getParentModule()->getName()<< ENDL;
    for(int i = 0; associatedInterfaces.size(); i++){
        PRINT_ERR << "Interface[" << i << "] = " <<    associatedInterfaces[i]->getMACAddress() << ENDL;
    }

}

string OSPFN::Router::getPacketTypeName(int type){
    string type_name;
    switch (type){
    case OSPFN_HELLO_PACKET: return "hello";
    case OSPFN_DATABASE_DESCRIPTION_PACKET: return "database_description";
    case OSPFN_LINKSTATE_UPDATE_PACKET: return "lsa_upd";
    case OSPFN_LINKSTATE_ACKNOWLEDGEMENT_PACKET: return "lsa_ack";
    default : return "";
    }

}

void OSPFN::Router::addOrUpdatePrefixTableEntry(string prefix, MACAddress src, MACAddress dest, bool isLocal, int hops, bool isAdv){

    string prefix_mod = prefix;
        if (prefix[prefix.size()-1] == '/'){
            prefix_mod = prefix.substr(0, prefix.size()-1);
           // PRINT_ERR << "The prefix cannot have '/' character at last prefix" << ENDL;
        }

        if(prefix[0] != '/' )
        {
            string slash = "/";
            slash += prefix_mod;

            prefix_mod = slash;
        }

        string content = prefix_mod;
        if(content[0] != '/' ||  *content.rbegin() == '/')
          opp_error("In ForwardingTable: inconsistent prefix");

        if(existEntryInPF(prefix, hops)){
            prefixTable.erase(prefix_mod);
        }

        PrefixEntry entry;
        entry.prefix = prefix_mod;
        entry.src = src;
        entry.dst = dest;
        entry.hops = hops;
        entry.isLocal = isLocal;
        entry.isAdvertisable = isAdv;

        if(prefixTable.find(prefix_mod) == prefixTable.end()){

            PrefixVector pvector;
            pvector.push_back(entry);
            prefixTable[prefix_mod] = pvector;
        }else
            prefixTable[prefix_mod].push_back(entry);
}

void OSPFN::Router::addToPrefixTable(string prefix, MACAddress src, MACAddress dest, bool isLocal, int hops, bool isAdv){

     string prefix_mod = prefix;
     if (prefix[prefix.size()-1] == '/'){
         prefix_mod = prefix.substr(0, prefix.size()-1);
        // PRINT_ERR << "The prefix cannot have '/' character at last prefix" << ENDL;
     }

     if(prefix[0] != '/' )
     {
         string slash = "/";
         slash += prefix_mod;

         prefix_mod = slash;
     }


     string content = prefix_mod;
     if(content[0] != '/' ||  *content.rbegin() == '/')
       opp_error("In ForwardingTable: inconsistent prefix");


     if(existEntryInPF(prefix, hops)){
         EV << "prefix "<< prefix <<" exists in prefixTable ";
         return;
     }

     PrefixEntry entry;
     entry.prefix = prefix_mod;
     entry.src = src;
     entry.dst = dest;
     entry.hops = hops;
     entry.isLocal = isLocal;
     entry.isAdvertisable = isAdv;

     if(prefixTable.find(prefix_mod) == prefixTable.end()){

         PrefixVector pvector;
         pvector.push_back(entry);
         prefixTable[prefix_mod] = pvector;
     }else
         prefixTable[prefix_mod].push_back(entry);
}

bool OSPFN::Router::existEntryInPF(chunk_t prefix, int hops){

    PrefixMap::iterator it_map = prefixTable.find(prefix);
    PrefixVector::iterator it_vec;
    for(it_map = prefixTable.begin(); it_map != prefixTable.end(); it_map++){

        it_vec = (*it_map).second.begin();

        for(; it_vec!=(*it_map).second.end(); it_vec++ )
        {
            if((*it_vec).prefix == prefix && (*it_vec).hops == hops)
                return  true;
        }
    }

    return false;
}

std::vector<OSPFN::adv_prefix> OSPFN::Router::getPrefixesToAdvertise(){

    std::vector<chunk_t> lsa_req_v; //empty;
    return getPrefixesToAdvertise(lsa_req_v);
}

std::vector<OSPFN::adv_prefix> OSPFN::Router::getPrefixesToAdvertise(std::vector<chunk_t> lsa_req_v){

    std::vector<OSPFN::adv_prefix> prefix_vec;
    PrefixMap::iterator it_map;
    PrefixVector::iterator it_vec;

    bool isDesired;
    for (it_map = prefixTable.begin(); it_map != prefixTable.end(); it_map++) {

        //    addForwardingEntry((*it).first,(*it2).first, (*it2).second.src);

        it_vec = (*it_map).second.begin();

       for(; it_vec!=(*it_map).second.end(); it_vec++ )
       {
           isDesired = true;
           for(int i = 0; i < lsa_req_v.size(); i++){
              if (lsa_req_v[i] == (*it_vec).prefix){
                  isDesired = false;
                  break;
              }
            }

           if((*it_vec).isAdvertisable == true && isDesired == true){

              OSPFN::adv_prefix prefix_entry;
              prefix_entry.prefix = (*it_vec).prefix;
              prefix_entry.hops = (*it_vec).hops;
              prefix_vec.push_back(prefix_entry);
           }
       }

//
//            if((*it).isAdvertisable == true){
//                OSPFN::adv_prefix prefix_entry;
//                prefix_entry.prefix = (*it_map).prefix;
//                prefix_entry.hops = (*it_map).hops;
//                prefix_vec.push_back(prefix_entry);
//            }
           // forwardingTable->addL2FwdRule((*it_map).first.c_str(),(*it2).first, (*it2).second.src);

    }


    return prefix_vec;
}

void OSPFN::Router::addInterface(OSPFN::Interface* intf) {

    intf->setRouter(this);

    PrefixMap::iterator it;
    for (it = prefixTable.begin(); it != prefixTable.end(); it++) {
        intf->addPrefixToRetransmissionList((*it).first.c_str());
    }

    associatedInterfaces.push_back(intf);
}

bool OSPFN::Router::floodHello() {

    long interfaceCount = associatedInterfaces.size();
    bool result = false;
    for (long i = 0; i < interfaceCount; i++) {
        if (associatedInterfaces[i]->floodHello()) {
            result = true;
        }
    }
    return result;
}

OSPFN::Router::~Router() {

    int interfaceNum = associatedInterfaces.size();
    for (int i = 0; i < interfaceNum; i++) {
        delete (associatedInterfaces[i]);
    }
    associatedInterfaces.clear();


    prefixTable.clear();


//    long areaCount = areas.size();
//    for (long i = 0; i < areaCount; i++) {
//        delete areas[i];
//    }
//    long lsaCount = asExternalLSAs.size();
//    for (long j = 0; j < lsaCount; j++) {
//        delete asExternalLSAs[j];
//    }
//    long routeCount = routingTable.size();
//    for (long k = 0; k < routeCount; k++) {
//        delete routingTable[k];
//    }
    //messageHandler->clearTimer(ageTimer);
//    delete ageTimer;


    delete messageHandler;
}

void OSPFN::Router::addWatches() {
//    WATCH(routerID);
//    WATCH_PTRVECTOR(areas);
//    WATCH_PTRVECTOR(asExternalLSAs);
//    WATCH_PTRVECTOR(routingTable);
}

int OSPFN::Router::getQntOfPrefixEntry(chunk_t prefix){

   return prefixTable[prefix].size();
}

void OSPFN::Router::clearNeighborhood(){

    int interfaceNum = associatedInterfaces.size();
    for (int i = 0; i < interfaceNum; i++) {
        associatedInterfaces[i]->clearNeighborhood();
    }
}

void OSPFN::Router::dumpPrefixTable(){

    PrefixMap::iterator it_map;
    PrefixVector::iterator it_vec;
    PRINT_ERR << "[DumpPrefixTable]:"<<getMessageHandler()->getOSPFNModule()->getParentModule()->getName() << ENDL;
    for (it_map = prefixTable.begin(); it_map != prefixTable.end(); it_map++) {

       it_vec = (*it_map).second.begin();
       int i = 0;
       for(; it_vec != (*it_map).second.end(); it_vec++ )
       {
           PRINT_ERR << ++i<<": name: " << (*it_vec).prefix
                   << " src: " << (*it_vec).src
                   << " dst: " << (*it_vec).dst
                   << " hops: " << (*it_vec).hops
                   << " isLocal: " << (*it_vec).isLocal
                   << " isAdv: " << (*it_vec).isAdvertisable
                   << ENDL;
       }

    }

}

std::vector<chunk_t> OSPFN::Router::getDesiredPrefix(std::vector<chunk_t> prefix_list){

    std::vector<chunk_t> desired_prefix;
    bool isDesired;
    PrefixMap::iterator it_map;
    for (it_map = prefixTable.begin(); it_map != prefixTable.end(); it_map++) {

        isDesired = true;
        for(int i = 0; i < desired_prefix.size(); i++){
            if( desired_prefix[i] == (*it_map).first )
            {
                isDesired = false;
                break;
            }
        }
        if(isDesired)
            desired_prefix.push_back((*it_map).first);
    }

    return desired_prefix;
}

void OSPFN::Router::clearPrefixTable(){

    //PRINT_ERR << "Before: \n";
   // dumpPrefixTable();
    PrefixMap::iterator it_map;
    PrefixVector::iterator it_vec;
    for (it_map = prefixTable.begin(); it_map != prefixTable.end();) {

        //    addForwardingEntry((*it).first,(*it2).first, (*it2).second.src);

        it_vec = (*it_map).second.begin();

       for(; it_vec!=(*it_map).second.end(); )
       {
           if((*it_vec).isLocal == false){
               it_vec = (*it_map).second.erase(it_vec);
           }else
               it_vec++;
       }

       if((*it_map).second.size() == 0 )
           it_map = prefixTable.erase(it_map);
       else
           it_map++;
    }
   // PRINT_ERR << "After: \n";
    //dumpPrefixTable();

    return;
}

void OSPFN::Router::rebuildForwardingTable(){
   //     dumpPrefixTable();

    forwardingTable->clear();

    //Calculate Shortest Path.
    PrefixMap::iterator it_map;
    PrefixVector::iterator it_vec, it_tmp;
    for (it_map = prefixTable.begin(); it_map != prefixTable.end(); it_map++) {

         it_vec = (*it_map).second.begin();
         ASSERT((*it_map).second.size());
          if((*it_map).second.size() != 1){
              int hops = 255;

              for(; it_vec!=(*it_map).second.end(); it_vec++ )
              {
                  if((*it_vec).hops < hops){
                      hops = (*it_vec).hops;
                      it_tmp = it_vec;
                  }
              }

              if(hops == 255)
                  opp_error("Router::rebuildRoutingTable: invalid PrefixMap (prefix,hops)");

              it_vec = it_tmp;
          }
          forwardingTable->addL2FwdRule((*it_vec).prefix.c_str(),(*it_vec).dst, (*it_vec).src, (*it_vec).isLocal,
                                      (*it_vec).hops,(*it_vec).isAdvertisable );
        }

      //  for(it2 =(*it).second.begin(); it2 != (*it).second.end(); it2++) {
            // std::cerr << (*it).first << " => dst: " << (*it2).first << " src: " <<(*it2).second.src << " hops: " << (*it2).second.hops << ENDL;
            //addForwardingEntry((*it).first,(*it2).first, (*it2).second.src);
         //   forwardingTable->addL2FwdRule((*it).first.c_str(),(*it2).first, (*it2).second.src, (*it2).second.isLocal, (*it2).second.hops,(*it2).second.isAdvertisable );
       // }

}
