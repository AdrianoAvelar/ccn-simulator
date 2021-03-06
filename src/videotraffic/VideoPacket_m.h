//
// Generated file, do not edit! Created by nedtool 4.6 from videotraffic/VideoPacket.msg.
//

#ifndef _VIDEOPACKET_M_H_
#define _VIDEOPACKET_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Class generated from <tt>videotraffic/VideoPacket.msg:21</tt> by nedtool.
 * <pre>
 * //
 * // TODO generated message class
 * //
 * packet VideoPacket
 * {
 *     int frametype_;
 *     int packetSize_;
 *     int frame_pkt_id_;
 *     int packetType_;
 *     double sendtime_;
 *     int priority_;
 * 
 *     int source;
 *     int destination;
 *     int hopCount = 0;
 * }
 * </pre>
 */
class VideoPacket : public ::cPacket
{
  protected:
    int frametype__var;
    int packetSize__var;
    int frame_pkt_id__var;
    int packetType__var;
    double sendtime__var;
    int priority__var;
    int source_var;
    int destination_var;
    int hopCount_var;

  private:
    void copy(const VideoPacket& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const VideoPacket&);

  public:
    VideoPacket(const char *name=NULL, int kind=0);
    VideoPacket(const VideoPacket& other);
    virtual ~VideoPacket();
    VideoPacket& operator=(const VideoPacket& other);
    virtual VideoPacket *dup() const {return new VideoPacket(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getFrametype_() const;
    virtual void setFrametype_(int frametype_);
    virtual int getPacketSize_() const;
    virtual void setPacketSize_(int packetSize_);
    virtual int getFrame_pkt_id_() const;
    virtual void setFrame_pkt_id_(int frame_pkt_id_);
    virtual int getPacketType_() const;
    virtual void setPacketType_(int packetType_);
    virtual double getSendtime_() const;
    virtual void setSendtime_(double sendtime_);
    virtual int getPriority_() const;
    virtual void setPriority_(int priority_);
    virtual int getSource() const;
    virtual void setSource(int source);
    virtual int getDestination() const;
    virtual void setDestination(int destination);
    virtual int getHopCount() const;
    virtual void setHopCount(int hopCount);
};

inline void doPacking(cCommBuffer *b, VideoPacket& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, VideoPacket& obj) {obj.parsimUnpack(b);}


#endif // ifndef _VIDEOPACKET_M_H_

