//
// Generated file, do not edit! Created by nedtool 4.6 from CcnPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "CcnPacket_m.h"

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
    cEnum *e = cEnum::find("CcnMessageType");
    if (!e) enums.getInstance()->add(e = new cEnum("CcnMessageType"));
    e->insert(CCN_INTEREST, "CCN_INTEREST");
    e->insert(CCN_CONTENT, "CCN_CONTENT");
);

Register_Class(CcnPacket);

CcnPacket::CcnPacket(const char *name, int kind) : ::RawPacket(name,kind)
{
    this->setByteLength(4);

    this->type_var = 0;
    this->chunkSize_var = 0;
    this->hops_var = 0;
    this->dstIface_var = 0;
    this->TSB_var = 0;
    this->TSI_var = 0;
    this->capacity_var = 0;
    this->SumDi_var = 0;
    this->TotDelay_var = 0;
    this->priority_var = 0;
    this->senderTime_var = 0;
    this->rank_var = 0;
    this->consumer_var = 0;
    this->btw_var = 0;
}

CcnPacket::CcnPacket(const CcnPacket& other) : ::RawPacket(other)
{
    copy(other);
}

CcnPacket::~CcnPacket()
{
}

CcnPacket& CcnPacket::operator=(const CcnPacket& other)
{
    if (this==&other) return *this;
    ::RawPacket::operator=(other);
    copy(other);
    return *this;
}

void CcnPacket::copy(const CcnPacket& other)
{
    this->type_var = other.type_var;
    this->chunkSize_var = other.chunkSize_var;
    this->hops_var = other.hops_var;
    this->dstIface_var = other.dstIface_var;
    this->TSB_var = other.TSB_var;
    this->TSI_var = other.TSI_var;
    this->capacity_var = other.capacity_var;
    this->SumDi_var = other.SumDi_var;
    this->TotDelay_var = other.TotDelay_var;
    this->priority_var = other.priority_var;
    this->senderTime_var = other.senderTime_var;
    this->rank_var = other.rank_var;
    this->consumer_var = other.consumer_var;
    this->btw_var = other.btw_var;
}

void CcnPacket::parsimPack(cCommBuffer *b)
{
    ::RawPacket::parsimPack(b);
    doPacking(b,this->type_var);
    doPacking(b,this->chunkSize_var);
    doPacking(b,this->hops_var);
    doPacking(b,this->dstIface_var);
    doPacking(b,this->TSB_var);
    doPacking(b,this->TSI_var);
    doPacking(b,this->capacity_var);
    doPacking(b,this->SumDi_var);
    doPacking(b,this->TotDelay_var);
    doPacking(b,this->priority_var);
    doPacking(b,this->senderTime_var);
    doPacking(b,this->rank_var);
    doPacking(b,this->consumer_var);
    doPacking(b,this->btw_var);
}

void CcnPacket::parsimUnpack(cCommBuffer *b)
{
    ::RawPacket::parsimUnpack(b);
    doUnpacking(b,this->type_var);
    doUnpacking(b,this->chunkSize_var);
    doUnpacking(b,this->hops_var);
    doUnpacking(b,this->dstIface_var);
    doUnpacking(b,this->TSB_var);
    doUnpacking(b,this->TSI_var);
    doUnpacking(b,this->capacity_var);
    doUnpacking(b,this->SumDi_var);
    doUnpacking(b,this->TotDelay_var);
    doUnpacking(b,this->priority_var);
    doUnpacking(b,this->senderTime_var);
    doUnpacking(b,this->rank_var);
    doUnpacking(b,this->consumer_var);
    doUnpacking(b,this->btw_var);
}

int CcnPacket::getType() const
{
    return type_var;
}

void CcnPacket::setType(int type)
{
    this->type_var = type;
}

int CcnPacket::getChunkSize() const
{
    return chunkSize_var;
}

void CcnPacket::setChunkSize(int chunkSize)
{
    this->chunkSize_var = chunkSize;
}

int CcnPacket::getHops() const
{
    return hops_var;
}

void CcnPacket::setHops(int hops)
{
    this->hops_var = hops;
}

int CcnPacket::getDstIface() const
{
    return dstIface_var;
}

void CcnPacket::setDstIface(int dstIface)
{
    this->dstIface_var = dstIface;
}

int CcnPacket::getTSB() const
{
    return TSB_var;
}

void CcnPacket::setTSB(int TSB)
{
    this->TSB_var = TSB;
}

int CcnPacket::getTSI() const
{
    return TSI_var;
}

void CcnPacket::setTSI(int TSI)
{
    this->TSI_var = TSI;
}

double CcnPacket::getCapacity() const
{
    return capacity_var;
}

void CcnPacket::setCapacity(double capacity)
{
    this->capacity_var = capacity;
}

double CcnPacket::getSumDi() const
{
    return SumDi_var;
}

void CcnPacket::setSumDi(double SumDi)
{
    this->SumDi_var = SumDi;
}

double CcnPacket::getTotDelay() const
{
    return TotDelay_var;
}

void CcnPacket::setTotDelay(double TotDelay)
{
    this->TotDelay_var = TotDelay;
}

int CcnPacket::getPriority() const
{
    return priority_var;
}

void CcnPacket::setPriority(int priority)
{
    this->priority_var = priority;
}

double CcnPacket::getSenderTime() const
{
    return senderTime_var;
}

void CcnPacket::setSenderTime(double senderTime)
{
    this->senderTime_var = senderTime;
}

int CcnPacket::getRank() const
{
    return rank_var;
}

void CcnPacket::setRank(int rank)
{
    this->rank_var = rank;
}

const char * CcnPacket::getConsumer() const
{
    return consumer_var.c_str();
}

void CcnPacket::setConsumer(const char * consumer)
{
    this->consumer_var = consumer;
}

double CcnPacket::getBtw() const
{
    return btw_var;
}

void CcnPacket::setBtw(double btw)
{
    this->btw_var = btw;
}

class CcnPacketDescriptor : public cClassDescriptor
{
  public:
    CcnPacketDescriptor();
    virtual ~CcnPacketDescriptor();

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

Register_ClassDescriptor(CcnPacketDescriptor);

CcnPacketDescriptor::CcnPacketDescriptor() : cClassDescriptor("CcnPacket", "RawPacket")
{
}

CcnPacketDescriptor::~CcnPacketDescriptor()
{
}

bool CcnPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<CcnPacket *>(obj)!=NULL;
}

const char *CcnPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CcnPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 14+basedesc->getFieldCount(object) : 14;
}

unsigned int CcnPacketDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<14) ? fieldTypeFlags[field] : 0;
}

const char *CcnPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "type",
        "chunkSize",
        "hops",
        "dstIface",
        "TSB",
        "TSI",
        "capacity",
        "SumDi",
        "TotDelay",
        "priority",
        "senderTime",
        "rank",
        "consumer",
        "btw",
    };
    return (field>=0 && field<14) ? fieldNames[field] : NULL;
}

int CcnPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "chunkSize")==0) return base+1;
    if (fieldName[0]=='h' && strcmp(fieldName, "hops")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "dstIface")==0) return base+3;
    if (fieldName[0]=='T' && strcmp(fieldName, "TSB")==0) return base+4;
    if (fieldName[0]=='T' && strcmp(fieldName, "TSI")==0) return base+5;
    if (fieldName[0]=='c' && strcmp(fieldName, "capacity")==0) return base+6;
    if (fieldName[0]=='S' && strcmp(fieldName, "SumDi")==0) return base+7;
    if (fieldName[0]=='T' && strcmp(fieldName, "TotDelay")==0) return base+8;
    if (fieldName[0]=='p' && strcmp(fieldName, "priority")==0) return base+9;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderTime")==0) return base+10;
    if (fieldName[0]=='r' && strcmp(fieldName, "rank")==0) return base+11;
    if (fieldName[0]=='c' && strcmp(fieldName, "consumer")==0) return base+12;
    if (fieldName[0]=='b' && strcmp(fieldName, "btw")==0) return base+13;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CcnPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "double",
        "double",
        "double",
        "int",
        "double",
        "int",
        "string",
        "double",
    };
    return (field>=0 && field<14) ? fieldTypeStrings[field] : NULL;
}

const char *CcnPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        case 0:
            if (!strcmp(propertyname,"enum")) return "CcnMessageType";
            return NULL;
        default: return NULL;
    }
}

int CcnPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    CcnPacket *pp = (CcnPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CcnPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    CcnPacket *pp = (CcnPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getType());
        case 1: return long2string(pp->getChunkSize());
        case 2: return long2string(pp->getHops());
        case 3: return long2string(pp->getDstIface());
        case 4: return long2string(pp->getTSB());
        case 5: return long2string(pp->getTSI());
        case 6: return double2string(pp->getCapacity());
        case 7: return double2string(pp->getSumDi());
        case 8: return double2string(pp->getTotDelay());
        case 9: return long2string(pp->getPriority());
        case 10: return double2string(pp->getSenderTime());
        case 11: return long2string(pp->getRank());
        case 12: return oppstring2string(pp->getConsumer());
        case 13: return double2string(pp->getBtw());
        default: return "";
    }
}

bool CcnPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    CcnPacket *pp = (CcnPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setType(string2long(value)); return true;
        case 1: pp->setChunkSize(string2long(value)); return true;
        case 2: pp->setHops(string2long(value)); return true;
        case 3: pp->setDstIface(string2long(value)); return true;
        case 4: pp->setTSB(string2long(value)); return true;
        case 5: pp->setTSI(string2long(value)); return true;
        case 6: pp->setCapacity(string2double(value)); return true;
        case 7: pp->setSumDi(string2double(value)); return true;
        case 8: pp->setTotDelay(string2double(value)); return true;
        case 9: pp->setPriority(string2long(value)); return true;
        case 10: pp->setSenderTime(string2double(value)); return true;
        case 11: pp->setRank(string2long(value)); return true;
        case 12: pp->setConsumer((value)); return true;
        case 13: pp->setBtw(string2double(value)); return true;
        default: return false;
    }
}

const char *CcnPacketDescriptor::getFieldStructName(void *object, int field) const
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

void *CcnPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    CcnPacket *pp = (CcnPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


