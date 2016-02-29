/*
 * File:   VideoTrafficGenerator.cpp
 * Author: adriano
 *
 * Created on 5 de Fevereiro de 2014, 16:55
 */

#include "VideoTrafficGenerator.h"
#include "CcnAdmin.h"

VideoTrafficGenerator::VideoTrafficGenerator() {
    tfile_ = (SenderTrace*) NULL;
    pktsize_ = 1024;
    max_ = 1054;
    totalTime = 0;
    fragment = 0;
    framepktid_ = 0;
    debugLevel = CcnAdmin::debugLevel;
    f_ = 0;

}

bool VideoTrafficGenerator::fillchunk(datachunk *chunk){

    unsigned long x_, y_;


       if (!running_){
           DBGPRT(EVAUX, Info, "VideoTrafficGenerator::fillchunk") <<
                   "The traffic generator is not running.. have you call init()?";
           return false;
       }

       if (tfile_->get_a() == 1) {
           running_ = false;
           return false;
       }

       x_ = pktsize_ / max_;
       y_ = pktsize_ % max_;

       chunk->priority_ = p_;
       chunk->pkt_id_  = framepktid_++;
       chunk->packetType_ = PT_VIDEO;
       chunk->frametype_ = f_;
       chunk->stime_ = simTime().dbl();

       /* If we have to brake the packets into a several pieces,
        * we should retorn each pieace. We won't go futher until to
        * send back all the fragments */
       if (x_ > 0 ) {

           if (fragment < x_) {
               chunk->packetSize_ = max_;
               sprintf(output,"FRAGMENT pktid: %d pktsize: %d, max_:%ld, x_:%lud, y_:%lud\n",framepktid_, pktsize_,
                       max_,x_, y_);

               DBGPRT(EVAUX, Info, "VideoTrafficGenerator::fillchunk")
                   << output;

               fragment++;

               return true;
           } else {
               fragment = 0;
           }


       }
       chunk->packetSize_ = y_;

       if (y_ != 0){
           sprintf(output,"pktid: %d pktsize: %d, max_:%ld, x_:%lud, y_:%lud\n",framepktid_, pktsize_,
                                  max_,x_, y_);
           DBGPRT(EVAUX, Info, "VideoTrafficGenerator::fillchunk")
                             << output;
       }

      nextPkttime_ = next_interval(pktsize_);
      chunk->stime_ = nextPkttime_;

       return true;
}

void VideoTrafficGenerator::init() {

    if (tfile_)
        ndx_ = tfile_->setup();

    running_ = true;

}

void VideoTrafficGenerator::setTraceFile(SenderTrace *traceFile) {
    tfile_ = traceFile;
}

double VideoTrafficGenerator::timeout(VideoPacket * packet) {

    unsigned long x_, y_;

    if (!running_)
        return -1;

    if (tfile_->get_a() == 1) {
        running_ = false;
        return -1;
    }


    x_ = pktsize_ / max_;
    y_ = pktsize_ % max_;

    //    agent_->set_prio(p_);
    //    agent_->set_pkttype(PT_VIDEO);
    //    agent_->set_frametype(f_);

    packet->setPriority_(p_);
    packet->setFrametype_(f_);
    packet->setPacketType_(PT_VIDEO);

    packet->setFrame_pkt_id_(framepktid_++);

    /* If we have to brake the packets into a several pieces,
     * we should retorn each pieace. We won't go futher until to
     * send back all the fragments */
    if (x_ > 0 ) {

        if (fragment < x_) {
            packet->setPacketSize_(max_);
            fprintf(stderr,"FRAGMENT pktid: %d pktsize: %d, max_:%ld, x_:%lud, y_:%lud\n",framepktid_, pktsize_,
                                              max_,x_, y_);

            fragment++;

            return 0;
        } else {
            fragment = 0;
        }

        // agent_->sendmsg(max_ + 28); //udp header + ip header ( 8 + 20 =28 bytes)
    }
    packet->setPacketSize_(y_);

    if (y_ != 0)
        fprintf(stderr,"pktid: %d pktsize: %d, max_:%ld, x_:%lud, y_:%lud\n",framepktid_, pktsize_,
                                          max_,x_, y_);
    //agent_->sendmsg(y_ + 28);

    /* figure out when to send the next one */


   nextPkttime_ = next_interval(pktsize_);

    /* schedule it */
//    printf("***NextPktTime %f\n", nextPkttime_ * 10000);
//    usleep(1000);
//    timeout();
    if(nextPkttime_ > 0)
        totalTime += nextPkttime_;

    fprintf(stderr,"TotalTime(s): %f nextPkttime_: %f\n",totalTime,nextPkttime_);

    return nextPkttime_;
    //timer_.resched(nextPkttime_);
}

double VideoTrafficGenerator::next_interval(int& size) {
    tfile_->get_next(ndx_, trec_);

    if (tfile_->get_a() == 1)
            return -1;

    size = trec_.trec_size;
    f_ = trec_.trec_type;
    p_ = trec_.trec_prio;
    max_ = trec_.trec_max;
    return (((double) trec_.trec_time) / 1000000.0); /* usecs->secs */
}

VideoTrafficGenerator::~VideoTrafficGenerator() {

    if(tfile_ )
        tfile_->close();

}
