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

#ifndef OSPFN_NEIGHBOR_H_
#define OSPFN_NEIGHBOR_H_

#ifndef __INET_OSPFNEIGHBOR_H
#define __INET_OSPFNEIGHBOR_H

#include <list>
#include "OSPFNInterface.h"
//#include "LSA.h"
#include "OSPFNcommon.h"
#include "OSPFNPacket_m.h"
#include "OSPFNTimer_m.h"
#include "OSPFNNeighborState.h"

namespace OSPFN {

class NeighborState;
class Interface;

class Neighbor {
//
friend class NeighborState;
//
public:

//    struct DDPacketID {
//        OSPFDDOptions   ddOptions;
//        OSPFOptions     options;
//        unsigned long   sequenceNumber;
//    };

//private:
//    struct TransmittedLSA {
//        LSAKeyType      lsaKey;
//        unsigned short  age;
//    };
//
private:
    NeighborState*                      state;
    NeighborState*                      previousState;
    OSPFNTimer*                         inactivityTimer;
    OSPFNTimer*                         pollTimer;
    OSPFNTimer*                         ddRetransmissionTimer;
    OSPFNTimer*                         updateRetransmissionTimer;
    bool                               updateRetransmissionTimerActive;
    OSPFNTimer*                         requestRetransmissionTimer;
    bool                               requestRetransmissionTimerActive;
    DatabaseExchangeRelationshipType    databaseExchangeRelationship;
    bool                               firstAdjacencyInited;
    unsigned long                     ddSequenceNumber;
//  DDPacketID                          lastReceivedDDPacket;
    string                              neighborID;
    unsigned char                     neighborPriority;
//  MACAddress                          neighborAddress;
    MACAddress                          neighborSrcAddress;
    MACAddress                          neighborDestAddress;
//  OSPFOptions                         neighborOptions;
    DesignatedRouterID                  neighborsDesignatedRouter;
    DesignatedRouterID                  neighborsBackupDesignatedRouter;
    bool                               designatedRoutersSetUp;
    short                              neighborsRouterDeadInterval;
//  std::list<OSPFLSA*>                 linkStateRetransmissionList;
//  std::list<OSPFLSAHeader*>           databaseSummaryList;
//  std::list<OSPFLSAHeader*>           linkStateRequestList;
//  std::list<TransmittedLSA>           transmittedLSAs;
    OSPFNDatabaseDescriptionPacket*     lastTransmittedDDPacket;

    Interface*                          parentInterface;

    // TODO: Should come from a global unique number generator module.
    static unsigned long                ddSequenceNumberInitSeed;

//private:
    void changeState(NeighborState* newState, NeighborState* currentState);
//
public:
   // Neighbor(RouterID neighbor = NULL_ROUTERID);
    Neighbor(std::string neighbor);
//
    virtual ~Neighbor();
//
    void                processEvent(NeighborEventType event);
    void                reset();
    void                initFirstAdjacency();
    NeighborStateType   getState() const;
    static const char*  getStateString(NeighborStateType stateType);
    void                sendDatabaseDescriptionPacket();
    bool                retransmitDatabaseDescriptionPacket();
//    void                createDatabaseSummary();
    void                sendLinkStateRequestPacket(std::vector<chunk_t> desired_prefixs);
//    void                retransmitUpdatePacket();
    bool                needAdjacency();
//    void                addToRetransmissionList(OSPFLSA* lsa);
//    void                removeFromRetransmissionList(LSAKeyType lsaKey);
//    bool                isLinkStateRequestListEmpty(LSAKeyType lsaKey) const;
//    OSPFLSA*            findOnRetransmissionList(LSAKeyType lsaKey);
//    void                startUpdateRetransmissionTimer();
    void                clearUpdateRetransmissionTimer();
//    void                addToRequestList(OSPFLSAHeader* lsaHeader);
//    void                removeFromRequestList(LSAKeyType lsaKey);
//    bool                isLSAOnRequestList(LSAKeyType lsaKey) const;
//    OSPFLSAHeader*      findOnRequestList(LSAKeyType lsaKey);
    void                startRequestRetransmissionTimer();
    void                clearRequestRetransmissionTimer();
//    void                addToTransmittedLSAList(LSAKeyType lsaKey);
//    bool                isOnTransmittedLSAList(LSAKeyType lsaKey) const;
//    void                ageTransmittedLSAList();
    unsigned long       getUniqueULong();
//    void                deleteLastSentDDPacket();
//
    void                setNeighborID(string id)  { neighborID = id; }
    string            getNeighborID() const  { return neighborID; }
//    void                setPriority(unsigned char priority)  { neighborPriority = priority; }
//    unsigned char       getPriority() const  { return neighborPriority; }
//    void                setAddress(MACAddress address)  { isLinkStateRequestListEmptysetSrcAddr(address); }
    void                setSrcAddr(MACAddress address){ neighborSrcAddress = address; };
    MACAddress                getSrcAddr(){return neighborSrcAddress;}

    void                setDestAddr(MACAddress address){ neighborDestAddress = address; };
    MACAddress           getDestAddr() const {return neighborDestAddress;}
    MACAddress           getAddress() { return getSrcAddr(); }
//    void                setDesignatedRouter(DesignatedRouterID routerID)  { neighborsDesignatedRouter = routerID; }
//    DesignatedRouterID  getDesignatedRouter() const  { return neighborsDesignatedRouter; }
//    void                setBackupDesignatedRouter(DesignatedRouterID routerID)  { neighborsBackupDesignatedRouter = routerID; }
//    DesignatedRouterID  getBackupDesignatedRouter() const  { return neighborsBackupDesignatedRouter; }
//    void                setRouterDeadInterval(short interval)  { neighborsRouterDeadInterval = interval; }
    short               getRouterDeadInterval() const  { return neighborsRouterDeadInterval; }
//    void                setDDSequenceNumber(unsigned long sequenceNumber)  { ddSequenceNumber = sequenceNumber; }
//    unsigned long       getDDSequenceNumber() const  { return ddSequenceNumber; }
//    void                setOptions(OSPFOptions options)  { neighborOptions = options; }
//    OSPFOptions         getOptions() const  { return neighborOptions; }
//    void                setLastReceivedDDPacket(DDPacketID packetID)  { lastReceivedDDPacket = packetID; }
//    DDPacketID          getLastReceivedDDPacket() const  { return lastReceivedDDPacket; }
//
//    void                                setDatabaseExchangeRelationship(DatabaseExchangeRelationshipType relation) { databaseExchangeRelationship = relation; }
//    DatabaseExchangeRelationshipType    getDatabaseExchangeRelationship() const  { return databaseExchangeRelationship; }
//
    void                setInterface(Interface* intf)  { parentInterface = intf; }
    Interface*          getInterface()  { return parentInterface; }
//    const Interface*    getInterface() const  { return parentInterface; }
//
    OSPFNTimer*          getInactivityTimer()  { return inactivityTimer; }
    OSPFNTimer*          getPollTimer()  { return pollTimer; }
    OSPFNTimer*          getDDRetransmissionTimer()  { return ddRetransmissionTimer; }
//    OSPFNTimer*          getUpdateRetransmissionTimer()  { return updateRetransmissionTimer; }
//    bool                isUpdateRetransmissionTimerActive() const  { return updateRetransmissionTimerActive; }
//    bool                isRequestRetransmissionTimerActive() const  { return requestRetransmissionTimerActive; }
    bool                isFirstAdjacencyInited() const  { return firstAdjacencyInited; }
//    bool                designatedRoutersAreSetUp() const  { return designatedRoutersSetUp; }
//    void                setupDesignatedRouters(bool setUp)  { designatedRoutersSetUp = setUp; }
//    unsigned long       getDatabaseSummaryListCount() const  { return databaseSummaryList.size(); }
//
    void incrementDDSequenceNumber()  { ddSequenceNumber++; }
//    bool isLinkStateRequestListEmpty() const { return linkStateRequestList.empty(); }
//    bool isLinkStateRequestListEmpty() ;
//    bool isLinkStateRetransmissionListEmpty() const { return linkStateRetransmissionList.empty(); }
//    void popFirstLinkStateRequest()  { linkStateRequestList.pop_front(); }
};

} // namespace OSPF

//inline bool operator==(OSPFN::Neighbor::DDPacketID leftID, OSPFN::Neighbor::DDPacketID rightID)
//{
//    return ((leftID.ddOptions.I_Init == rightID.ddOptions.I_Init) &&
//            (leftID.ddOptions.M_More == rightID.ddOptions.M_More) &&
//            (leftID.ddOptions.MS_MasterSlave == rightID.ddOptions.MS_MasterSlave) &&
//            (leftID.options == rightID.options) &&
//            (leftID.sequenceNumber == rightID.sequenceNumber));
//}
//
//inline bool operator!=(OSPFN::Neighbor::DDPacketID leftID, OSPFN::Neighbor::DDPacketID rightID)
//{
//    return (!(leftID == rightID));
//}

#endif // __INET_OSPFNEIGHBOR_H
#endif /* NEIGHBOR_H_ */
