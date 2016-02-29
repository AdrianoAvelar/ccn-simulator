//
// Generated file, do not edit! Created by nedtool 4.6 from CcnPacket.msg.
//

#ifndef _CCNPACKET_M_H_
#define _CCNPACKET_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "INETDefs.h"
#include "RawPacket.h"
using namespace inet;
// }}

/**
 * Enum generated from <tt>CcnPacket.msg:22</tt> by nedtool.
 * <pre>
 * enum CcnMessageType
 * {
 * 
 *     CCN_INTEREST = 24;
 *     CCN_CONTENT = 42;
 * }
 * </pre>
 */
enum CcnMessageType {
    CCN_INTEREST = 24,
    CCN_CONTENT = 42
};

/**
 * Class generated from <tt>CcnPacket.msg:37</tt> by nedtool.
 * <pre>
 * //      This is a container for the CCN packet handed by the CCNlite core.
 * //      One can place here additional extension header fields for different 
 * //      experiments (e.g. we use the CS-id of the cache that consumes an 
 * //      Interest in our experiments with transport strategies). 
 * //
 * // ByteArrayMessage is an INET defined type for dynamically varying packet
 * // sizes, which allows us to store in it the CCN packet
 * //
 * packet CcnPacket extends RawPacket
 * {
 *     byteLength = 4;		// Set initial size of packet upon construction to 
 *     					// automatically account for the extra fields added below.
 *     					// Thereafter when creating a new CcnPacket be carefull to 
 *     					// use the addByteLength() method instead of addByteLength()
 *     					// to correctly set the size of the packet!  
 *     int type @enum(CcnMessageType); //Type of CCN Packet
 * 
 *     int chunkSize = 0;
 * 
 *     int hops = 0; //hop count
 *     int dstIface = 0;
 * 
 *     //Prob-Cache decision strategy
 *     int TSB = 0; //Time Since Birth
 *     int TSI = 0; //Time Since Injection
 *     double capacity = 0; //Path capacity
 * 
 *     //Priority Cache
 *     double SumDi = 0;
 *     double TotDelay = 0;
 *     int priority = 0;
 *     double senderTime = 0; //Sender Time.
 *     int rank = 0;
 *     string consumer;
 *     //Betweenness decision strategy
 *     double btw = 0;// carries the higher betweenness identified by the interest packet
 * 
 * 
 * }
 * </pre>
 */
class CcnPacket : public ::RawPacket
{
  protected:
    int type_var;
    int chunkSize_var;
    int hops_var;
    int dstIface_var;
    int TSB_var;
    int TSI_var;
    double capacity_var;
    double SumDi_var;
    double TotDelay_var;
    int priority_var;
    double senderTime_var;
    int rank_var;
    opp_string consumer_var;
    double btw_var;

  private:
    void copy(const CcnPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const CcnPacket&);

  public:
    CcnPacket(const char *name=NULL, int kind=0);
    CcnPacket(const CcnPacket& other);
    virtual ~CcnPacket();
    CcnPacket& operator=(const CcnPacket& other);
    virtual CcnPacket *dup() const {return new CcnPacket(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getType() const;
    virtual void setType(int type);
    virtual int getChunkSize() const;
    virtual void setChunkSize(int chunkSize);
    virtual int getHops() const;
    virtual void setHops(int hops);
    virtual int getDstIface() const;
    virtual void setDstIface(int dstIface);
    virtual int getTSB() const;
    virtual void setTSB(int TSB);
    virtual int getTSI() const;
    virtual void setTSI(int TSI);
    virtual double getCapacity() const;
    virtual void setCapacity(double capacity);
    virtual double getSumDi() const;
    virtual void setSumDi(double SumDi);
    virtual double getTotDelay() const;
    virtual void setTotDelay(double TotDelay);
    virtual int getPriority() const;
    virtual void setPriority(int priority);
    virtual double getSenderTime() const;
    virtual void setSenderTime(double senderTime);
    virtual int getRank() const;
    virtual void setRank(int rank);
    virtual const char * getConsumer() const;
    virtual void setConsumer(const char * consumer);
    virtual double getBtw() const;
    virtual void setBtw(double btw);
};

inline void doPacking(cCommBuffer *b, CcnPacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, CcnPacket& obj) {obj.parsimUnpack(b);}


#endif // ifndef _CCNPACKET_M_H_

