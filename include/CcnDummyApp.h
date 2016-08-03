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

#ifndef CcnDummyApp_H_
#define CcnDummyApp_H_

#include <ctime>
#include <omnetpp.h>
#include "videotraffic/VideoTrace.h"
#include "CcnAppMessage_m.h"
#include "QoEMetric.h"
#include "ICcnApp.h"
#include "shared.h"

#define INTERVAL_REQUEST 0.5
#define NAME_SIZE 64
#define BULK_TIME 1.0

#define SEND_OTHER_VIDEO truncnormal(20,5)

#define APPID 100
#define INTERVAL 0.3

class CcnDummyApp : public cSimpleModule, public ICcnApp {
public:
    CcnDummyApp();
    virtual ~CcnDummyApp();
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
    void transmitNext();
    virtual int numInitStages() const  {return 6;}


private:
    VideoTrace *video;
    //'cMessage *event;
    cMessage *timeout_video;
    QoEMetric *metric ;

    int howmany;
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
    double ds_stop;
    long pktsent;
    long  pktreceived;

    simsignal_t hitHopSignal;
    simsignal_t rttSignal;

    simsignal_t app_throughput;
    double bytes_;
    cMessage* thorugput_timer;

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

#endif /* CcnDummyApp_H_ */
