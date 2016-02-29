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

#ifndef FORWARDINGTABLE_H_
#define FORWARDINGTABLE_H_

#include <omnetpp.h>

#include "IInterfaceTable.h"
#include <boost/unordered_map.hpp>
#include "ccnsim.h"
#include "shared.h"
#include "Util.h"
#include "XMLUtils.h"

using namespace inet;

//This structure takes care of data forwarding
struct fib_entry {
    MACAddress src;
    MACAddress dst;
    int hops;
    bool isAdv;
    bool isLocal ;
    bool permantent;
    simtime_t time;
};

#define DEFAULT_PREFIX "/default_gw"
#define FIB_ENTRY_TIMEOUT 10

static std::ostream& operator<<(std::ostream& os, const fib_entry& fib){
    os << "src: " << fib.src << "  dst: " << fib.dst << " isLocal: " <<
            fib.isLocal << " hops:" << fib.hops << " isAdv: " << fib.isAdv << " t:" << fib.time; // no endl!
    return os;
}

class ForwardingTable: public cSimpleModule {



public:
    ForwardingTable();
    virtual ~ForwardingTable();

    void configureRouterId();
    void printForwardingTable();

    typedef std::map < chunk_t , fib_entry > FIB_TABLE;

    FIB_TABLE::iterator lookup(std::string contentName);
    bool isInTable(chunk_t content);

    FIB_TABLE getTable();
    FIB_TABLE *getTablePtr();


    bool addL2FwdRule(const char *contentName, MACAddress srcAddr,
            MACAddress dstAddr, bool isLocal , int hops , bool isAdv );
    bool addOrUpdateL2FwdRule(const char *contentName, MACAddress srcAddr,
            MACAddress dstAddr, bool isLocal, int hops, bool isAdv);

    string getRouterName();
    string getRouterNamePrefix();
    void setRouterId(MACAddress mac);
    MACAddress getRouterId();
    void clear();

    void addDefaultRoutes();

    FIB_TABLE::iterator getDefaultGateway();
    void addDefaultGateway();

protected:

    IInterfaceTable *ift; // cached pointer
//    NotificationBoard *nb; // cached pointer

    virtual int numInitStages() const  {return 4;}
    virtual void initialize(int stage);
    virtual void handleMessage(cMessage *);

    void readTableFromXML(const cXMLElement *ftable);
    void readItemFromXML(const cXMLElement *fitem);
    /**
     * Called by the NotificationBoard whenever a change of a category
     * occurs to which this client has subscribed.
     */
    virtual void receiveChangeNotification(int category,
            const cObject *details);
private:
    FIB_TABLE FIB;
    MACAddress routerId;

};

#endif /* FORWARDINGTABLE_H_ */
