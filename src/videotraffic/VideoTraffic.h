//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef BASENODE_H_
#define BASENODE_H_


#include <string.h>
#include <omnetpp.h>
#include "VideoPacket_m.h"

#include "VideoTrafficGenerator.h"
#include "DumpFile.h"

class VideoTraffic {

public:
    VideoTraffic( const char*,const char*, const char*);

    virtual ~VideoTraffic();
    void eval();
    void forwadingMessage(VideoPacket *msg);
    void receiveMessage(VideoPacket *msg);
    VideoPacket * generateMessage();
    double getNextPkttime();
    int addToSenderTrace(double time, VideoPacket *msg);
   virtual void finish();

private:

    int counter;
    VideoPacket *videopkt;
    cMessage *event;
    simtime_t delayTime;
    long numSent;
    long numReceived;

    double nextPkttime_;
    VideoTrafficGenerator *traffic;
    double totalTime;

    /*Files*/
    DumpFile *rd; //Receiver dump file
    DumpFile *sd; //sender dump file

};

#endif /* BASENODE_H_ */
