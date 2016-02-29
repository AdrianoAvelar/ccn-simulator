//
// Generated file, do not edit! Created by nedtool 4.6 from ospfn/OSPFNTimer.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "OSPFNTimer_m.h"

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
    cEnum *e = cEnum::find("OSPFNTimerType");
    if (!e) enums.getInstance()->add(e = new cEnum("OSPFNTimerType"));
    e->insert(INTERFACE_HELLO_TIMER, "INTERFACE_HELLO_TIMER");
    e->insert(INTERFACE_WAIT_TIMER, "INTERFACE_WAIT_TIMER");
    e->insert(INTERFACE_ACKNOWLEDGEMENT_TIMER, "INTERFACE_ACKNOWLEDGEMENT_TIMER");
    e->insert(NEIGHBOR_INACTIVITY_TIMER, "NEIGHBOR_INACTIVITY_TIMER");
    e->insert(NEIGHBOR_POLL_TIMER, "NEIGHBOR_POLL_TIMER");
    e->insert(NEIGHBOR_DD_RETRANSMISSION_TIMER, "NEIGHBOR_DD_RETRANSMISSION_TIMER");
    e->insert(NEIGHBOR_UPDATE_RETRANSMISSION_TIMER, "NEIGHBOR_UPDATE_RETRANSMISSION_TIMER");
    e->insert(NEIGHBOR_REQUEST_RETRANSMISSION_TIMER, "NEIGHBOR_REQUEST_RETRANSMISSION_TIMER");
    e->insert(DATABASE_AGE_TIMER, "DATABASE_AGE_TIMER");
);

Register_Class(OSPFNTimer);

OSPFNTimer::OSPFNTimer(const char *name, int kind) : ::cMessage(name,kind)
{
    this->timerKind_var = INTERFACE_HELLO_TIMER;
}

OSPFNTimer::OSPFNTimer(const OSPFNTimer& other) : ::cMessage(other)
{
    copy(other);
}

OSPFNTimer::~OSPFNTimer()
{
}

OSPFNTimer& OSPFNTimer::operator=(const OSPFNTimer& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void OSPFNTimer::copy(const OSPFNTimer& other)
{
    this->timerKind_var = other.timerKind_var;
}

void OSPFNTimer::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->timerKind_var);
}

void OSPFNTimer::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->timerKind_var);
}

char OSPFNTimer::getTimerKind() const
{
    return timerKind_var;
}

void OSPFNTimer::setTimerKind(char timerKind)
{
    this->timerKind_var = timerKind;
}

class OSPFNTimerDescriptor : public cClassDescriptor
{
  public:
    OSPFNTimerDescriptor();
    virtual ~OSPFNTimerDescriptor();

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

Register_ClassDescriptor(OSPFNTimerDescriptor);

OSPFNTimerDescriptor::OSPFNTimerDescriptor() : cClassDescriptor("OSPFNTimer", "cMessage")
{
}

OSPFNTimerDescriptor::~OSPFNTimerDescriptor()
{
}

bool OSPFNTimerDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<OSPFNTimer *>(obj)!=NULL;
}

const char *OSPFNTimerDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int OSPFNTimerDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int OSPFNTimerDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *OSPFNTimerDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "timerKind",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int OSPFNTimerDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "timerKind")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *OSPFNTimerDescriptor::getFieldTypeString(void *object, int field) const
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

const char *OSPFNTimerDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "OSPFNTimerType";
            return NULL;
        default: return NULL;
    }
}

int OSPFNTimerDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNTimer *pp = (OSPFNTimer *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string OSPFNTimerDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNTimer *pp = (OSPFNTimer *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getTimerKind());
        default: return "";
    }
}

bool OSPFNTimerDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNTimer *pp = (OSPFNTimer *)object; (void)pp;
    switch (field) {
        case 0: pp->setTimerKind(string2long(value)); return true;
        default: return false;
    }
}

const char *OSPFNTimerDescriptor::getFieldStructName(void *object, int field) const
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

void *OSPFNTimerDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    OSPFNTimer *pp = (OSPFNTimer *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


