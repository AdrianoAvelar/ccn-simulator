//
// Generated file, do not edit! Created by nedtool 4.6 from ospfn/OSPFNPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "OSPFNPacket_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("OSPFNPacketType");
    if (!e) enums.getInstance()->add(e = new cEnum("OSPFNPacketType"));
    e->insert(OSPFN_HELLO_PACKET, "OSPFN_HELLO_PACKET");
    e->insert(OSPFN_DATABASE_DESCRIPTION_PACKET, "OSPFN_DATABASE_DESCRIPTION_PACKET");
    e->insert(OSPFN_LINKSTATE_REQUEST_PACKET, "OSPFN_LINKSTATE_REQUEST_PACKET");
    e->insert(OSPFN_LINKSTATE_UPDATE_PACKET, "OSPFN_LINKSTATE_UPDATE_PACKET");
    e->insert(OSPFN_LINKSTATE_ACKNOWLEDGEMENT_PACKET, "OSPFN_LINKSTATE_ACKNOWLEDGEMENT_PACKET");
);

OSPFNOptions::OSPFNOptions()
{
    unused_1 = 0;
    E_ExternalRoutingCapability = 0;
    MC_MulticastForwarding = 0;
    NP_Type7LSA = 0;
    EA_ForwardExternalLSAs = 0;
    DC_DemandCircuits = 0;
    unused_2 = 0;
    unused_3 = 0;
}

void doPacking(cCommBuffer *b, OSPFNOptions& a)
{
    doPacking(b,a.unused_1);
    doPacking(b,a.E_ExternalRoutingCapability);
    doPacking(b,a.MC_MulticastForwarding);
    doPacking(b,a.NP_Type7LSA);
    doPacking(b,a.EA_ForwardExternalLSAs);
    doPacking(b,a.DC_DemandCircuits);
    doPacking(b,a.unused_2);
    doPacking(b,a.unused_3);
}

void doUnpacking(cCommBuffer *b, OSPFNOptions& a)
{
    doUnpacking(b,a.unused_1);
    doUnpacking(b,a.E_ExternalRoutingCapability);
    doUnpacking(b,a.MC_MulticastForwarding);
    doUnpacking(b,a.NP_Type7LSA);
    doUnpacking(b,a.EA_ForwardExternalLSAs);
    doUnpacking(b,a.DC_DemandCircuits);
    doUnpacking(b,a.unused_2);
    doUnpacking(b,a.unused_3);
}

class OSPFNOptionsDescriptor : public cClassDescriptor
{
  public:
    OSPFNOptionsDescriptor();
    virtual ~OSPFNOptionsDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(OSPFNOptionsDescriptor);

OSPFNOptionsDescriptor::OSPFNOptionsDescriptor() : cClassDescriptor("OSPFNOptions", "")
{
}

OSPFNOptionsDescriptor::~OSPFNOptionsDescriptor()
{
}

bool OSPFNOptionsDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<OSPFNOptions *>(obj)!=NULL;
}

const char *OSPFNOptionsDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int OSPFNOptionsDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount(object) : 8;
}

unsigned int OSPFNOptionsDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *OSPFNOptionsDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "unused_1",
        "E_ExternalRoutingCapability",
        "MC_MulticastForwarding",
        "NP_Type7LSA",
        "EA_ForwardExternalLSAs",
        "DC_DemandCircuits",
        "unused_2",
        "unused_3",
    };
    return (field>=0 && field<8) ? fieldNames[field] : NULL;
}

int OSPFNOptionsDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='u' && strcmp(fieldName, "unused_1")==0) return base+0;
    if (fieldName[0]=='E' && strcmp(fieldName, "E_ExternalRoutingCapability")==0) return base+1;
    if (fieldName[0]=='M' && strcmp(fieldName, "MC_MulticastForwarding")==0) return base+2;
    if (fieldName[0]=='N' && strcmp(fieldName, "NP_Type7LSA")==0) return base+3;
    if (fieldName[0]=='E' && strcmp(fieldName, "EA_ForwardExternalLSAs")==0) return base+4;
    if (fieldName[0]=='D' && strcmp(fieldName, "DC_DemandCircuits")==0) return base+5;
    if (fieldName[0]=='u' && strcmp(fieldName, "unused_2")==0) return base+6;
    if (fieldName[0]=='u' && strcmp(fieldName, "unused_3")==0) return base+7;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *OSPFNOptionsDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "bool",
        "bool",
        "bool",
        "bool",
        "bool",
        "bool",
        "bool",
        "bool",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : NULL;
}

const char *OSPFNOptionsDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int OSPFNOptionsDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNOptions *pp = (OSPFNOptions *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string OSPFNOptionsDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNOptions *pp = (OSPFNOptions *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->unused_1);
        case 1: return bool2string(pp->E_ExternalRoutingCapability);
        case 2: return bool2string(pp->MC_MulticastForwarding);
        case 3: return bool2string(pp->NP_Type7LSA);
        case 4: return bool2string(pp->EA_ForwardExternalLSAs);
        case 5: return bool2string(pp->DC_DemandCircuits);
        case 6: return bool2string(pp->unused_2);
        case 7: return bool2string(pp->unused_3);
        default: return "";
    }
}

bool OSPFNOptionsDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNOptions *pp = (OSPFNOptions *)object; (void)pp;
    switch (field) {
        case 0: pp->unused_1 = string2bool(value); return true;
        case 1: pp->E_ExternalRoutingCapability = string2bool(value); return true;
        case 2: pp->MC_MulticastForwarding = string2bool(value); return true;
        case 3: pp->NP_Type7LSA = string2bool(value); return true;
        case 4: pp->EA_ForwardExternalLSAs = string2bool(value); return true;
        case 5: pp->DC_DemandCircuits = string2bool(value); return true;
        case 6: pp->unused_2 = string2bool(value); return true;
        case 7: pp->unused_3 = string2bool(value); return true;
        default: return false;
    }
}

const char *OSPFNOptionsDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *OSPFNOptionsDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNOptions *pp = (OSPFNOptions *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(OSPFNPacket);

OSPFNPacket::OSPFNPacket(const char *name, int kind) : ::cPacket(name,kind)
{
    this->version_var = 2;
    this->type_var = 0;
    this->routerID_var = 0;
    this->destination_var = 0;
}

OSPFNPacket::OSPFNPacket(const OSPFNPacket& other) : ::cPacket(other)
{
    copy(other);
}

OSPFNPacket::~OSPFNPacket()
{
}

OSPFNPacket& OSPFNPacket::operator=(const OSPFNPacket& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void OSPFNPacket::copy(const OSPFNPacket& other)
{
    this->version_var = other.version_var;
    this->type_var = other.type_var;
    this->routerID_var = other.routerID_var;
    this->destination_var = other.destination_var;
}

void OSPFNPacket::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->version_var);
    doPacking(b,this->type_var);
    doPacking(b,this->routerID_var);
    doPacking(b,this->destination_var);
}

void OSPFNPacket::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->type_var);
    doUnpacking(b,this->routerID_var);
    doUnpacking(b,this->destination_var);
}

char OSPFNPacket::getVersion() const
{
    return version_var;
}

void OSPFNPacket::setVersion(char version)
{
    this->version_var = version;
}

char OSPFNPacket::getType() const
{
    return type_var;
}

void OSPFNPacket::setType(char type)
{
    this->type_var = type;
}

const char * OSPFNPacket::getRouterID() const
{
    return routerID_var.c_str();
}

void OSPFNPacket::setRouterID(const char * routerID)
{
    this->routerID_var = routerID;
}

const char * OSPFNPacket::getDestination() const
{
    return destination_var.c_str();
}

void OSPFNPacket::setDestination(const char * destination)
{
    this->destination_var = destination;
}

class OSPFNPacketDescriptor : public cClassDescriptor
{
  public:
    OSPFNPacketDescriptor();
    virtual ~OSPFNPacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(OSPFNPacketDescriptor);

OSPFNPacketDescriptor::OSPFNPacketDescriptor() : cClassDescriptor("OSPFNPacket", "cPacket")
{
}

OSPFNPacketDescriptor::~OSPFNPacketDescriptor()
{
}

bool OSPFNPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<OSPFNPacket *>(obj)!=NULL;
}

const char *OSPFNPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int OSPFNPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int OSPFNPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *OSPFNPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "version",
        "type",
        "routerID",
        "destination",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int OSPFNPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+1;
    if (fieldName[0]=='r' && strcmp(fieldName, "routerID")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "destination")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *OSPFNPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "char",
        "char",
        "string",
        "string",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *OSPFNPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 1:
            if (!strcmp(propertyname,"enum")) return "OSPFNPacketType";
            return NULL;
        default: return NULL;
    }
}

int OSPFNPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNPacket *pp = (OSPFNPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string OSPFNPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNPacket *pp = (OSPFNPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getVersion());
        case 1: return long2string(pp->getType());
        case 2: return oppstring2string(pp->getRouterID());
        case 3: return oppstring2string(pp->getDestination());
        default: return "";
    }
}

bool OSPFNPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNPacket *pp = (OSPFNPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setVersion(string2long(value)); return true;
        case 1: pp->setType(string2long(value)); return true;
        case 2: pp->setRouterID((value)); return true;
        case 3: pp->setDestination((value)); return true;
        default: return false;
    }
}

const char *OSPFNPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *OSPFNPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNPacket *pp = (OSPFNPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(OSPFNHelloPacket);

OSPFNHelloPacket::OSPFNHelloPacket(const char *name, int kind) : ::OSPFNPacket(name,kind)
{
    this->setType(OSPFN_HELLO_PACKET);

    this->contentName_var = 0;
    this->helloInterval_var = 5;
    this->routerPriority_var = 0;
    this->routerDeadInterval_var = 0;
    neighbor_arraysize = 0;
    this->neighbor_var = 0;
}

OSPFNHelloPacket::OSPFNHelloPacket(const OSPFNHelloPacket& other) : ::OSPFNPacket(other)
{
    neighbor_arraysize = 0;
    this->neighbor_var = 0;
    copy(other);
}

OSPFNHelloPacket::~OSPFNHelloPacket()
{
    delete [] neighbor_var;
}

OSPFNHelloPacket& OSPFNHelloPacket::operator=(const OSPFNHelloPacket& other)
{
    if (this==&other) return *this;
    ::OSPFNPacket::operator=(other);
    copy(other);
    return *this;
}

void OSPFNHelloPacket::copy(const OSPFNHelloPacket& other)
{
    this->contentName_var = other.contentName_var;
    this->helloInterval_var = other.helloInterval_var;
    this->routerPriority_var = other.routerPriority_var;
    this->routerDeadInterval_var = other.routerDeadInterval_var;
    this->designatedRouter_var = other.designatedRouter_var;
    this->backupDesignatedRouter_var = other.backupDesignatedRouter_var;
    delete [] this->neighbor_var;
    this->neighbor_var = (other.neighbor_arraysize==0) ? NULL : new MACAddress[other.neighbor_arraysize];
    neighbor_arraysize = other.neighbor_arraysize;
    for (unsigned int i=0; i<neighbor_arraysize; i++)
        this->neighbor_var[i] = other.neighbor_var[i];
}

void OSPFNHelloPacket::parsimPack(cCommBuffer *b)
{
    ::OSPFNPacket::parsimPack(b);
    doPacking(b,this->contentName_var);
    doPacking(b,this->helloInterval_var);
    doPacking(b,this->routerPriority_var);
    doPacking(b,this->routerDeadInterval_var);
    doPacking(b,this->designatedRouter_var);
    doPacking(b,this->backupDesignatedRouter_var);
    b->pack(neighbor_arraysize);
    doPacking(b,this->neighbor_var,neighbor_arraysize);
}

void OSPFNHelloPacket::parsimUnpack(cCommBuffer *b)
{
    ::OSPFNPacket::parsimUnpack(b);
    doUnpacking(b,this->contentName_var);
    doUnpacking(b,this->helloInterval_var);
    doUnpacking(b,this->routerPriority_var);
    doUnpacking(b,this->routerDeadInterval_var);
    doUnpacking(b,this->designatedRouter_var);
    doUnpacking(b,this->backupDesignatedRouter_var);
    delete [] this->neighbor_var;
    b->unpack(neighbor_arraysize);
    if (neighbor_arraysize==0) {
        this->neighbor_var = 0;
    } else {
        this->neighbor_var = new MACAddress[neighbor_arraysize];
        doUnpacking(b,this->neighbor_var,neighbor_arraysize);
    }
}

const char * OSPFNHelloPacket::getContentName() const
{
    return contentName_var.c_str();
}

void OSPFNHelloPacket::setContentName(const char * contentName)
{
    this->contentName_var = contentName;
}

short OSPFNHelloPacket::getHelloInterval() const
{
    return helloInterval_var;
}

void OSPFNHelloPacket::setHelloInterval(short helloInterval)
{
    this->helloInterval_var = helloInterval;
}

char OSPFNHelloPacket::getRouterPriority() const
{
    return routerPriority_var;
}

void OSPFNHelloPacket::setRouterPriority(char routerPriority)
{
    this->routerPriority_var = routerPriority;
}

long OSPFNHelloPacket::getRouterDeadInterval() const
{
    return routerDeadInterval_var;
}

void OSPFNHelloPacket::setRouterDeadInterval(long routerDeadInterval)
{
    this->routerDeadInterval_var = routerDeadInterval;
}

MACAddress& OSPFNHelloPacket::getDesignatedRouter()
{
    return designatedRouter_var;
}

void OSPFNHelloPacket::setDesignatedRouter(const MACAddress& designatedRouter)
{
    this->designatedRouter_var = designatedRouter;
}

MACAddress& OSPFNHelloPacket::getBackupDesignatedRouter()
{
    return backupDesignatedRouter_var;
}

void OSPFNHelloPacket::setBackupDesignatedRouter(const MACAddress& backupDesignatedRouter)
{
    this->backupDesignatedRouter_var = backupDesignatedRouter;
}

void OSPFNHelloPacket::setNeighborArraySize(unsigned int size)
{
    MACAddress *neighbor_var2 = (size==0) ? NULL : new MACAddress[size];
    unsigned int sz = neighbor_arraysize < size ? neighbor_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        neighbor_var2[i] = this->neighbor_var[i];
    neighbor_arraysize = size;
    delete [] this->neighbor_var;
    this->neighbor_var = neighbor_var2;
}

unsigned int OSPFNHelloPacket::getNeighborArraySize() const
{
    return neighbor_arraysize;
}

MACAddress& OSPFNHelloPacket::getNeighbor(unsigned int k)
{
    if (k>=neighbor_arraysize) throw cRuntimeError("Array of size %d indexed by %d", neighbor_arraysize, k);
    return neighbor_var[k];
}

void OSPFNHelloPacket::setNeighbor(unsigned int k, const MACAddress& neighbor)
{
    if (k>=neighbor_arraysize) throw cRuntimeError("Array of size %d indexed by %d", neighbor_arraysize, k);
    this->neighbor_var[k] = neighbor;
}

class OSPFNHelloPacketDescriptor : public cClassDescriptor
{
  public:
    OSPFNHelloPacketDescriptor();
    virtual ~OSPFNHelloPacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(OSPFNHelloPacketDescriptor);

OSPFNHelloPacketDescriptor::OSPFNHelloPacketDescriptor() : cClassDescriptor("OSPFNHelloPacket", "OSPFNPacket")
{
}

OSPFNHelloPacketDescriptor::~OSPFNHelloPacketDescriptor()
{
}

bool OSPFNHelloPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<OSPFNHelloPacket *>(obj)!=NULL;
}

const char *OSPFNHelloPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int OSPFNHelloPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int OSPFNHelloPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISARRAY | FD_ISCOMPOUND,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *OSPFNHelloPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "contentName",
        "helloInterval",
        "routerPriority",
        "routerDeadInterval",
        "designatedRouter",
        "backupDesignatedRouter",
        "neighbor",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int OSPFNHelloPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "contentName")==0) return base+0;
    if (fieldName[0]=='h' && strcmp(fieldName, "helloInterval")==0) return base+1;
    if (fieldName[0]=='r' && strcmp(fieldName, "routerPriority")==0) return base+2;
    if (fieldName[0]=='r' && strcmp(fieldName, "routerDeadInterval")==0) return base+3;
    if (fieldName[0]=='d' && strcmp(fieldName, "designatedRouter")==0) return base+4;
    if (fieldName[0]=='b' && strcmp(fieldName, "backupDesignatedRouter")==0) return base+5;
    if (fieldName[0]=='n' && strcmp(fieldName, "neighbor")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *OSPFNHelloPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "short",
        "char",
        "long",
        "MACAddress",
        "MACAddress",
        "MACAddress",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *OSPFNHelloPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int OSPFNHelloPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNHelloPacket *pp = (OSPFNHelloPacket *)object; (void)pp;
    switch (field) {
        case 6: return pp->getNeighborArraySize();
        default: return 0;
    }
}

std::string OSPFNHelloPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNHelloPacket *pp = (OSPFNHelloPacket *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getContentName());
        case 1: return long2string(pp->getHelloInterval());
        case 2: return long2string(pp->getRouterPriority());
        case 3: return long2string(pp->getRouterDeadInterval());
        case 4: {std::stringstream out; out << pp->getDesignatedRouter(); return out.str();}
        case 5: {std::stringstream out; out << pp->getBackupDesignatedRouter(); return out.str();}
        case 6: {std::stringstream out; out << pp->getNeighbor(i); return out.str();}
        default: return "";
    }
}

bool OSPFNHelloPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNHelloPacket *pp = (OSPFNHelloPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setContentName((value)); return true;
        case 1: pp->setHelloInterval(string2long(value)); return true;
        case 2: pp->setRouterPriority(string2long(value)); return true;
        case 3: pp->setRouterDeadInterval(string2long(value)); return true;
        default: return false;
    }
}

const char *OSPFNHelloPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 4: return opp_typename(typeid(MACAddress));
        case 5: return opp_typename(typeid(MACAddress));
        case 6: return opp_typename(typeid(MACAddress));
        default: return NULL;
    };
}

void *OSPFNHelloPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNHelloPacket *pp = (OSPFNHelloPacket *)object; (void)pp;
    switch (field) {
        case 4: return (void *)(&pp->getDesignatedRouter()); break;
        case 5: return (void *)(&pp->getBackupDesignatedRouter()); break;
        case 6: return (void *)(&pp->getNeighbor(i)); break;
        default: return NULL;
    }
}

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("OSPFNLSAType");
    if (!e) enums.getInstance()->add(e = new cEnum("OSPFNLSAType"));
    e->insert(OFPSN_ROUTERLSA_TYPE, "OFPSN_ROUTERLSA_TYPE");
    e->insert(OFPSN_NETWORKLSA_TYPE, "OFPSN_NETWORKLSA_TYPE");
    e->insert(OFPSN_SUMMARYLSA_NETWORKS_TYPE, "OFPSN_SUMMARYLSA_NETWORKS_TYPE");
    e->insert(OFPSN_SUMMARYLSA_ASBOUNDARYROUTERS_TYPE, "OFPSN_SUMMARYLSA_ASBOUNDARYROUTERS_TYPE");
    e->insert(OFPSN_AS_EXTERNAL_LSA_TYPE, "OFPSN_AS_EXTERNAL_LSA_TYPE");
);

Register_Class(OSPFNLSAHeader);

OSPFNLSAHeader::OSPFNLSAHeader() : ::cObject()
{
    this->lsAge_var = 0;
    this->lsType_var = OFPSN_ROUTERLSA_TYPE;
    this->lsSequenceNumber_var = 0;
    this->lsaLength_var = 0;
}

OSPFNLSAHeader::OSPFNLSAHeader(const OSPFNLSAHeader& other) : ::cObject(other)
{
    copy(other);
}

OSPFNLSAHeader::~OSPFNLSAHeader()
{
}

OSPFNLSAHeader& OSPFNLSAHeader::operator=(const OSPFNLSAHeader& other)
{
    if (this==&other) return *this;
    ::cObject::operator=(other);
    copy(other);
    return *this;
}

void OSPFNLSAHeader::copy(const OSPFNLSAHeader& other)
{
    this->lsAge_var = other.lsAge_var;
    this->lsOptions_var = other.lsOptions_var;
    this->lsType_var = other.lsType_var;
    this->linkStateID_var = other.linkStateID_var;
    this->advertisingRouter_var = other.advertisingRouter_var;
    this->lsSequenceNumber_var = other.lsSequenceNumber_var;
    this->lsaLength_var = other.lsaLength_var;
}

void OSPFNLSAHeader::parsimPack(cCommBuffer *b)
{
    doPacking(b,this->lsAge_var);
    doPacking(b,this->lsOptions_var);
    doPacking(b,this->lsType_var);
    doPacking(b,this->linkStateID_var);
    doPacking(b,this->advertisingRouter_var);
    doPacking(b,this->lsSequenceNumber_var);
    doPacking(b,this->lsaLength_var);
}

void OSPFNLSAHeader::parsimUnpack(cCommBuffer *b)
{
    doUnpacking(b,this->lsAge_var);
    doUnpacking(b,this->lsOptions_var);
    doUnpacking(b,this->lsType_var);
    doUnpacking(b,this->linkStateID_var);
    doUnpacking(b,this->advertisingRouter_var);
    doUnpacking(b,this->lsSequenceNumber_var);
    doUnpacking(b,this->lsaLength_var);
}

unsigned short OSPFNLSAHeader::getLsAge() const
{
    return lsAge_var;
}

void OSPFNLSAHeader::setLsAge(unsigned short lsAge)
{
    this->lsAge_var = lsAge;
}

OSPFNOptions& OSPFNLSAHeader::getLsOptions()
{
    return lsOptions_var;
}

void OSPFNLSAHeader::setLsOptions(const OSPFNOptions& lsOptions)
{
    this->lsOptions_var = lsOptions;
}

char OSPFNLSAHeader::getLsType() const
{
    return lsType_var;
}

void OSPFNLSAHeader::setLsType(char lsType)
{
    this->lsType_var = lsType;
}

IPv4Address& OSPFNLSAHeader::getLinkStateID()
{
    return linkStateID_var;
}

void OSPFNLSAHeader::setLinkStateID(const IPv4Address& linkStateID)
{
    this->linkStateID_var = linkStateID;
}

IPv4Address& OSPFNLSAHeader::getAdvertisingRouter()
{
    return advertisingRouter_var;
}

void OSPFNLSAHeader::setAdvertisingRouter(const IPv4Address& advertisingRouter)
{
    this->advertisingRouter_var = advertisingRouter;
}

long OSPFNLSAHeader::getLsSequenceNumber() const
{
    return lsSequenceNumber_var;
}

void OSPFNLSAHeader::setLsSequenceNumber(long lsSequenceNumber)
{
    this->lsSequenceNumber_var = lsSequenceNumber;
}

unsigned short OSPFNLSAHeader::getLsaLength() const
{
    return lsaLength_var;
}

void OSPFNLSAHeader::setLsaLength(unsigned short lsaLength)
{
    this->lsaLength_var = lsaLength;
}

class OSPFNLSAHeaderDescriptor : public cClassDescriptor
{
  public:
    OSPFNLSAHeaderDescriptor();
    virtual ~OSPFNLSAHeaderDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(OSPFNLSAHeaderDescriptor);

OSPFNLSAHeaderDescriptor::OSPFNLSAHeaderDescriptor() : cClassDescriptor("OSPFNLSAHeader", "cObject")
{
}

OSPFNLSAHeaderDescriptor::~OSPFNLSAHeaderDescriptor()
{
}

bool OSPFNLSAHeaderDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<OSPFNLSAHeader *>(obj)!=NULL;
}

const char *OSPFNLSAHeaderDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int OSPFNLSAHeaderDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int OSPFNLSAHeaderDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *OSPFNLSAHeaderDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "lsAge",
        "lsOptions",
        "lsType",
        "linkStateID",
        "advertisingRouter",
        "lsSequenceNumber",
        "lsaLength",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int OSPFNLSAHeaderDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='l' && strcmp(fieldName, "lsAge")==0) return base+0;
    if (fieldName[0]=='l' && strcmp(fieldName, "lsOptions")==0) return base+1;
    if (fieldName[0]=='l' && strcmp(fieldName, "lsType")==0) return base+2;
    if (fieldName[0]=='l' && strcmp(fieldName, "linkStateID")==0) return base+3;
    if (fieldName[0]=='a' && strcmp(fieldName, "advertisingRouter")==0) return base+4;
    if (fieldName[0]=='l' && strcmp(fieldName, "lsSequenceNumber")==0) return base+5;
    if (fieldName[0]=='l' && strcmp(fieldName, "lsaLength")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *OSPFNLSAHeaderDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
        "OSPFNOptions",
        "char",
        "IPv4Address",
        "IPv4Address",
        "long",
        "unsigned short",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *OSPFNLSAHeaderDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 2:
            if (!strcmp(propertyname,"enum")) return "OSPFNLSAType";
            return NULL;
        default: return NULL;
    }
}

int OSPFNLSAHeaderDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNLSAHeader *pp = (OSPFNLSAHeader *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string OSPFNLSAHeaderDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNLSAHeader *pp = (OSPFNLSAHeader *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getLsAge());
        case 1: {std::stringstream out; out << pp->getLsOptions(); return out.str();}
        case 2: return long2string(pp->getLsType());
        case 3: {std::stringstream out; out << pp->getLinkStateID(); return out.str();}
        case 4: {std::stringstream out; out << pp->getAdvertisingRouter(); return out.str();}
        case 5: return long2string(pp->getLsSequenceNumber());
        case 6: return ulong2string(pp->getLsaLength());
        default: return "";
    }
}

bool OSPFNLSAHeaderDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNLSAHeader *pp = (OSPFNLSAHeader *)object; (void)pp;
    switch (field) {
        case 0: pp->setLsAge(string2ulong(value)); return true;
        case 2: pp->setLsType(string2long(value)); return true;
        case 5: pp->setLsSequenceNumber(string2long(value)); return true;
        case 6: pp->setLsaLength(string2ulong(value)); return true;
        default: return false;
    }
}

const char *OSPFNLSAHeaderDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 1: return opp_typename(typeid(OSPFNOptions));
        case 3: return opp_typename(typeid(IPv4Address));
        case 4: return opp_typename(typeid(IPv4Address));
        default: return NULL;
    };
}

void *OSPFNLSAHeaderDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNLSAHeader *pp = (OSPFNLSAHeader *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getLsOptions()); break;
        case 3: return (void *)(&pp->getLinkStateID()); break;
        case 4: return (void *)(&pp->getAdvertisingRouter()); break;
        default: return NULL;
    }
}

OSPFNDDOptions::OSPFNDDOptions()
{
    unused_1 = 0;
    unused_2 = 0;
    unused_3 = 0;
    unused_4 = 0;
    unused_5 = 0;
    I_Init = 0;
    M_More = 0;
    MS_MasterSlave = 0;
}

void doPacking(cCommBuffer *b, OSPFNDDOptions& a)
{
    doPacking(b,a.unused_1);
    doPacking(b,a.unused_2);
    doPacking(b,a.unused_3);
    doPacking(b,a.unused_4);
    doPacking(b,a.unused_5);
    doPacking(b,a.I_Init);
    doPacking(b,a.M_More);
    doPacking(b,a.MS_MasterSlave);
}

void doUnpacking(cCommBuffer *b, OSPFNDDOptions& a)
{
    doUnpacking(b,a.unused_1);
    doUnpacking(b,a.unused_2);
    doUnpacking(b,a.unused_3);
    doUnpacking(b,a.unused_4);
    doUnpacking(b,a.unused_5);
    doUnpacking(b,a.I_Init);
    doUnpacking(b,a.M_More);
    doUnpacking(b,a.MS_MasterSlave);
}

class OSPFNDDOptionsDescriptor : public cClassDescriptor
{
  public:
    OSPFNDDOptionsDescriptor();
    virtual ~OSPFNDDOptionsDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(OSPFNDDOptionsDescriptor);

OSPFNDDOptionsDescriptor::OSPFNDDOptionsDescriptor() : cClassDescriptor("OSPFNDDOptions", "")
{
}

OSPFNDDOptionsDescriptor::~OSPFNDDOptionsDescriptor()
{
}

bool OSPFNDDOptionsDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<OSPFNDDOptions *>(obj)!=NULL;
}

const char *OSPFNDDOptionsDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int OSPFNDDOptionsDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount(object) : 8;
}

unsigned int OSPFNDDOptionsDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *OSPFNDDOptionsDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "unused_1",
        "unused_2",
        "unused_3",
        "unused_4",
        "unused_5",
        "I_Init",
        "M_More",
        "MS_MasterSlave",
    };
    return (field>=0 && field<8) ? fieldNames[field] : NULL;
}

int OSPFNDDOptionsDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='u' && strcmp(fieldName, "unused_1")==0) return base+0;
    if (fieldName[0]=='u' && strcmp(fieldName, "unused_2")==0) return base+1;
    if (fieldName[0]=='u' && strcmp(fieldName, "unused_3")==0) return base+2;
    if (fieldName[0]=='u' && strcmp(fieldName, "unused_4")==0) return base+3;
    if (fieldName[0]=='u' && strcmp(fieldName, "unused_5")==0) return base+4;
    if (fieldName[0]=='I' && strcmp(fieldName, "I_Init")==0) return base+5;
    if (fieldName[0]=='M' && strcmp(fieldName, "M_More")==0) return base+6;
    if (fieldName[0]=='M' && strcmp(fieldName, "MS_MasterSlave")==0) return base+7;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *OSPFNDDOptionsDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "bool",
        "bool",
        "bool",
        "bool",
        "bool",
        "bool",
        "bool",
        "bool",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : NULL;
}

const char *OSPFNDDOptionsDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int OSPFNDDOptionsDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNDDOptions *pp = (OSPFNDDOptions *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string OSPFNDDOptionsDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNDDOptions *pp = (OSPFNDDOptions *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->unused_1);
        case 1: return bool2string(pp->unused_2);
        case 2: return bool2string(pp->unused_3);
        case 3: return bool2string(pp->unused_4);
        case 4: return bool2string(pp->unused_5);
        case 5: return bool2string(pp->I_Init);
        case 6: return bool2string(pp->M_More);
        case 7: return bool2string(pp->MS_MasterSlave);
        default: return "";
    }
}

bool OSPFNDDOptionsDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNDDOptions *pp = (OSPFNDDOptions *)object; (void)pp;
    switch (field) {
        case 0: pp->unused_1 = string2bool(value); return true;
        case 1: pp->unused_2 = string2bool(value); return true;
        case 2: pp->unused_3 = string2bool(value); return true;
        case 3: pp->unused_4 = string2bool(value); return true;
        case 4: pp->unused_5 = string2bool(value); return true;
        case 5: pp->I_Init = string2bool(value); return true;
        case 6: pp->M_More = string2bool(value); return true;
        case 7: pp->MS_MasterSlave = string2bool(value); return true;
        default: return false;
    }
}

const char *OSPFNDDOptionsDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *OSPFNDDOptionsDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNDDOptions *pp = (OSPFNDDOptions *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(OSPFNDatabaseDescriptionPacket);

OSPFNDatabaseDescriptionPacket::OSPFNDatabaseDescriptionPacket(const char *name, int kind) : ::OSPFNPacket(name,kind)
{
    this->setType(OSPFN_DATABASE_DESCRIPTION_PACKET);

    this->interfaceMTU_var = 0;
    this->ddSequenceNumber_var = 0;
    lsaHeaders_arraysize = 0;
    this->lsaHeaders_var = 0;
}

OSPFNDatabaseDescriptionPacket::OSPFNDatabaseDescriptionPacket(const OSPFNDatabaseDescriptionPacket& other) : ::OSPFNPacket(other)
{
    lsaHeaders_arraysize = 0;
    this->lsaHeaders_var = 0;
    copy(other);
}

OSPFNDatabaseDescriptionPacket::~OSPFNDatabaseDescriptionPacket()
{
    delete [] lsaHeaders_var;
}

OSPFNDatabaseDescriptionPacket& OSPFNDatabaseDescriptionPacket::operator=(const OSPFNDatabaseDescriptionPacket& other)
{
    if (this==&other) return *this;
    ::OSPFNPacket::operator=(other);
    copy(other);
    return *this;
}

void OSPFNDatabaseDescriptionPacket::copy(const OSPFNDatabaseDescriptionPacket& other)
{
    this->interfaceMTU_var = other.interfaceMTU_var;
    this->options_var = other.options_var;
    this->ddOptions_var = other.ddOptions_var;
    this->ddSequenceNumber_var = other.ddSequenceNumber_var;
    delete [] this->lsaHeaders_var;
    this->lsaHeaders_var = (other.lsaHeaders_arraysize==0) ? NULL : new opp_string[other.lsaHeaders_arraysize];
    lsaHeaders_arraysize = other.lsaHeaders_arraysize;
    for (unsigned int i=0; i<lsaHeaders_arraysize; i++)
        this->lsaHeaders_var[i] = other.lsaHeaders_var[i];
}

void OSPFNDatabaseDescriptionPacket::parsimPack(cCommBuffer *b)
{
    ::OSPFNPacket::parsimPack(b);
    doPacking(b,this->interfaceMTU_var);
    doPacking(b,this->options_var);
    doPacking(b,this->ddOptions_var);
    doPacking(b,this->ddSequenceNumber_var);
    b->pack(lsaHeaders_arraysize);
    doPacking(b,this->lsaHeaders_var,lsaHeaders_arraysize);
}

void OSPFNDatabaseDescriptionPacket::parsimUnpack(cCommBuffer *b)
{
    ::OSPFNPacket::parsimUnpack(b);
    doUnpacking(b,this->interfaceMTU_var);
    doUnpacking(b,this->options_var);
    doUnpacking(b,this->ddOptions_var);
    doUnpacking(b,this->ddSequenceNumber_var);
    delete [] this->lsaHeaders_var;
    b->unpack(lsaHeaders_arraysize);
    if (lsaHeaders_arraysize==0) {
        this->lsaHeaders_var = 0;
    } else {
        this->lsaHeaders_var = new opp_string[lsaHeaders_arraysize];
        doUnpacking(b,this->lsaHeaders_var,lsaHeaders_arraysize);
    }
}

unsigned short OSPFNDatabaseDescriptionPacket::getInterfaceMTU() const
{
    return interfaceMTU_var;
}

void OSPFNDatabaseDescriptionPacket::setInterfaceMTU(unsigned short interfaceMTU)
{
    this->interfaceMTU_var = interfaceMTU;
}

OSPFNOptions& OSPFNDatabaseDescriptionPacket::getOptions()
{
    return options_var;
}

void OSPFNDatabaseDescriptionPacket::setOptions(const OSPFNOptions& options)
{
    this->options_var = options;
}

OSPFNDDOptions& OSPFNDatabaseDescriptionPacket::getDdOptions()
{
    return ddOptions_var;
}

void OSPFNDatabaseDescriptionPacket::setDdOptions(const OSPFNDDOptions& ddOptions)
{
    this->ddOptions_var = ddOptions;
}

unsigned long OSPFNDatabaseDescriptionPacket::getDdSequenceNumber() const
{
    return ddSequenceNumber_var;
}

void OSPFNDatabaseDescriptionPacket::setDdSequenceNumber(unsigned long ddSequenceNumber)
{
    this->ddSequenceNumber_var = ddSequenceNumber;
}

void OSPFNDatabaseDescriptionPacket::setLsaHeadersArraySize(unsigned int size)
{
    opp_string *lsaHeaders_var2 = (size==0) ? NULL : new opp_string[size];
    unsigned int sz = lsaHeaders_arraysize < size ? lsaHeaders_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        lsaHeaders_var2[i] = this->lsaHeaders_var[i];
    for (unsigned int i=sz; i<size; i++)
        lsaHeaders_var2[i] = 0;
    lsaHeaders_arraysize = size;
    delete [] this->lsaHeaders_var;
    this->lsaHeaders_var = lsaHeaders_var2;
}

unsigned int OSPFNDatabaseDescriptionPacket::getLsaHeadersArraySize() const
{
    return lsaHeaders_arraysize;
}

const char * OSPFNDatabaseDescriptionPacket::getLsaHeaders(unsigned int k) const
{
    if (k>=lsaHeaders_arraysize) throw cRuntimeError("Array of size %d indexed by %d", lsaHeaders_arraysize, k);
    return lsaHeaders_var[k].c_str();
}

void OSPFNDatabaseDescriptionPacket::setLsaHeaders(unsigned int k, const char * lsaHeaders)
{
    if (k>=lsaHeaders_arraysize) throw cRuntimeError("Array of size %d indexed by %d", lsaHeaders_arraysize, k);
    this->lsaHeaders_var[k] = lsaHeaders;
}

class OSPFNDatabaseDescriptionPacketDescriptor : public cClassDescriptor
{
  public:
    OSPFNDatabaseDescriptionPacketDescriptor();
    virtual ~OSPFNDatabaseDescriptionPacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(OSPFNDatabaseDescriptionPacketDescriptor);

OSPFNDatabaseDescriptionPacketDescriptor::OSPFNDatabaseDescriptionPacketDescriptor() : cClassDescriptor("OSPFNDatabaseDescriptionPacket", "OSPFNPacket")
{
}

OSPFNDatabaseDescriptionPacketDescriptor::~OSPFNDatabaseDescriptionPacketDescriptor()
{
}

bool OSPFNDatabaseDescriptionPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<OSPFNDatabaseDescriptionPacket *>(obj)!=NULL;
}

const char *OSPFNDatabaseDescriptionPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int OSPFNDatabaseDescriptionPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int OSPFNDatabaseDescriptionPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *OSPFNDatabaseDescriptionPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "interfaceMTU",
        "options",
        "ddOptions",
        "ddSequenceNumber",
        "lsaHeaders",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int OSPFNDatabaseDescriptionPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='i' && strcmp(fieldName, "interfaceMTU")==0) return base+0;
    if (fieldName[0]=='o' && strcmp(fieldName, "options")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "ddOptions")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "ddSequenceNumber")==0) return base+3;
    if (fieldName[0]=='l' && strcmp(fieldName, "lsaHeaders")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *OSPFNDatabaseDescriptionPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned short",
        "OSPFNOptions",
        "OSPFNDDOptions",
        "unsigned long",
        "string",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *OSPFNDatabaseDescriptionPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int OSPFNDatabaseDescriptionPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNDatabaseDescriptionPacket *pp = (OSPFNDatabaseDescriptionPacket *)object; (void)pp;
    switch (field) {
        case 4: return pp->getLsaHeadersArraySize();
        default: return 0;
    }
}

std::string OSPFNDatabaseDescriptionPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNDatabaseDescriptionPacket *pp = (OSPFNDatabaseDescriptionPacket *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->getInterfaceMTU());
        case 1: {std::stringstream out; out << pp->getOptions(); return out.str();}
        case 2: {std::stringstream out; out << pp->getDdOptions(); return out.str();}
        case 3: return ulong2string(pp->getDdSequenceNumber());
        case 4: return oppstring2string(pp->getLsaHeaders(i));
        default: return "";
    }
}

bool OSPFNDatabaseDescriptionPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNDatabaseDescriptionPacket *pp = (OSPFNDatabaseDescriptionPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setInterfaceMTU(string2ulong(value)); return true;
        case 3: pp->setDdSequenceNumber(string2ulong(value)); return true;
        case 4: pp->setLsaHeaders(i,(value)); return true;
        default: return false;
    }
}

const char *OSPFNDatabaseDescriptionPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 1: return opp_typename(typeid(OSPFNOptions));
        case 2: return opp_typename(typeid(OSPFNDDOptions));
        default: return NULL;
    };
}

void *OSPFNDatabaseDescriptionPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNDatabaseDescriptionPacket *pp = (OSPFNDatabaseDescriptionPacket *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->getOptions()); break;
        case 2: return (void *)(&pp->getDdOptions()); break;
        default: return NULL;
    }
}

OSPFNLSARequest::OSPFNLSARequest()
{
    lsType = 0;
}

void doPacking(cCommBuffer *b, OSPFNLSARequest& a)
{
    doPacking(b,a.lsType);
    doPacking(b,a.linkStateID);
    doPacking(b,a.advertisingRouter);
}

void doUnpacking(cCommBuffer *b, OSPFNLSARequest& a)
{
    doUnpacking(b,a.lsType);
    doUnpacking(b,a.linkStateID);
    doUnpacking(b,a.advertisingRouter);
}

class OSPFNLSARequestDescriptor : public cClassDescriptor
{
  public:
    OSPFNLSARequestDescriptor();
    virtual ~OSPFNLSARequestDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(OSPFNLSARequestDescriptor);

OSPFNLSARequestDescriptor::OSPFNLSARequestDescriptor() : cClassDescriptor("OSPFNLSARequest", "")
{
}

OSPFNLSARequestDescriptor::~OSPFNLSARequestDescriptor()
{
}

bool OSPFNLSARequestDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<OSPFNLSARequest *>(obj)!=NULL;
}

const char *OSPFNLSARequestDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int OSPFNLSARequestDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int OSPFNLSARequestDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *OSPFNLSARequestDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "lsType",
        "linkStateID",
        "advertisingRouter",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int OSPFNLSARequestDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='l' && strcmp(fieldName, "lsType")==0) return base+0;
    if (fieldName[0]=='l' && strcmp(fieldName, "linkStateID")==0) return base+1;
    if (fieldName[0]=='a' && strcmp(fieldName, "advertisingRouter")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *OSPFNLSARequestDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "unsigned long",
        "IPv4Address",
        "IPv4Address",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *OSPFNLSARequestDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int OSPFNLSARequestDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNLSARequest *pp = (OSPFNLSARequest *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string OSPFNLSARequestDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNLSARequest *pp = (OSPFNLSARequest *)object; (void)pp;
    switch (field) {
        case 0: return ulong2string(pp->lsType);
        case 1: {std::stringstream out; out << pp->linkStateID; return out.str();}
        case 2: {std::stringstream out; out << pp->advertisingRouter; return out.str();}
        default: return "";
    }
}

bool OSPFNLSARequestDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNLSARequest *pp = (OSPFNLSARequest *)object; (void)pp;
    switch (field) {
        case 0: pp->lsType = string2ulong(value); return true;
        default: return false;
    }
}

const char *OSPFNLSARequestDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 1: return opp_typename(typeid(IPv4Address));
        case 2: return opp_typename(typeid(IPv4Address));
        default: return NULL;
    };
}

void *OSPFNLSARequestDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNLSARequest *pp = (OSPFNLSARequest *)object; (void)pp;
    switch (field) {
        case 1: return (void *)(&pp->linkStateID); break;
        case 2: return (void *)(&pp->advertisingRouter); break;
        default: return NULL;
    }
}

Register_Class(OSPFNLinkStateRequestPacket);

OSPFNLinkStateRequestPacket::OSPFNLinkStateRequestPacket(const char *name, int kind) : ::OSPFNPacket(name,kind)
{
    requests_arraysize = 0;
    this->requests_var = 0;
    LSAs_arraysize = 0;
    this->LSAs_var = 0;
}

OSPFNLinkStateRequestPacket::OSPFNLinkStateRequestPacket(const OSPFNLinkStateRequestPacket& other) : ::OSPFNPacket(other)
{
    requests_arraysize = 0;
    this->requests_var = 0;
    LSAs_arraysize = 0;
    this->LSAs_var = 0;
    copy(other);
}

OSPFNLinkStateRequestPacket::~OSPFNLinkStateRequestPacket()
{
    delete [] requests_var;
    delete [] LSAs_var;
}

OSPFNLinkStateRequestPacket& OSPFNLinkStateRequestPacket::operator=(const OSPFNLinkStateRequestPacket& other)
{
    if (this==&other) return *this;
    ::OSPFNPacket::operator=(other);
    copy(other);
    return *this;
}

void OSPFNLinkStateRequestPacket::copy(const OSPFNLinkStateRequestPacket& other)
{
    delete [] this->requests_var;
    this->requests_var = (other.requests_arraysize==0) ? NULL : new OSPFNLSARequest[other.requests_arraysize];
    requests_arraysize = other.requests_arraysize;
    for (unsigned int i=0; i<requests_arraysize; i++)
        this->requests_var[i] = other.requests_var[i];
    delete [] this->LSAs_var;
    this->LSAs_var = (other.LSAs_arraysize==0) ? NULL : new opp_string[other.LSAs_arraysize];
    LSAs_arraysize = other.LSAs_arraysize;
    for (unsigned int i=0; i<LSAs_arraysize; i++)
        this->LSAs_var[i] = other.LSAs_var[i];
}

void OSPFNLinkStateRequestPacket::parsimPack(cCommBuffer *b)
{
    ::OSPFNPacket::parsimPack(b);
    b->pack(requests_arraysize);
    doPacking(b,this->requests_var,requests_arraysize);
    b->pack(LSAs_arraysize);
    doPacking(b,this->LSAs_var,LSAs_arraysize);
}

void OSPFNLinkStateRequestPacket::parsimUnpack(cCommBuffer *b)
{
    ::OSPFNPacket::parsimUnpack(b);
    delete [] this->requests_var;
    b->unpack(requests_arraysize);
    if (requests_arraysize==0) {
        this->requests_var = 0;
    } else {
        this->requests_var = new OSPFNLSARequest[requests_arraysize];
        doUnpacking(b,this->requests_var,requests_arraysize);
    }
    delete [] this->LSAs_var;
    b->unpack(LSAs_arraysize);
    if (LSAs_arraysize==0) {
        this->LSAs_var = 0;
    } else {
        this->LSAs_var = new opp_string[LSAs_arraysize];
        doUnpacking(b,this->LSAs_var,LSAs_arraysize);
    }
}

void OSPFNLinkStateRequestPacket::setRequestsArraySize(unsigned int size)
{
    OSPFNLSARequest *requests_var2 = (size==0) ? NULL : new OSPFNLSARequest[size];
    unsigned int sz = requests_arraysize < size ? requests_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        requests_var2[i] = this->requests_var[i];
    requests_arraysize = size;
    delete [] this->requests_var;
    this->requests_var = requests_var2;
}

unsigned int OSPFNLinkStateRequestPacket::getRequestsArraySize() const
{
    return requests_arraysize;
}

OSPFNLSARequest& OSPFNLinkStateRequestPacket::getRequests(unsigned int k)
{
    if (k>=requests_arraysize) throw cRuntimeError("Array of size %d indexed by %d", requests_arraysize, k);
    return requests_var[k];
}

void OSPFNLinkStateRequestPacket::setRequests(unsigned int k, const OSPFNLSARequest& requests)
{
    if (k>=requests_arraysize) throw cRuntimeError("Array of size %d indexed by %d", requests_arraysize, k);
    this->requests_var[k] = requests;
}

void OSPFNLinkStateRequestPacket::setLSAsArraySize(unsigned int size)
{
    opp_string *LSAs_var2 = (size==0) ? NULL : new opp_string[size];
    unsigned int sz = LSAs_arraysize < size ? LSAs_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        LSAs_var2[i] = this->LSAs_var[i];
    for (unsigned int i=sz; i<size; i++)
        LSAs_var2[i] = 0;
    LSAs_arraysize = size;
    delete [] this->LSAs_var;
    this->LSAs_var = LSAs_var2;
}

unsigned int OSPFNLinkStateRequestPacket::getLSAsArraySize() const
{
    return LSAs_arraysize;
}

const char * OSPFNLinkStateRequestPacket::getLSAs(unsigned int k) const
{
    if (k>=LSAs_arraysize) throw cRuntimeError("Array of size %d indexed by %d", LSAs_arraysize, k);
    return LSAs_var[k].c_str();
}

void OSPFNLinkStateRequestPacket::setLSAs(unsigned int k, const char * LSAs)
{
    if (k>=LSAs_arraysize) throw cRuntimeError("Array of size %d indexed by %d", LSAs_arraysize, k);
    this->LSAs_var[k] = LSAs;
}

class OSPFNLinkStateRequestPacketDescriptor : public cClassDescriptor
{
  public:
    OSPFNLinkStateRequestPacketDescriptor();
    virtual ~OSPFNLinkStateRequestPacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(OSPFNLinkStateRequestPacketDescriptor);

OSPFNLinkStateRequestPacketDescriptor::OSPFNLinkStateRequestPacketDescriptor() : cClassDescriptor("OSPFNLinkStateRequestPacket", "OSPFNPacket")
{
}

OSPFNLinkStateRequestPacketDescriptor::~OSPFNLinkStateRequestPacketDescriptor()
{
}

bool OSPFNLinkStateRequestPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<OSPFNLinkStateRequestPacket *>(obj)!=NULL;
}

const char *OSPFNLinkStateRequestPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int OSPFNLinkStateRequestPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int OSPFNLinkStateRequestPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *OSPFNLinkStateRequestPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "requests",
        "LSAs",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int OSPFNLinkStateRequestPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='r' && strcmp(fieldName, "requests")==0) return base+0;
    if (fieldName[0]=='L' && strcmp(fieldName, "LSAs")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *OSPFNLinkStateRequestPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "OSPFNLSARequest",
        "string",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *OSPFNLinkStateRequestPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int OSPFNLinkStateRequestPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNLinkStateRequestPacket *pp = (OSPFNLinkStateRequestPacket *)object; (void)pp;
    switch (field) {
        case 0: return pp->getRequestsArraySize();
        case 1: return pp->getLSAsArraySize();
        default: return 0;
    }
}

std::string OSPFNLinkStateRequestPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNLinkStateRequestPacket *pp = (OSPFNLinkStateRequestPacket *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getRequests(i); return out.str();}
        case 1: return oppstring2string(pp->getLSAs(i));
        default: return "";
    }
}

bool OSPFNLinkStateRequestPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNLinkStateRequestPacket *pp = (OSPFNLinkStateRequestPacket *)object; (void)pp;
    switch (field) {
        case 1: pp->setLSAs(i,(value)); return true;
        default: return false;
    }
}

const char *OSPFNLinkStateRequestPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(OSPFNLSARequest));
        default: return NULL;
    };
}

void *OSPFNLinkStateRequestPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNLinkStateRequestPacket *pp = (OSPFNLinkStateRequestPacket *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getRequests(i)); break;
        default: return NULL;
    }
}

Register_Class(OSPFNLinkStateAcknowledgementPacket);

OSPFNLinkStateAcknowledgementPacket::OSPFNLinkStateAcknowledgementPacket(const char *name, int kind) : ::OSPFNPacket(name,kind)
{
    LSAs_arraysize = 0;
    this->LSAs_var = 0;
    hops_arraysize = 0;
    this->hops_var = 0;
}

OSPFNLinkStateAcknowledgementPacket::OSPFNLinkStateAcknowledgementPacket(const OSPFNLinkStateAcknowledgementPacket& other) : ::OSPFNPacket(other)
{
    LSAs_arraysize = 0;
    this->LSAs_var = 0;
    hops_arraysize = 0;
    this->hops_var = 0;
    copy(other);
}

OSPFNLinkStateAcknowledgementPacket::~OSPFNLinkStateAcknowledgementPacket()
{
    delete [] LSAs_var;
    delete [] hops_var;
}

OSPFNLinkStateAcknowledgementPacket& OSPFNLinkStateAcknowledgementPacket::operator=(const OSPFNLinkStateAcknowledgementPacket& other)
{
    if (this==&other) return *this;
    ::OSPFNPacket::operator=(other);
    copy(other);
    return *this;
}

void OSPFNLinkStateAcknowledgementPacket::copy(const OSPFNLinkStateAcknowledgementPacket& other)
{
    delete [] this->LSAs_var;
    this->LSAs_var = (other.LSAs_arraysize==0) ? NULL : new opp_string[other.LSAs_arraysize];
    LSAs_arraysize = other.LSAs_arraysize;
    for (unsigned int i=0; i<LSAs_arraysize; i++)
        this->LSAs_var[i] = other.LSAs_var[i];
    delete [] this->hops_var;
    this->hops_var = (other.hops_arraysize==0) ? NULL : new int[other.hops_arraysize];
    hops_arraysize = other.hops_arraysize;
    for (unsigned int i=0; i<hops_arraysize; i++)
        this->hops_var[i] = other.hops_var[i];
}

void OSPFNLinkStateAcknowledgementPacket::parsimPack(cCommBuffer *b)
{
    ::OSPFNPacket::parsimPack(b);
    b->pack(LSAs_arraysize);
    doPacking(b,this->LSAs_var,LSAs_arraysize);
    b->pack(hops_arraysize);
    doPacking(b,this->hops_var,hops_arraysize);
}

void OSPFNLinkStateAcknowledgementPacket::parsimUnpack(cCommBuffer *b)
{
    ::OSPFNPacket::parsimUnpack(b);
    delete [] this->LSAs_var;
    b->unpack(LSAs_arraysize);
    if (LSAs_arraysize==0) {
        this->LSAs_var = 0;
    } else {
        this->LSAs_var = new opp_string[LSAs_arraysize];
        doUnpacking(b,this->LSAs_var,LSAs_arraysize);
    }
    delete [] this->hops_var;
    b->unpack(hops_arraysize);
    if (hops_arraysize==0) {
        this->hops_var = 0;
    } else {
        this->hops_var = new int[hops_arraysize];
        doUnpacking(b,this->hops_var,hops_arraysize);
    }
}

void OSPFNLinkStateAcknowledgementPacket::setLSAsArraySize(unsigned int size)
{
    opp_string *LSAs_var2 = (size==0) ? NULL : new opp_string[size];
    unsigned int sz = LSAs_arraysize < size ? LSAs_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        LSAs_var2[i] = this->LSAs_var[i];
    for (unsigned int i=sz; i<size; i++)
        LSAs_var2[i] = 0;
    LSAs_arraysize = size;
    delete [] this->LSAs_var;
    this->LSAs_var = LSAs_var2;
}

unsigned int OSPFNLinkStateAcknowledgementPacket::getLSAsArraySize() const
{
    return LSAs_arraysize;
}

const char * OSPFNLinkStateAcknowledgementPacket::getLSAs(unsigned int k) const
{
    if (k>=LSAs_arraysize) throw cRuntimeError("Array of size %d indexed by %d", LSAs_arraysize, k);
    return LSAs_var[k].c_str();
}

void OSPFNLinkStateAcknowledgementPacket::setLSAs(unsigned int k, const char * LSAs)
{
    if (k>=LSAs_arraysize) throw cRuntimeError("Array of size %d indexed by %d", LSAs_arraysize, k);
    this->LSAs_var[k] = LSAs;
}

void OSPFNLinkStateAcknowledgementPacket::setHopsArraySize(unsigned int size)
{
    int *hops_var2 = (size==0) ? NULL : new int[size];
    unsigned int sz = hops_arraysize < size ? hops_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        hops_var2[i] = this->hops_var[i];
    for (unsigned int i=sz; i<size; i++)
        hops_var2[i] = 0;
    hops_arraysize = size;
    delete [] this->hops_var;
    this->hops_var = hops_var2;
}

unsigned int OSPFNLinkStateAcknowledgementPacket::getHopsArraySize() const
{
    return hops_arraysize;
}

int OSPFNLinkStateAcknowledgementPacket::getHops(unsigned int k) const
{
    if (k>=hops_arraysize) throw cRuntimeError("Array of size %d indexed by %d", hops_arraysize, k);
    return hops_var[k];
}

void OSPFNLinkStateAcknowledgementPacket::setHops(unsigned int k, int hops)
{
    if (k>=hops_arraysize) throw cRuntimeError("Array of size %d indexed by %d", hops_arraysize, k);
    this->hops_var[k] = hops;
}

class OSPFNLinkStateAcknowledgementPacketDescriptor : public cClassDescriptor
{
  public:
    OSPFNLinkStateAcknowledgementPacketDescriptor();
    virtual ~OSPFNLinkStateAcknowledgementPacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(OSPFNLinkStateAcknowledgementPacketDescriptor);

OSPFNLinkStateAcknowledgementPacketDescriptor::OSPFNLinkStateAcknowledgementPacketDescriptor() : cClassDescriptor("OSPFNLinkStateAcknowledgementPacket", "OSPFNPacket")
{
}

OSPFNLinkStateAcknowledgementPacketDescriptor::~OSPFNLinkStateAcknowledgementPacketDescriptor()
{
}

bool OSPFNLinkStateAcknowledgementPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<OSPFNLinkStateAcknowledgementPacket *>(obj)!=NULL;
}

const char *OSPFNLinkStateAcknowledgementPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int OSPFNLinkStateAcknowledgementPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int OSPFNLinkStateAcknowledgementPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *OSPFNLinkStateAcknowledgementPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "LSAs",
        "hops",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int OSPFNLinkStateAcknowledgementPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='L' && strcmp(fieldName, "LSAs")==0) return base+0;
    if (fieldName[0]=='h' && strcmp(fieldName, "hops")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *OSPFNLinkStateAcknowledgementPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
        "int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *OSPFNLinkStateAcknowledgementPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int OSPFNLinkStateAcknowledgementPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNLinkStateAcknowledgementPacket *pp = (OSPFNLinkStateAcknowledgementPacket *)object; (void)pp;
    switch (field) {
        case 0: return pp->getLSAsArraySize();
        case 1: return pp->getHopsArraySize();
        default: return 0;
    }
}

std::string OSPFNLinkStateAcknowledgementPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNLinkStateAcknowledgementPacket *pp = (OSPFNLinkStateAcknowledgementPacket *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getLSAs(i));
        case 1: return long2string(pp->getHops(i));
        default: return "";
    }
}

bool OSPFNLinkStateAcknowledgementPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNLinkStateAcknowledgementPacket *pp = (OSPFNLinkStateAcknowledgementPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setLSAs(i,(value)); return true;
        case 1: pp->setHops(i,string2long(value)); return true;
        default: return false;
    }
}

const char *OSPFNLinkStateAcknowledgementPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *OSPFNLinkStateAcknowledgementPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNLinkStateAcknowledgementPacket *pp = (OSPFNLinkStateAcknowledgementPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


