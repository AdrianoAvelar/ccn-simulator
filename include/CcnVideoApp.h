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

#ifndef CcnVideoApp_H_
#define CcnVideoApp_H_

#include <ctime>
#include <omnetpp.h>
#include "videotraffic/VideoTrace.h"
#include "CcnAppMessage_m.h"
#include "ICcnApp.h"

#include "QoEMetric.h"

#define INTERVAL_REQUEST 0.5
#define NAME_SIZE 64
#define BULK_TIME 1.0

#define SEND_OTHER_VIDEO truncnormal(20,5)


class CcnVideoApp : public cSimpleModule, public ICcnApp {
public:
    CcnVideoApp();
    virtual ~CcnVideoApp();
    virtual void handleMessage (cMessage *msg);
    virtual void registerMyselfInCcnLayer();

    /**
     * Initialization and termination of the module
     */
    virtual void    initialize(int);
    virtual void    finish();
    void requestFile();
    void requestDummyFile();
    void handlerData(CcnAppMessage * ccnmsg);
    void retransmiting();
    virtual int numInitStages() const  {return 6;}

private:
    VideoTrace *video;
    cMessage *event;
    cMessage *timeout_video;
    QoEMetric *metric ;

    int video_count;
    int count_req;
    std::string base_contentname;

    //FIXME[EAMA] Achar em algum artigo um valor para o delay max em aplicações de video streaming
    double max_delay;
    double interestLifetime;
    int max_retrans_attempts;
    int retrans_attempts;

    cMessage *arrival;
    double lambda;
    int num_dummy_chunks;
    long pktsent;
    long  pktreceived;

    cOutVector hit_hop;
    cOutVector rtt_vector;

    boost::unordered_map<std::string ,double> downloads;

    double rtt_sum;
    int rtt_tot;

    simtime_t last_rtt;
    int nrtt;

    bool dummy_active;
    //Timer of running
    string begin;
    clock_t start;

    double frame_interval;

    int currentRunId ;
    int appId;
};

#endif /* CcnVideoApp_H_ */
