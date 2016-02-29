//
// Generated file, do not edit! Created by nedtool 4.6 from ospfn/OSPFNPacket.msg.
//

#ifndef _OSPFNPACKET_M_H_
#define _OSPFNPACKET_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "IPv4Address.h"
#include "MACAddress.h"
using namespace inet;
// }}

/**
 * Enum generated from <tt>ospfn/OSPFNPacket.msg:30</tt> by nedtool.
 * <pre>
 * enum OSPFNPacketType
 * {
 * 
 *     OSPFN_HELLO_PACKET = 1;
 *     OSPFN_DATABASE_DESCRIPTION_PACKET = 2;
 *     OSPFN_LINKSTATE_REQUEST_PACKET = 3;
 *     OSPFN_LINKSTATE_UPDATE_PACKET = 4;
 *     OSPFN_LINKSTATE_ACKNOWLEDGEMENT_PACKET = 5;
 * }
 * </pre>
 */
enum OSPFNPacketType {
    OSPFN_HELLO_PACKET = 1,
    OSPFN_DATABASE_DESCRIPTION_PACKET = 2,
    OSPFN_LINKSTATE_REQUEST_PACKET = 3,
    OSPFN_LINKSTATE_UPDATE_PACKET = 4,
    OSPFN_LINKSTATE_ACKNOWLEDGEMENT_PACKET = 5
};

/**
 * Struct generated from ospfn/OSPFNPacket.msg:40 by nedtool.
 */
struct OSPFNOptions
{
    OSPFNOptions();
    bool unused_1;
    bool E_ExternalRoutingCapability;
    bool MC_MulticastForwarding;
    bool NP_Type7LSA;
    bool EA_ForwardExternalLSAs;
    bool DC_DemandCircuits;
    bool unused_2;
    bool unused_3;
};

void doPacking(cCommBuffer *b, OSPFNOptions& a);
void doUnpacking(cCommBuffer *b, OSPFNOptions& a);

/**
 * Class generated from <tt>ospfn/OSPFNPacket.msg:55</tt> by nedtool.
 * <pre>
 * //
 * // Represents an OSPFN packet header
 * //
 * packet OSPFNPacket
 * {
 *     char version = 2;
 *     char type @enum(OSPFNPacketType);
 *     string routerID;
 *     string destination;
 * 
 *     //MACAddress areaID;
 * 
 *     //short authenticationType = 0;
 *     //char authentication[8];
 * }
 * </pre>
 */
class OSPFNPacket : public ::cPacket
{
  protected:
    char version_var;
    char type_var;
    opp_string routerID_var;
    opp_string destination_var;

  private:
    void copy(const OSPFNPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const OSPFNPacket&);

  public:
    OSPFNPacket(const char *name=NULL, int kind=0);
    OSPFNPacket(const OSPFNPacket& other);
    virtual ~OSPFNPacket();
    OSPFNPacket& operator=(const OSPFNPacket& other);
    virtual OSPFNPacket *dup() const {return new OSPFNPacket(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual char getVersion() const;
    virtual void setVersion(char version);
    virtual char getType() const;
    virtual void setType(char type);
    virtual const char * getRouterID() const;
    virtual void setRouterID(const char * routerID);
    virtual const char * getDestination() const;
    virtual void setDestination(const char * destination);
};

inline void doPacking(cCommBuffer *b, OSPFNPacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, OSPFNPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>ospfn/OSPFNPacket.msg:71</tt> by nedtool.
 * <pre>
 * //
 * // Represents an OSPFN Hello packet
 * //
 * packet OSPFNHelloPacket extends OSPFNPacket
 * {
 *     string contentName;
 *     short helloInterval = 5;
 *     type = OSPFN_HELLO_PACKET; //6.2.10 Assignment of Inherited Fields
 *  //   OSPFNOptions options;
 * 
 *     char routerPriority = 0;
 *     long routerDeadInterval = 0;
 * 
 * 
 *     MACAddress designatedRouter;
 *     MACAddress backupDesignatedRouter;
 *     MACAddress neighbor[];
 * }
 * </pre>
 */
class OSPFNHelloPacket : public ::OSPFNPacket
{
  protected:
    opp_string contentName_var;
    short helloInterval_var;
    char routerPriority_var;
    long routerDeadInterval_var;
    MACAddress designatedRouter_var;
    MACAddress backupDesignatedRouter_var;
    MACAddress *neighbor_var; // array ptr
    unsigned int neighbor_arraysize;

  private:
    void copy(const OSPFNHelloPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const OSPFNHelloPacket&);

  public:
    OSPFNHelloPacket(const char *name=NULL, int kind=0);
    OSPFNHelloPacket(const OSPFNHelloPacket& other);
    virtual ~OSPFNHelloPacket();
    OSPFNHelloPacket& operator=(const OSPFNHelloPacket& other);
    virtual OSPFNHelloPacket *dup() const {return new OSPFNHelloPacket(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual const char * getContentName() const;
    virtual void setContentName(const char * contentName);
    virtual short getHelloInterval() const;
    virtual void setHelloInterval(short helloInterval);
    virtual char getRouterPriority() const;
    virtual void setRouterPriority(char routerPriority);
    virtual long getRouterDeadInterval() const;
    virtual void setRouterDeadInterval(long routerDeadInterval);
    virtual MACAddress& getDesignatedRouter();
    virtual const MACAddress& getDesignatedRouter() const {return const_cast<OSPFNHelloPacket*>(this)->getDesignatedRouter();}
    virtual void setDesignatedRouter(const MACAddress& designatedRouter);
    virtual MACAddress& getBackupDesignatedRouter();
    virtual const MACAddress& getBackupDesignatedRouter() const {return const_cast<OSPFNHelloPacket*>(this)->getBackupDesignatedRouter();}
    virtual void setBackupDesignatedRouter(const MACAddress& backupDesignatedRouter);
    virtual void setNeighborArraySize(unsigned int size);
    virtual unsigned int getNeighborArraySize() const;
    virtual MACAddress& getNeighbor(unsigned int k);
    virtual const MACAddress& getNeighbor(unsigned int k) const {return const_cast<OSPFNHelloPacket*>(this)->getNeighbor(k);}
    virtual void setNeighbor(unsigned int k, const MACAddress& neighbor);
};

inline void doPacking(cCommBuffer *b, OSPFNHelloPacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, OSPFNHelloPacket& obj) {obj.parsimUnpack(b);}

/**
 * Enum generated from <tt>ospfn/OSPFNPacket.msg:88</tt> by nedtool.
 * <pre>
 * //
 * enum OSPFNLSAType
 * {
 * 
 *     OFPSN_ROUTERLSA_TYPE = 1;
 *     OFPSN_NETWORKLSA_TYPE = 2;
 *     OFPSN_SUMMARYLSA_NETWORKS_TYPE = 3;
 *     OFPSN_SUMMARYLSA_ASBOUNDARYROUTERS_TYPE = 4;
 *     OFPSN_AS_EXTERNAL_LSA_TYPE = 5;
 * }
 * </pre>
 */
enum OSPFNLSAType {
    OFPSN_ROUTERLSA_TYPE = 1,
    OFPSN_NETWORKLSA_TYPE = 2,
    OFPSN_SUMMARYLSA_NETWORKS_TYPE = 3,
    OFPSN_SUMMARYLSA_ASBOUNDARYROUTERS_TYPE = 4,
    OFPSN_AS_EXTERNAL_LSA_TYPE = 5
};

/**
 * Class generated from <tt>ospfn/OSPFNPacket.msg:100</tt> by nedtool.
 * <pre>
 * //
 * ////
 * //// Represents an OSPFN LSA header
 * ////
 * class OSPFNLSAHeader
 * {
 *     unsigned short lsAge = 0;
 *     OSPFNOptions lsOptions;
 *     char lsType @enum(OSPFNLSAType) = OFPSN_ROUTERLSA_TYPE;
 *     IPv4Address linkStateID;
 *     IPv4Address advertisingRouter;
 *     long lsSequenceNumber = 0;
 *     unsigned short lsaLength = 0;
 * }
 * </pre>
 */
class OSPFNLSAHeader : public ::cObject
{
  protected:
    unsigned short lsAge_var;
    OSPFNOptions lsOptions_var;
    char lsType_var;
    IPv4Address linkStateID_var;
    IPv4Address advertisingRouter_var;
    long lsSequenceNumber_var;
    unsigned short lsaLength_var;

  private:
    void copy(const OSPFNLSAHeader& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const OSPFNLSAHeader&);

  public:
    OSPFNLSAHeader();
    OSPFNLSAHeader(const OSPFNLSAHeader& other);
    virtual ~OSPFNLSAHeader();
    OSPFNLSAHeader& operator=(const OSPFNLSAHeader& other);
    virtual OSPFNLSAHeader *dup() const {return new OSPFNLSAHeader(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual unsigned short getLsAge() const;
    virtual void setLsAge(unsigned short lsAge);
    virtual OSPFNOptions& getLsOptions();
    virtual const OSPFNOptions& getLsOptions() const {return const_cast<OSPFNLSAHeader*>(this)->getLsOptions();}
    virtual void setLsOptions(const OSPFNOptions& lsOptions);
    virtual char getLsType() const;
    virtual void setLsType(char lsType);
    virtual IPv4Address& getLinkStateID();
    virtual const IPv4Address& getLinkStateID() const {return const_cast<OSPFNLSAHeader*>(this)->getLinkStateID();}
    virtual void setLinkStateID(const IPv4Address& linkStateID);
    virtual IPv4Address& getAdvertisingRouter();
    virtual const IPv4Address& getAdvertisingRouter() const {return const_cast<OSPFNLSAHeader*>(this)->getAdvertisingRouter();}
    virtual void setAdvertisingRouter(const IPv4Address& advertisingRouter);
    virtual long getLsSequenceNumber() const;
    virtual void setLsSequenceNumber(long lsSequenceNumber);
    virtual unsigned short getLsaLength() const;
    virtual void setLsaLength(unsigned short lsaLength);
};

inline void doPacking(cCommBuffer *b, OSPFNLSAHeader& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, OSPFNLSAHeader& obj) {obj.parsimUnpack(b);}

/**
 * Struct generated from ospfn/OSPFNPacket.msg:205 by nedtool.
 */
struct OSPFNDDOptions
{
    OSPFNDDOptions();
    bool unused_1;
    bool unused_2;
    bool unused_3;
    bool unused_4;
    bool unused_5;
    bool I_Init;
    bool M_More;
    bool MS_MasterSlave;
};

void doPacking(cCommBuffer *b, OSPFNDDOptions& a);
void doUnpacking(cCommBuffer *b, OSPFNDDOptions& a);

/**
 * Class generated from <tt>ospfn/OSPFNPacket.msg:220</tt> by nedtool.
 * <pre>
 * //
 * ////
 * //// Represents an OSPFN Database Description packet
 * ////
 * packet OSPFNDatabaseDescriptionPacket extends OSPFNPacket
 * {
 *     unsigned short interfaceMTU;
 *     type = OSPFN_DATABASE_DESCRIPTION_PACKET;
 *     OSPFNOptions options;
 *     OSPFNDDOptions ddOptions;
 *     unsigned long ddSequenceNumber;
 *     //OSPFNLSAHeader lsaHeaders[];
 *     string lsaHeaders[];
 * 
 * }
 * </pre>
 */
class OSPFNDatabaseDescriptionPacket : public ::OSPFNPacket
{
  protected:
    unsigned short interfaceMTU_var;
    OSPFNOptions options_var;
    OSPFNDDOptions ddOptions_var;
    unsigned long ddSequenceNumber_var;
    opp_string *lsaHeaders_var; // array ptr
    unsigned int lsaHeaders_arraysize;

  private:
    void copy(const OSPFNDatabaseDescriptionPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const OSPFNDatabaseDescriptionPacket&);

  public:
    OSPFNDatabaseDescriptionPacket(const char *name=NULL, int kind=0);
    OSPFNDatabaseDescriptionPacket(const OSPFNDatabaseDescriptionPacket& other);
    virtual ~OSPFNDatabaseDescriptionPacket();
    OSPFNDatabaseDescriptionPacket& operator=(const OSPFNDatabaseDescriptionPacket& other);
    virtual OSPFNDatabaseDescriptionPacket *dup() const {return new OSPFNDatabaseDescriptionPacket(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual unsigned short getInterfaceMTU() const;
    virtual void setInterfaceMTU(unsigned short interfaceMTU);
    virtual OSPFNOptions& getOptions();
    virtual const OSPFNOptions& getOptions() const {return const_cast<OSPFNDatabaseDescriptionPacket*>(this)->getOptions();}
    virtual void setOptions(const OSPFNOptions& options);
    virtual OSPFNDDOptions& getDdOptions();
    virtual const OSPFNDDOptions& getDdOptions() const {return const_cast<OSPFNDatabaseDescriptionPacket*>(this)->getDdOptions();}
    virtual void setDdOptions(const OSPFNDDOptions& ddOptions);
    virtual unsigned long getDdSequenceNumber() const;
    virtual void setDdSequenceNumber(unsigned long ddSequenceNumber);
    virtual void setLsaHeadersArraySize(unsigned int size);
    virtual unsigned int getLsaHeadersArraySize() const;
    virtual const char * getLsaHeaders(unsigned int k) const;
    virtual void setLsaHeaders(unsigned int k, const char * lsaHeaders);
};

inline void doPacking(cCommBuffer *b, OSPFNDatabaseDescriptionPacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, OSPFNDatabaseDescriptionPacket& obj) {obj.parsimUnpack(b);}

/**
 * Struct generated from ospfn/OSPFNPacket.msg:232 by nedtool.
 */
struct OSPFNLSARequest
{
    OSPFNLSARequest();
    unsigned long lsType;
    IPv4Address linkStateID;
    IPv4Address advertisingRouter;
};

void doPacking(cCommBuffer *b, OSPFNLSARequest& a);
void doUnpacking(cCommBuffer *b, OSPFNLSARequest& a);

/**
 * Class generated from <tt>ospfn/OSPFNPacket.msg:242</tt> by nedtool.
 * <pre>
 * //
 * ////
 * //// Represents an OSPFN Link State Request packet
 * ////
 * packet OSPFNLinkStateRequestPacket extends OSPFNPacket
 * {
 *     OSPFNLSARequest requests[];
 *     string LSAs[];
 *   //  int hops[];
 * }
 * </pre>
 */
class OSPFNLinkStateRequestPacket : public ::OSPFNPacket
{
  protected:
    OSPFNLSARequest *requests_var; // array ptr
    unsigned int requests_arraysize;
    opp_string *LSAs_var; // array ptr
    unsigned int LSAs_arraysize;

  private:
    void copy(const OSPFNLinkStateRequestPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const OSPFNLinkStateRequestPacket&);

  public:
    OSPFNLinkStateRequestPacket(const char *name=NULL, int kind=0);
    OSPFNLinkStateRequestPacket(const OSPFNLinkStateRequestPacket& other);
    virtual ~OSPFNLinkStateRequestPacket();
    OSPFNLinkStateRequestPacket& operator=(const OSPFNLinkStateRequestPacket& other);
    virtual OSPFNLinkStateRequestPacket *dup() const {return new OSPFNLinkStateRequestPacket(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual void setRequestsArraySize(unsigned int size);
    virtual unsigned int getRequestsArraySize() const;
    virtual OSPFNLSARequest& getRequests(unsigned int k);
    virtual const OSPFNLSARequest& getRequests(unsigned int k) const {return const_cast<OSPFNLinkStateRequestPacket*>(this)->getRequests(k);}
    virtual void setRequests(unsigned int k, const OSPFNLSARequest& requests);
    virtual void setLSAsArraySize(unsigned int size);
    virtual unsigned int getLSAsArraySize() const;
    virtual const char * getLSAs(unsigned int k) const;
    virtual void setLSAs(unsigned int k, const char * LSAs);
};

inline void doPacking(cCommBuffer *b, OSPFNLinkStateRequestPacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, OSPFNLinkStateRequestPacket& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>ospfn/OSPFNPacket.msg:264</tt> by nedtool.
 * <pre>
 * //
 * ////
 * //// Represents an OSPFN Link State Update packet
 * ////
 * //packet OSPFNLinkStateUpdatePacket extends OSPFNPacket
 * //{
 * //    unsigned long numberOfLSAs;
 * //    OSPFNRouterLSA routerLSAs[];
 * //    OSPFNNetworkLSA networkLSAs[];
 * //    OSPFNSummaryLSA summaryLSAs[];
 * //    OSPFNASExternalLSA asExternalLSAs[];
 * //}
 * //
 * ////
 * //// Represents an OSPFN Link State Acknowledgement packet
 * ////
 * packet OSPFNLinkStateAcknowledgementPacket extends OSPFNPacket
 * {
 *     string LSAs[];
 *     int hops[];
 * }
 * </pre>
 */
class OSPFNLinkStateAcknowledgementPacket : public ::OSPFNPacket
{
  protected:
    opp_string *LSAs_var; // array ptr
    unsigned int LSAs_arraysize;
    int *hops_var; // array ptr
    unsigned int hops_arraysize;

  private:
    void copy(const OSPFNLinkStateAcknowledgementPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const OSPFNLinkStateAcknowledgementPacket&);

  public:
    OSPFNLinkStateAcknowledgementPacket(const char *name=NULL, int kind=0);
    OSPFNLinkStateAcknowledgementPacket(const OSPFNLinkStateAcknowledgementPacket& other);
    virtual ~OSPFNLinkStateAcknowledgementPacket();
    OSPFNLinkStateAcknowledgementPacket& operator=(const OSPFNLinkStateAcknowledgementPacket& other);
    virtual OSPFNLinkStateAcknowledgementPacket *dup() const {return new OSPFNLinkStateAcknowledgementPacket(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual void setLSAsArraySize(unsigned int size);
    virtual unsigned int getLSAsArraySize() const;
    virtual const char * getLSAs(unsigned int k) const;
    virtual void setLSAs(unsigned int k, const char * LSAs);
    virtual void setHopsArraySize(unsigned int size);
    virtual unsigned int getHopsArraySize() const;
    virtual int getHops(unsigned int k) const;
    virtual void setHops(unsigned int k, int hops);
};

inline void doPacking(cCommBuffer *b, OSPFNLinkStateAcknowledgementPacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, OSPFNLinkStateAcknowledgementPacket& obj) {obj.parsimUnpack(b);}


#endif // ifndef _OSPFNPACKET_M_H_

