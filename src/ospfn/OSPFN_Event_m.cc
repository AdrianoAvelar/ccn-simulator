//
// Generated file, do not edit! Created by nedtool 4.6 from ospfn/OSPFN_Event.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "OSPFN_Event_m.h"

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
    cEnum *e = cEnum::find("EventType");
    if (!e) enums.getInstance()->add(e = new cEnum("EventType"));
    e->insert(SEND_HELLO_PACKET, "SEND_HELLO_PACKET");
    e->insert(FLOOD_HELLO_PACKET, "FLOOD_HELLO_PACKET");
    e->insert(SEND_LSA, "SEND_LSA");
);

Register_Class(OSPFN_Event);

OSPFN_Event::OSPFN_Event(const char *name, int kind) : ::cPacket(name,kind)
{
    this->eventType_var = SEND_HELLO_PACKET;
}

OSPFN_Event::OSPFN_Event(const OSPFN_Event& other) : ::cPacket(other)
{
    copy(other);
}

OSPFN_Event::~OSPFN_Event()
{
}

OSPFN_Event& OSPFN_Event::operator=(const OSPFN_Event& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void OSPFN_Event::copy(const OSPFN_Event& other)
{
    this->eventType_var = other.eventType_var;
}

void OSPFN_Event::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->eventType_var);
}

void OSPFN_Event::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->eventType_var);
}

char OSPFN_Event::getEventType() const
{
    return eventType_var;
}

void OSPFN_Event::setEventType(char eventType)
{
    this->eventType_var = eventType;
}

class OSPFN_EventDescriptor : public cClassDescriptor
{
  public:
    OSPFN_EventDescriptor();
    virtual ~OSPFN_EventDescriptor();

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

Register_ClassDescriptor(OSPFN_EventDescriptor);

OSPFN_EventDescriptor::OSPFN_EventDescriptor() : cClassDescriptor("OSPFN_Event", "cPacket")
{
}

OSPFN_EventDescriptor::~OSPFN_EventDescriptor()
{
}

bool OSPFN_EventDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<OSPFN_Event *>(obj)!=NULL;
}

const char *OSPFN_EventDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int OSPFN_EventDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int OSPFN_EventDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *OSPFN_EventDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "eventType",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int OSPFN_EventDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='e' && strcmp(fieldName, "eventType")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *OSPFN_EventDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "char",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *OSPFN_EventDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "EventType";
            return NULL;
        default: return NULL;
    }
}

int OSPFN_EventDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    OSPFN_Event *pp = (OSPFN_Event *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string OSPFN_EventDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFN_Event *pp = (OSPFN_Event *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getEventType());
        default: return "";
    }
}

bool OSPFN_EventDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    OSPFN_Event *pp = (OSPFN_Event *)object; (void)pp;
    switch (field) {
        case 0: pp->setEventType(string2long(value)); return true;
        default: return false;
    }
}

const char *OSPFN_EventDescriptor::getFieldStructName(void *object, int field) const
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

void *OSPFN_EventDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFN_Event *pp = (OSPFN_Event *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(OSPFN_Event_Hello);

OSPFN_Event_Hello::OSPFN_Event_Hello(const char *name, int kind) : ::OSPFN_Event(name,kind)
{
}

OSPFN_Event_Hello::OSPFN_Event_Hello(const OSPFN_Event_Hello& other) : ::OSPFN_Event(other)
{
    copy(other);
}

OSPFN_Event_Hello::~OSPFN_Event_Hello()
{
}

OSPFN_Event_Hello& OSPFN_Event_Hello::operator=(const OSPFN_Event_Hello& other)
{
    if (this==&other) return *this;
    ::OSPFN_Event::operator=(other);
    copy(other);
    return *this;
}

void OSPFN_Event_Hello::copy(const OSPFN_Event_Hello& other)
{
    this->destination_var = other.destination_var;
}

void OSPFN_Event_Hello::parsimPack(cCommBuffer *b)
{
    ::OSPFN_Event::parsimPack(b);
    doPacking(b,this->destination_var);
}

void OSPFN_Event_Hello::parsimUnpack(cCommBuffer *b)
{
    ::OSPFN_Event::parsimUnpack(b);
    doUnpacking(b,this->destination_var);
}

MACAddress& OSPFN_Event_Hello::getDestination()
{
    return destination_var;
}

void OSPFN_Event_Hello::setDestination(const MACAddress& destination)
{
    this->destination_var = destination;
}

class OSPFN_Event_HelloDescriptor : public cClassDescriptor
{
  public:
    OSPFN_Event_HelloDescriptor();
    virtual ~OSPFN_Event_HelloDescriptor();

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

Register_ClassDescriptor(OSPFN_Event_HelloDescriptor);

OSPFN_Event_HelloDescriptor::OSPFN_Event_HelloDescriptor() : cClassDescriptor("OSPFN_Event_Hello", "OSPFN_Event")
{
}

OSPFN_Event_HelloDescriptor::~OSPFN_Event_HelloDescriptor()
{
}

bool OSPFN_Event_HelloDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<OSPFN_Event_Hello *>(obj)!=NULL;
}

const char *OSPFN_Event_HelloDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int OSPFN_Event_HelloDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int OSPFN_Event_HelloDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISCOMPOUND,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *OSPFN_Event_HelloDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "destination",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int OSPFN_Event_HelloDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destination")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *OSPFN_Event_HelloDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "MACAddress",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *OSPFN_Event_HelloDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int OSPFN_Event_HelloDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    OSPFN_Event_Hello *pp = (OSPFN_Event_Hello *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string OSPFN_Event_HelloDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFN_Event_Hello *pp = (OSPFN_Event_Hello *)object; (void)pp;
    switch (field) {
        case 0: {std::stringstream out; out << pp->getDestination(); return out.str();}
        default: return "";
    }
}

bool OSPFN_Event_HelloDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    OSPFN_Event_Hello *pp = (OSPFN_Event_Hello *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *OSPFN_Event_HelloDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0: return opp_typename(typeid(MACAddress));
        default: return NULL;
    };
}

void *OSPFN_Event_HelloDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFN_Event_Hello *pp = (OSPFN_Event_Hello *)object; (void)pp;
    switch (field) {
        case 0: return (void *)(&pp->getDestination()); break;
        default: return NULL;
    }
}


