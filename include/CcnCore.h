/*
 * CcnCore.h
 *
 * Generic c++ stub for the CCN lite core.
 *
 * The wrapper is written such that multiple versions (e.g. different versions of CCN lite or other
 * such stub) can be accommodated seamlessly in the same experimental setup. (If things won't
 * work when using different versions in an experiment chances are that the different versions are
 * shamefully incompatible!).
 *
 *  Created on: Aug 11, 2012
 *      Author: manolis sifalakis
 */


#ifndef CCN_CORE_H_
#define CCN_CORE_H_

/* ***********************************************************************************************
 * Class CcnCORE provides access to the CCN protocol
 * ***********************************************************************************************/
#include "Ccn.h"
#include "Ccnr.h"
#include "base_cache.h"
#include "CcnPacket_m.h"
#include "CcnAppMessage_m.h"
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

class Ccn;

#define STAT_INTERVAL 1.0
#define PIT_MAX_SIZE 1000

#define FLOOD_TAG "/all"
#define FLOOD 0x01
#define ONLY_FORWARD 0x02

typedef boost::unordered_map < std::string , MACAddress > INTERFACES;

//This structure takes care of data forwarding
struct pit_entry {
   // MACAddress src; //Pit has a list of interfaces.
    //MACAddress dst; //Pit has a list of interfaces.
    INTERFACES faces;
    boost::unordered_set<int> nonces;
    simtime_t time;
};


typedef boost::unordered_map <chunk_t, pit_entry > PIT_TABLE;

#include <omnetpp.h>

class CcnCore : public cSimpleModule
{

public:

    ~CcnCore();
    CcnCore();
    //CcnCore (Ccn *owner,  const char *nodeName, const char *coreVer);

    virtual void    initialize();
    virtual void    handleMessage(cMessage* msg);
    virtual void    finish();


    /** Express Interest for named content. Return 1/true on success or 0/false on failure */
    void requestContent (CcnPacket *ccnPkt, int arrivalGateId);
    //void forwardingInterest(chunk_t chunk, void * = 0, int size = 0);
    void sendInterest(CcnPacket *ccnPkt); //fromUpperLayer
    void forwardingInterest(CcnPacket* ccnPkt);//fromLowerLayer
    //void forwardingObject(chunk_t chunk,void *data, int size, double delayed = 0);
    void forwardingObject(CcnPacket *ccnPkt);

    PIT_TABLE::iterator pitLookup(std::string contentName);
    void dumpPIT();
    void addPITRule(const char *srcAddr, const char *dstAddr,
            chunk_t chunk);

    /** Add to cache a buffer of content chunks of equal size. Return the number of chunks successfully added to CS */
    int addToCacheFixedSizeChunks (const char *contentName, const int numChunks,
            const int chunkSize);

    int addFileToCache(const char* contentName, const char* localPath);

    /** Pass packet received from the MAC layer to the relay. Return 1/true on success or 0/false on failure */

    void fromMACFace(CcnPacket *ccnPkt, CcnContext *ccnCtx);

    /** Add a FIB rule using L2 ID (MAC address). Return success/fail */
    //bool addL2FwdRule (const char *contentName,  MACAddress destAddr, int localNetifIndex);
    bool addRule(const char *contentName, MACAddress srcAddr,MACAddress dstAddr,bool isLocal = false);
    bool toMACFace (int type, const char *dstAddr, const char *srcAddr, const char *contentName,
            void* data = 0,int len = 0, double delayed = 0);

    bool toMACFace(const char *srcAddr, const char *dstAddr, CcnPacket *ccnPkt);

    //bool deliverContent (const char *contentName, void *data, int len);
    bool deliverContent(CcnPacket* ccnPkt);

    void registerContent(const char *contentName, void *data, int len);

    std::string macToString( char * mac) ;
    bool isThisDestination(MACAddress dst);

    void flood(CcnPacket *ccnPkt);
    int checkSpecialNames(const chunk_t chunk);
    void onlyForwardInterest(CcnPacket *ccnPkt);

    inline void setCcnModule(Ccn *ccnModule){
        this->ccnModule = ccnModule;
    }

    void sendInterestToListeners(CcnPacket *ccnPkt);

private:

       ForwardingTable *ccnfib;


       int debugLevel;
       std::string     relayName;
       std::string     coreVersion;
       Ccn             *ccnModule;
       void            *ctrlBlock;
       double RTT;
       base_cache *contentStore;

       PIT_TABLE PIT;

       //Can we use only one timeout for PIT and FIB?
       double timeoutPIT;
       double timeoutFIB;

       cMessage *pitTimeoutMsg;
       cMessage *fibTimeoutMsg;

       cMessage *statistic;
       Ccnr* ccnr;
       bool hasCcnr;

       //cOutVector pitSizeVector;
       cOutVector hit_hop;

       //Betweenness decision strategy
       double my_btw;
       //double tmp_btw;

       int server_hit;

       uint32_t tot_pkt;
       double tot_delay;

       //Signals
       simsignal_t pitsizeSignal;
};


#endif /* CCN_CORE_H_ */
