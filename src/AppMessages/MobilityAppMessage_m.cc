//
// Generated file, do not edit! Created by nedtool 4.6 from AppMessages/MobilityAppMessage.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "MobilityAppMessage_m.h"

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

Register_Class(MobilityAppMessage);

MobilityAppMessage::MobilityAppMessage(const char *name, int kind) : ::cPacket(name,kind)
{
    contents_arraysize = 0;
    this->contents_var = 0;
}

MobilityAppMessage::MobilityAppMessage(const MobilityAppMessage& other) : ::cPacket(other)
{
    contents_arraysize = 0;
    this->contents_var = 0;
    copy(other);
}

MobilityAppMessage::~MobilityAppMessage()
{
    delete [] contents_var;
}

MobilityAppMessage& MobilityAppMessage::operator=(const MobilityAppMessage& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void MobilityAppMessage::copy(const MobilityAppMessage& other)
{
    delete [] this->contents_var;
    this->contents_var = (other.contents_arraysize==0) ? NULL : new opp_string[other.contents_arraysize];
    contents_arraysize = other.contents_arraysize;
    for (unsigned int i=0; i<contents_arraysize; i++)
        this->contents_var[i] = other.contents_var[i];
}

void MobilityAppMessage::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    b->pack(contents_arraysize);
    doPacking(b,this->contents_var,contents_arraysize);
}

void MobilityAppMessage::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    delete [] this->contents_var;
    b->unpack(contents_arraysize);
    if (contents_arraysize==0) {
        this->contents_var = 0;
    } else {
        this->contents_var = new opp_string[contents_arraysize];
        doUnpacking(b,this->contents_var,contents_arraysize);
    }
}

void MobilityAppMessage::setContentsArraySize(unsigned int size)
{
    opp_string *contents_var2 = (size==0) ? NULL : new opp_string[size];
    unsigned int sz = contents_arraysize < size ? contents_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        contents_var2[i] = this->contents_var[i];
    for (unsigned int i=sz; i<size; i++)
        contents_var2[i] = 0;
    contents_arraysize = size;
    delete [] this->contents_var;
    this->contents_var = contents_var2;
}

unsigned int MobilityAppMessage::getContentsArraySize() const
{
    return contents_arraysize;
}

const char * MobilityAppMessage::getContents(unsigned int k) const
{
    if (k>=contents_arraysize) throw cRuntimeError("Array of size %d indexed by %d", contents_arraysize, k);
    return contents_var[k].c_str();
}

void MobilityAppMessage::setContents(unsigned int k, const char * contents)
{
    if (k>=contents_arraysize) throw cRuntimeError("Array of size %d indexed by %d", contents_arraysize, k);
    this->contents_var[k] = contents;
}

class MobilityAppMessageDescriptor : public cClassDescriptor
{
  public:
    MobilityAppMessageDescriptor();
    virtual ~MobilityAppMessageDescriptor();

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

Register_ClassDescriptor(MobilityAppMessageDescriptor);

MobilityAppMessageDescriptor::MobilityAppMessageDescriptor() : cClassDescriptor("MobilityAppMessage", "cPacket")
{
}

MobilityAppMessageDescriptor::~MobilityAppMessageDescriptor()
{
}

bool MobilityAppMessageDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<MobilityAppMessage *>(obj)!=NULL;
}

const char *MobilityAppMessageDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int MobilityAppMessageDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int MobilityAppMessageDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *MobilityAppMessageDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "contents",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int MobilityAppMessageDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "contents")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *MobilityAppMessageDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "string",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *MobilityAppMessageDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int MobilityAppMessageDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    MobilityAppMessage *pp = (MobilityAppMessage *)object; (void)pp;
    switch (field) {
        case 0: return pp->getContentsArraySize();
        default: return 0;
    }
}

std::string MobilityAppMessageDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    MobilityAppMessage *pp = (MobilityAppMessage *)object; (void)pp;
    switch (field) {
        case 0: return oppstring2string(pp->getContents(i));
        default: return "";
    }
}

bool MobilityAppMessageDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    MobilityAppMessage *pp = (MobilityAppMessage *)object; (void)pp;
    switch (field) {
        case 0: pp->setContents(i,(value)); return true;
        default: return false;
    }
}

const char *MobilityAppMessageDescriptor::getFieldStructName(void *object, int field) const
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

void *MobilityAppMessageDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    MobilityAppMessage *pp = (MobilityAppMessage *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


