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

#ifndef VIDEOTRACE_H_
#define VIDEOTRACE_H_

#include "Ccnr.h"
#include "FileHandlers/DumpFile.h"

#define BULK_TIME 1.0

struct videochunks_rx_ {
   int pkt_id_;
   double stime_;
   double rtime_;
   int packetSize_;
};

typedef struct videochunks_rx_ videochunks_rx;

typedef std::vector<videochunks_rx> videochunks_v;

//FIXME[EAMA] Move to ini configuration
#define FRAME_WIDTH     352
#define FRAME_HEIGHT    288
#define YUV_FORMAT      420
#define YUV_REF         "results/akiyo_cif.yuv"

#define TRACE_REF "st_ref.tr"

class VideoTrace {
public:
    VideoTrace(std::string workdir, std::string trace, string mp4_reconstructed);
    virtual ~VideoTrace();

    int receiveMessage(datachunk *chunks);
    void setTraceFile(const char* send_trace,const char* receiver_trace);
    void finish();
    void clear();
    void setWordDir();
    void eval(string mp4_original);

    void cleanAll();

    void toYuv();

    std::string getNextChunk();
    std::string getChunk();

    inline void setContentName(std::string content_name){
       this->content_name = content_name;
    }
    inline int getSeqN(){
        return seqn;
    }

    inline void setWordDir(std::string dir){
        this->workdir = dir;
    }

    inline void setMaxDelay(double maxdelay){
        this->maxdelay = maxdelay;
    }

    inline int getRemain(){
        return this->remain;
    }

    inline int setRemain(int remain){
        this->remain = remain;
    }

    inline void setWasSent(bool wasSent){
        this->wasSent = wasSent;
    }
    inline bool getWasSent(){
        return this->wasSent;
    }

    inline string getBaseName(){
        return mp4file_rec;
    }



private:
    DumpFile *sdumpfile;
    DumpFile *rdumpfile;
    videochunks_v VideoChunks;
    std::string content_name;
    std::string workdir;
    int seqn;
    std::string trace;
    double maxdelay;
    int remain;
    bool wasSent;
    string mp4file_rec;
    int out_of_order;
    int pkts_dropped;
    cOutVector rttOutVector;

    double delay_sum;
    int ndelay;
    simtime_t last_delay;


};

#endif /* VIDEOTRACE_H_ */
