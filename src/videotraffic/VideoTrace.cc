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

#include "VideoTrace.h"
#include <stdlib.h>
#include "VideoHandlers/EvaluateTrace.h"
#include "QoEMetric.h"
#include "Util.h"

VideoTrace::VideoTrace(std::string workdir, std::string trace,
        string mp4_reconstructed) {

    sdumpfile = new DumpFile();
    rdumpfile = new DumpFile();
    seqn = 0;
    remain = 0;
    this->wasSent = false;

    char rtt[32];
    //FIXME[EAMA] fazer um método que retorna uma string formatada. string = getString("string: %s",x);
    sprintf(rtt, "delay_video");
    rttOutVector.setName(rtt);

    this->workdir = workdir;
    this->trace = "";
    this->trace.append(workdir);

    if (this->trace.at(this->trace.length() - 1) != '/')
        this->trace.append("/");
    this->trace.append(trace);

    mp4ReconstructedPath = workdir;

    mp4ReconstructedName = mp4_reconstructed;
    if (mp4ReconstructedPath.at(mp4ReconstructedPath.length() - 1) != '/')
        mp4ReconstructedPath.append("/");
    mp4ReconstructedPath.append(mp4_reconstructed);

    out_of_order = 0;
    pkts_dropped = 0;

    delay_sum = 0;
    ndelay = 0;

}

void VideoTrace::setTraceFile(const char* strace, const char* rtrace) {


    std::string send_trace = workdir;
    if (send_trace.at(send_trace.length() - 1) != '/')
        send_trace.append("/");
    send_trace.append(strace);

    std::string receiver_trace = workdir;
    if (receiver_trace.at(receiver_trace.length() - 1) != '/')
        receiver_trace.append("/");
    receiver_trace.append(rtrace);

    sdumpfile->setFilePath(send_trace.c_str());
    sdumpfile->setFileName(strace);

    rdumpfile->setFilePath(receiver_trace.c_str());
    rdumpfile->setFileName(rtrace);
}

std::string VideoTrace::getNextChunk() {

    std::string name = content_name;
    name.append("#");

    seqn += 1; //Next sequence number

    stringstream ss;
    ss << seqn;
    name.append(ss.str());
    return name;
}

std::string VideoTrace::getChunk() {
    std::string name = content_name;
    name.append("#");

    //Request the first chunk
    stringstream ss;
    ss << seqn;
    name.append(ss.str());

    return name;
}

int VideoTrace::receiveMessage(datachunk *chunks) {

    videochunks_rx vrx;
    vrx.pkt_id_ = chunks->pkt_id_;
    vrx.stime_ = chunks->stime_;  //Register the arrival time
    vrx.rtime_ = simTime().dbl();
    vrx.packetSize_ = chunks->packetSize_;

    double rdelay = simTime().dbl() - chunks->stime_;

    delay_sum += rdelay;
    ndelay++;

    if (simTime() - last_delay > BULK_TIME) {
        rttOutVector.record(delay_sum/ndelay);
        ndelay = 0;
        delay_sum = 0;
        last_delay = simTime();
    }

    VideoChunks.push_back(vrx);
    remain = chunks->remain;

    if (remain > 0) {
        seqn = chunks->pkt_id_;
        return seqn;
    } else
        return 0;
}

void VideoTrace::clear() {
    seqn = 0;
    VideoChunks.clear();
    wasSent = false;
    remain = 0;
}

void VideoTrace::finish() {

    rdumpfile->open("w");
    sdumpfile->open("w");

    //FIXME[EAMA] Bolar um jeito melhor de fazer isso,
    //estou simulando o envio dos pacotes perdidos pegando a média entre dois
    //pacotes.

    if (rdumpfile->isOpen() && sdumpfile->isOpen()) {

        videochunks_v::iterator it = VideoChunks.begin();
        int last = 0;
        char buf[100];
        double rdelay = 0;
        double gap = 0;
        //cerr << VideoChunks.size() << endl;
        for (; it != VideoChunks.end(); it++) {

            gap = (*it).pkt_id_ - (last + 1);

            //delayed packets are discarded
            if (gap < 0) {
                out_of_order++;
                continue;
            }

            while (gap--) {
                pkts_dropped++;
                sprintf(buf, "%-16f id %-16d udp %-16d\n", (*it).stime_,
                        (last + 1), (*it).packetSize_);
                sdumpfile->add(buf);
                sprintf(buf, "%-16f id %-16d lost %-16d\n", (*it).stime_,
                        (last + 1), (*it).packetSize_);
                rdumpfile->add(buf);
                last += 1;
            }

            //Record the sender frame
            sprintf(buf, "%-16f id %-16d udp %-16d\n", (*it).stime_,
                    (*it).pkt_id_, (*it).packetSize_);
            sdumpfile->add(buf);

            //Record the received frame
            rdelay = (*it).rtime_ - (*it).stime_;

            if (rdelay > maxdelay) {
                sprintf(buf, "%-16f id %-16d lost %-16d\n", (*it).rtime_,
                        (*it).pkt_id_, (*it).packetSize_);
                rdumpfile->add(buf);
            } else {
                sprintf(buf, "%-16f id %-16d udp %-16d\n", (*it).rtime_,
                        (*it).pkt_id_, (*it).packetSize_);
                rdumpfile->add(buf);
            }

            last = (*it).pkt_id_;
        }
        rdumpfile->close();
        sdumpfile->close();
    }

}

void VideoTrace::toYuv() {
    char cmd[128];

    // int found = mp4_original.find(".");
    size_t found = -1;

    if ((found = mp4ReconstructedPath.find(".") != std::string::npos)) {
        found = mp4ReconstructedPath.find_last_of(".");
    }

    string mp4_to_yuv = mp4ReconstructedPath.substr(0, found);
    mp4_to_yuv.append(".yuv");

    sprintf(cmd, "avconv -i %s %s -v quiet ", mp4ReconstructedPath.c_str(), mp4_to_yuv.c_str());
    system(cmd);
}

void VideoTrace::cleanAll() {

    //char cmd[64];
    string cmd = "rm -f ";

    string noext = Util::getNoExt(mp4ReconstructedPath);

    cmd.append(workdir);
    cmd.append("/*");
    cmd.append( Util::getNoExt(mp4ReconstructedName));
    cmd.append("* ");
//    cmd.append(noext.c_str());
//    cmd.append(".* ");

    //sprintf(cmd, "rm -f %s.m4v", noext.c_str());
    //system(cmd);

    //sprintf(cmd, "rm -f %s.mp4", noext.c_str());
    //system(cmd);

    //sprintf(cmd, "rm -f %s.yuv", noext.c_str());
    //system(cmd);

    cmd.append(Util::getNoExt(sdumpfile->getFilePath()));
    cmd.append("* ");
    cmd.append(Util::getNoExt(rdumpfile->getFilePath()));
    cmd.append("* ");
    /*
    sprintf(cmd, "rm -f %s", sdumpfile->getFileName());
    system(cmd);

    sprintf(cmd, "rm -f %s", rdumpfile->getFileName());
    */

    system(cmd.c_str());

}

void VideoTrace::eval(string mp4_original) {

    EvaluateTrace *eval = new EvaluateTrace();
    eval->setSDump(sdumpfile);
    eval->setRDump(rdumpfile);
    //eval->setMP4file("a01.mp4");

    string mp4file = workdir;

    if (mp4file.at(mp4file.length() - 1) != '/')
        mp4file.append("/");

    mp4file.append(mp4_original);

    eval->setMP4file(mp4file.c_str());

    //eval->setMP4Output("a01_reconstructed.mp4");
    eval->setMP4Output(mp4ReconstructedPath.c_str());
    //eval->setSenderTrace("st_a01.tr");

    eval->setSenderTrace(trace.c_str());
   if( eval->evaluate() == EXIT_FAILURE){
       cerr << "ERROR| Cannot evaluate " << mp4ReconstructedPath.c_str() ;
       cleanAll();
   }

    delete eval;
    eval = 0;
}


void VideoTrace::reconstructing(string mp4_original) {

    char cmd[128];

    sprintf(cmd, "cd %s; etmp4 -F -x %s %s st_a01.tr %s %s ; cd ..",workdir.c_str(),
            sdumpfile->getFileName(),rdumpfile->getFileName(),mp4_original.c_str(),mp4ReconstructedName.c_str());


//    std::cerr << cmd << endl;

    system(cmd);

}
VideoTrace::~VideoTrace() {

    delete rdumpfile;
    delete sdumpfile;

}

