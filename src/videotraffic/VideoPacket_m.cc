//
// Generated file, do not edit! Created by nedtool 4.6 from videotraffic/VideoPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "VideoPacket_m.h"

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

Register_Class(VideoPacket);

VideoPacket::VideoPacket(const char *name, int kind) : ::cPacket(name,kind)
{
    this->frametype__var = 0;
    this->packetSize__var = 0;
    this->frame_pkt_id__var = 0;
    this->packetType__var = 0;
    this->sendtime__var = 0;
    this->priority__var = 0;
    this->source_var = 0;
    this->destination_var = 0;
    this->hopCount_var = 0;
}

VideoPacket::VideoPacket(const VideoPacket& other) : ::cPacket(other)
{
    copy(other);
}

VideoPacket::~VideoPacket()
{
}

VideoPacket& VideoPacket::operator=(const VideoPacket& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void VideoPacket::copy(const VideoPacket& other)
{
    this->frametype__var = other.frametype__var;
    this->packetSize__var = other.packetSize__var;
    this->frame_pkt_id__var = other.frame_pkt_id__var;
    this->packetType__var = other.packetType__var;
    this->sendtime__var = other.sendtime__var;
    this->priority__var = other.priority__var;
    this->source_var = other.source_var;
    this->destination_var = other.destination_var;
    this->hopCount_var = other.hopCount_var;
}

void VideoPacket::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
    doPacking(b,this->frametype__var);
    doPacking(b,this->packetSize__var);
    doPacking(b,this->frame_pkt_id__var);
    doPacking(b,this->packetType__var);
    doPacking(b,this->sendtime__var);
    doPacking(b,this->priority__var);
    doPacking(b,this->source_var);
    doPacking(b,this->destination_var);
    doPacking(b,this->hopCount_var);
}

void VideoPacket::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
    doUnpacking(b,this->frametype__var);
    doUnpacking(b,this->packetSize__var);
    doUnpacking(b,this->frame_pkt_id__var);
    doUnpacking(b,this->packetType__var);
    doUnpacking(b,this->sendtime__var);
    doUnpacking(b,this->priority__var);
    doUnpacking(b,this->source_var);
    doUnpacking(b,this->destination_var);
    doUnpacking(b,this->hopCount_var);
}

int VideoPacket::getFrametype_() const
{
    return frametype__var;
}

void VideoPacket::setFrametype_(int frametype_)
{
    this->frametype__var = frametype_;
}

int VideoPacket::getPacketSize_() const
{
    return packetSize__var;
}

void VideoPacket::setPacketSize_(int packetSize_)
{
    this->packetSize__var = packetSize_;
}

int VideoPacket::getFrame_pkt_id_() const
{
    return frame_pkt_id__var;
}

void VideoPacket::setFrame_pkt_id_(int frame_pkt_id_)
{
    this->frame_pkt_id__var = frame_pkt_id_;
}

int VideoPacket::getPacketType_() const
{
    return packetType__var;
}

void VideoPacket::setPacketType_(int packetType_)
{
    this->packetType__var = packetType_;
}

double VideoPacket::getSendtime_() const
{
    return sendtime__var;
}

void VideoPacket::setSendtime_(double sendtime_)
{
    this->sendtime__var = sendtime_;
}

int VideoPacket::getPriority_() const
{
    return priority__var;
}

void VideoPacket::setPriority_(int priority_)
{
    this->priority__var = priority_;
}

int VideoPacket::getSource() const
{
    return source_var;
}

void VideoPacket::setSource(int source)
{
    this->source_var = source;
}

int VideoPacket::getDestination() const
{
    return destination_var;
}

void VideoPacket::setDestination(int destination)
{
    this->destination_var = destination;
}

int VideoPacket::getHopCount() const
{
    return hopCount_var;
}

void VideoPacket::setHopCount(int hopCount)
{
    this->hopCount_var = hopCount;
}

class VideoPacketDescriptor : public cClassDescriptor
{
  public:
    VideoPacketDescriptor();
    virtual ~VideoPacketDescriptor();

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

Register_ClassDescriptor(VideoPacketDescriptor);

VideoPacketDescriptor::VideoPacketDescriptor() : cClassDescriptor("VideoPacket", "cPacket")
{
}

VideoPacketDescriptor::~VideoPacketDescriptor()
{
}

bool VideoPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<VideoPacket *>(obj)!=NULL;
}

const char *VideoPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int VideoPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 9+basedesc->getFieldCount(object) : 9;
}

unsigned int VideoPacketDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<9) ? fieldTypeFlags[field] : 0;
}

const char *VideoPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "frametype_",
        "packetSize_",
        "frame_pkt_id_",
        "packetType_",
        "sendtime_",
        "priority_",
        "source",
        "destination",
        "hopCount",
    };
    return (field>=0 && field<9) ? fieldNames[field] : NULL;
}

int VideoPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='f' && strcmp(fieldName, "frametype_")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "packetSize_")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "frame_pkt_id_")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "packetType_")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "sendtime_")==0) return base+4;
    if (fieldName[0]=='p' && strcmp(fieldName, "priority_")==0) return base+5;
    if (fieldName[0]=='s' && strcmp(fieldName, "source")==0) return base+6;
    if (fieldName[0]=='d' && strcmp(fieldName, "destination")==0) return base+7;
    if (fieldName[0]=='h' && strcmp(fieldName, "hopCount")==0) return base+8;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *VideoPacketDescriptor::getFieldTypeString(void *object, int field) const
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
        "double",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<9) ? fieldTypeStrings[field] : NULL;
}

const char *VideoPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int VideoPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    VideoPacket *pp = (VideoPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string VideoPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    VideoPacket *pp = (VideoPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getFrametype_());
        case 1: return long2string(pp->getPacketSize_());
        case 2: return long2string(pp->getFrame_pkt_id_());
        case 3: return long2string(pp->getPacketType_());
        case 4: return double2string(pp->getSendtime_());
        case 5: return long2string(pp->getPriority_());
        case 6: return long2string(pp->getSource());
        case 7: return long2string(pp->getDestination());
        case 8: return long2string(pp->getHopCount());
        default: return "";
    }
}

bool VideoPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    VideoPacket *pp = (VideoPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setFrametype_(string2long(value)); return true;
        case 1: pp->setPacketSize_(string2long(value)); return true;
        case 2: pp->setFrame_pkt_id_(string2long(value)); return true;
        case 3: pp->setPacketType_(string2long(value)); return true;
        case 4: pp->setSendtime_(string2double(value)); return true;
        case 5: pp->setPriority_(string2long(value)); return true;
        case 6: pp->setSource(string2long(value)); return true;
        case 7: pp->setDestination(string2long(value)); return true;
        case 8: pp->setHopCount(string2long(value)); return true;
        default: return false;
    }
}

const char *VideoPacketDescriptor::getFieldStructName(void *object, int field) const
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

void *VideoPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    VideoPacket *pp = (VideoPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


