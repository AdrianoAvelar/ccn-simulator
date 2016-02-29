//
// Generated file, do not edit! Created by nedtool 4.6 from CcnAppMessage.msg.
//

#ifndef _CCNAPPMESSAGE_M_H_
#define _CCNAPPMESSAGE_M_H_

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
 * Enum generated from <tt>CcnAppMessage.msg:30</tt> by nedtool.
 * <pre>
 * // 42 is the Content of the answer to the ultimate question of life.
 * // The ultimate question of life for those Interested is encoded as the reverse of its answer
 * //
 * enum CcnAppMessageType
 * {
 * 
 *     CCN_APP_INTEREST = 24;
 *     CCN_APP_CONTENT = 42;
 * }
 * </pre>
 */
enum CcnAppMessageType {
    CCN_APP_INTEREST = 24,
    CCN_APP_CONTENT = 42
};

/**
 * Enum generated from <tt>CcnAppMessage.msg:39</tt> by nedtool.
 * <pre>
 * // Different possible control/data actions for the relay in regard to named content
 * // May need/want to exend that according to the control interface between app and relay
 * //
 * enum CcnRelayAction
 * {
 * 
 *     CONTENT_REGISTER = 421;
 *     CONTENT_UNREGISTER = 422;
 *     CONTENT_DELIVER = 423;
 *     CONTENT_SENDER_REGISTER = 424;
 * }
 * </pre>
 */
enum CcnRelayAction {
    CONTENT_REGISTER = 421,
    CONTENT_UNREGISTER = 422,
    CONTENT_DELIVER = 423,
    CONTENT_SENDER_REGISTER = 424
};

/**
 * Class generated from <tt>CcnAppMessage.msg:51</tt> by nedtool.
 * <pre>
 * // This is a message exchanged between the CCN layer and the Layer above 
 * // (strategy or application). Can be extended to enable various signalling/data 
 * // operations between the two (see some options in the commented code)
 * //
 * packet CcnAppMessage extends RawPacket
 * {
 *     int type @enum(CcnAppMessageType);
 *     int action @enum(CcnRelayAction);
 *     string contentName;
 *     int seqNr;		// for CCN_APP_INTEREST & CCN_APP_CONTENT, the chunk seq num;
 *     					// for CCN_APP_CONTENT registration, the start chunk of a range of chunks to be registered so that the cache is the content source 
 *     int numChunks;	// for CCN_APP_CONTENT registration requests, the num of chunks to be registered so that the cache is the content source
 *     int chunkSize;	// for CCN_APP_CONTENT registration requests, the size of each chunk, serialised in the ByteArray
 * 
 *     int appId = 0;			//Like a PORT Application.
 *     int hops;
 *     int dstGate = 0;
 * 
 *     string lsa;			//for ospfn. should not be here.
 *     int lsaHops;
 *     string consumer;
 * 
 *     // string dest;		//e.g. for installing redirection rules or FIB rules   
 *     // int timeOut; 	//e.g. for testing a timeout strategy
 *     // int expire;		//e.g. for setting a content to timeout
 *     // bool register;	//e.g. for register/unregister content 
 * }
 * </pre>
 */
class CcnAppMessage : public ::RawPacket
{
  protected:
    int type_var;
    int action_var;
    opp_string contentName_var;
    int seqNr_var;
    int numChunks_var;
    int chunkSize_var;
    int appId_var;
    int hops_var;
    int dstGate_var;
    opp_string lsa_var;
    int lsaHops_var;
    opp_string consumer_var;

  private:
    void copy(const CcnAppMessage& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const CcnAppMessage&);

  public:
    CcnAppMessage(const char *name=NULL, int kind=0);
    CcnAppMessage(const CcnAppMessage& other);
    virtual ~CcnAppMessage();
    CcnAppMessage& operator=(const CcnAppMessage& other);
    virtual CcnAppMessage *dup() const {return new CcnAppMessage(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getType() const;
    virtual void setType(int type);
    virtual int getAction() const;
    virtual void setAction(int action);
    virtual const char * getContentName() const;
    virtual void setContentName(const char * contentName);
    virtual int getSeqNr() const;
    virtual void setSeqNr(int seqNr);
    virtual int getNumChunks() const;
    virtual void setNumChunks(int numChunks);
    virtual int getChunkSize() const;
    virtual void setChunkSize(int chunkSize);
    virtual int getAppId() const;
    virtual void setAppId(int appId);
    virtual int getHops() const;
    virtual void setHops(int hops);
    virtual int getDstGate() const;
    virtual void setDstGate(int dstGate);
    virtual const char * getLsa() const;
    virtual void setLsa(const char * lsa);
    virtual int getLsaHops() const;
    virtual void setLsaHops(int lsaHops);
    virtual const char * getConsumer() const;
    virtual void setConsumer(const char * consumer);
};

inline void doPacking(cCommBuffer *b, CcnAppMessage& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, CcnAppMessage& obj) {obj.parsimUnpack(b);}


#endif // ifndef _CCNAPPMESSAGE_M_H_
