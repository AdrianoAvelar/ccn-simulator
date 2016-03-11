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

#include <VideoTraffic.h>

#include <EvaluateTrace.h>
#include "shared.h"

VideoTraffic::VideoTraffic(const char* videodat_filename, const char* rd_filename, const char* sd_filename) {
    videopkt = NULL;
    numSent = 0;
    numReceived = 0;


    SenderTrace *file = new SenderTrace();
    file->setFilePath(videodat_filename);

    rd = new DumpFile();
    rd->setFilePath(rd_filename);
    rd->open("w");

    sd = new DumpFile();
    sd->setFilePath(sd_filename);
    sd->open("w");

    traffic = new VideoTrafficGenerator();
    traffic->setTraceFile(file);

}


double VideoTraffic::getNextPkttime() {
    return nextPkttime_;
}

VideoPacket * VideoTraffic::generateMessage() {

    if (!traffic->running_) {
        traffic->init();
        traffic->running_ = true;
    }

    VideoPacket *newmsg = new VideoPacket();
    newmsg->setDestination(1);

    nextPkttime_ = traffic->timeout(newmsg);

    if (nextPkttime_ < 0) {

     //cancelAndDelete(event);
     //event->setKind(FINISH);
     //scheduleAt(simTime() + 10, event);
        traffic->running_ = false;
        delete newmsg;
        return NULL;
    }

    totalTime += nextPkttime_;

    return newmsg;
}

//void VideoTraffic::handleMessage(cMessage *msg) {
//
//    if (msg->isSelfMessage()) {
//        switch (msg->getKind()) {
//        case SEND:
//            videopkt = generateMessage();
//            if (videopkt != NULL) {
//                forwadingMessage(videopkt);
//                event->setKind(SEND);
//                scheduleAt(simTime() + nextPkttime_, event);
//                numSent++;
//            }
//            break;
//        case FINISH:
//            cancelAndDelete(msg);
//            break;
//        }
//
//    } else {
//
//        VideoPacket * vp = check_and_cast<VideoPacket *>(msg);
//        if (vp->getDestination() == getIndex()) {
//            receiveMessage(vp);
//        } else {
//            EV << " $$$$$$$$$$$$$$ GHOST message arrived at : " << simTime();
//        }
//    }
//
//}

void VideoTraffic::receiveMessage(VideoPacket *msg) {

    numReceived++;
    EV << numReceived << " video message arrived at : " << simTime();

    if (rd->isOpen()) {
        char buf[100];
        sprintf(buf, "%-16f id %-16d udp %-16d\n", simTime().dbl(),
                msg->getFrame_pkt_id_(), msg->getPacketSize_());
        rd->add(buf);
    }

    delete msg;
}

int VideoTraffic::addToSenderTrace(double time, VideoPacket *msg) {

    if (sd->isOpen()) {
        char buf[100];
        sprintf(buf, "%-16f id %-16d udp %-16d\n", time,
                msg->getFrame_pkt_id_(), msg->getPacketSize_());
        sd->add(buf);
        return 0;
    } else {
        EV << "Cannot add to sender trace. Sender Dump:"
                << sd->getFilePath() << "is no open" << std::endl;

        return -1;
    }
}

void VideoTraffic::eval() {

    EvaluateTrace *eval = new EvaluateTrace();
    eval->setSDump(sd);
    eval->setRDump(rd);
    eval->setMP4file("a01.mp4");
    eval->setMP4Output("a01_reconstructed.mp4");
    eval->setSenderTrace("st_a01.tr");
    eval->evaluate();
}

VideoTraffic::~VideoTraffic() {

    delete videopkt;
    delete rd;
    delete traffic;
}

void VideoTraffic::finish() {
    eval();
    // This function is called by OMNeT++ at the end of the simulation.
    EV << "Sent:     " << numSent << endl;
    EV << "Received: " << numReceived << endl;

    EV << "TotalTime: " << totalTime << endl;


}

