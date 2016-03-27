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

#include "CcnVideoApp.h"
#include "commons.h"

#include "Util.h"

Define_Module (CcnVideoApp);

CcnVideoApp::CcnVideoApp() {
    timeout_video = 0;
    event = 0;
    arrival = 0;
    video_count = 0;
    count_req = 0;
    max_retrans_attempts = 0;
    retrans_attempts = 0;
    pktsent = 0;
    pktreceived = 0;
    metric = 0;
    rtt_sum = 0;
    rtt_tot = 0;
    nrtt = 0;
    video = 0;
    dummy_active = false;
    frame_interval = 0;

    bytes_ = 0;
}

CcnVideoApp::~CcnVideoApp() {

    if (arrival != 0)
        cancelAndDelete(arrival);

    if (event != 0)
        cancelAndDelete(event);

    if (metric != 0)
        delete metric;

    if(video != 0)
        delete video;

    if(timeout_video != 0)
        cancelAndDelete(timeout_video);

    if(thorugput_timer != 0)
           cancelAndDelete(thorugput_timer);

}

/**
 * Initialization and termination of the module
 */
void CcnVideoApp::initialize(int stage) {

    //Timers
    if(stage == 4){
    begin = Util::currentDateTime();
    start = clock();

    appId = CCN_VIDEO_APP + getIndex();

    video_count = par("video_count");
    base_contentname = par("base_contentname").stringValue();
    max_delay = par("max_delay").doubleValue() / 1000; //ms to s.
    interestLifetime = par("interestLifetime").doubleValue() / 1000; //ms to s
    max_retrans_attempts = par("max_retrans_attempts");
    num_dummy_chunks = par("num_dummy_chunks");

    frame_interval = par("frame_interval");

    currentRunId  = ev.getConfigEx()->getActiveRunNumber();

    lambda = par("lambda").doubleValue();

    double startTime = par("startTime");

    char rec[64];
    sprintf(rec, "%s_rid_%d.mp4", getParentModule()->getName(), currentRunId);
    timeout_video = new cMessage("Timeout_Video");

    video = new VideoTrace("results", TRACE_REF, rec);
    metric = new QoEMetric(Util::getNoExt(video->getBaseName()).c_str());

    event = new cMessage("SEND_OP");
    event->setKind(SEND_OP);
    scheduleAt(simTime() + startTime, event);

    registerMyselfInCcnLayer();

    char nome[32];
    sprintf(nome, "hit_hop_%s", getParentModule()->getName());
    hit_hop.setName(nome);

    sprintf(nome, "rtt_all_pkts_%s", getParentModule()->getName());
    rtt_vector.setName(nome);

    last_rtt = simTime();

    app_throughput = registerSignal("app_throughput");

    thorugput_timer = new cMessage("AppThroughput");
    scheduleAt(simTime() + startTime, thorugput_timer);
    }
}

void CcnVideoApp::registerMyselfInCcnLayer(){

    if(gateSize("ccnOut") == 0)
    {
        error("This application cannot be unconnected");
    }

    Ccn* ccn = getModuleFromPar<Ccn>(par("ccndModule"), this);
    cGate *mygate = gate("ccnIn");
    ccn->registerApp(appId,mygate);
    ccn->registerChunkListener("*",appId);
}


void CcnVideoApp::handleMessage(cMessage *msg) {

    if (msg->isSelfMessage()) {

        if (msg->getKind() == CCN_APP_INTEREST) {

            CcnAppMessage * ccn_i = static_cast<CcnAppMessage *>(msg);

            downloads[string(ccn_i->getContentName())] = simTime().dbl();
            ccn_i = 0;
            send(msg, "ccnOut");

        } else if (msg->getKind() == EVALUATE) {

            evaluate();
            delete msg;

        } else if (msg->getKind() == EVALUATE_INCOMPLETED_FILE){

            evaluate(par("requestInterval").doubleValue());
            delete msg;
        }else if (msg->getKind() == SEND_OP) {

            requestFile();

        } else if (msg->getKind() == TIMEOUT) {
            //We lost last packet, so get next.

            if (retrans_attempts < max_retrans_attempts) {
                //Forget the missing chunks and try another.
                //It's a streaming service.
                retransmiting();
                retrans_attempts++;
            } else {
                fprintf(stderr,
                        "[ERROR] Run out Interest Retransmission Attempts.. at module %s\n",getParentModule()->getName());

                //Send other video if exists.
                cMessage *eval = new cMessage("EVALUATE");
                eval->setKind(EVALUATE_INCOMPLETED_FILE);
                scheduleAt(simTime(),eval);

                retrans_attempts = 0;
            }

        } else if (msg->getKind() == STOP_DUMMY) {
            //Stop to send packets.
            dummy_active = false;
            delete msg;
        } else if (msg->getKind() == STOP_SIMULATION) {
            delete msg;
            endSimulation();

        }else if(msg == thorugput_timer){

            double thr = bytes_/(INTERVAL)*8/1000000;
            bytes_ = 0;
            emit(app_throughput,thr);
            scheduleAt(simTime()+INTERVAL,thorugput_timer);
         }

    } else {

        CcnAppMessage * ccnmsg = dynamic_cast<CcnAppMessage *>(msg);
        if (!ccnmsg) {
            EV << this->getFullName()
                      << "Not a CcnAppMessage. Caught and sent to /dev/null."
                      << std::endl;
        }

        switch (ccnmsg->getAction()) {
        case CONTENT_SENDER_REGISTER:
            //Register sender.
            delete msg;
            break;
        case CONTENT_DELIVER:

            if (ccnmsg->getType() == CCN_APP_CONTENT) {
                handlerData(ccnmsg);
            }

            break;
        default:
            fprintf(stderr, "CcnVideoApp::handleMessage/ Unknown Action!");
            delete msg;
        }
    }
}


void CcnVideoApp::evaluate(double delay_to_another_request){

    video->finish();

    if (par("evaluate").boolValue() == true)
        video->reconstructing("a01.mp4");

    if (par("toYuv").boolValue() == true)
        video->toYuv();

    if(par("qoe_metrics").boolValue() == true)
    {
        metric->calculatePSNR();
        metric->calculateSSIM();
    }

    if (par("cleanall").boolValue() == true)
        video->cleanAll();

    if (count_req < video_count || video_count < 0) {
        event->setKind(SEND_OP);
        scheduleAt(simTime() + delay_to_another_request,event);
    }

}

void CcnVideoApp::requestFile() {

    char svideo_name[64], rvideo_name[64];
    sprintf(rvideo_name, "rd_a0%d_%s_rid_%d.tr", count_req,getParentModule()->getName(), currentRunId);
    sprintf(svideo_name, "sd_a0%d_%s_rid_%d.tr", count_req,getParentModule()->getName(), currentRunId);

    video->clear();

    video->setMaxDelay(max_delay);
    video->setWordDir("results");
    video->setTraceFile(svideo_name, rvideo_name);

    stringstream contentname;
    std::cerr << "CcnVideoApp::requestFile: random: " << dblrand() << std::endl;
    unsigned int number = Ccnr::zipf.value(dblrand());

    contentname << number;

    std::string cname = base_contentname;
    cname.append(VIDEO_TAG);
    cname.append(contentname.str());

    video->setContentName(cname);

    CcnAppMessage * ccn_i = new CcnAppMessage("Interest");
    ccn_i->setType(CCN_APP_INTEREST);

    ccn_i->setSeqNr(video->getSeqN());
    ccn_i->setNumChunks(1);
    ccn_i->setChunkSize(1);
    string chunk = video->getChunk();
    ccn_i->setAppId(appId);
    ccn_i->setContentName(video->getChunk().c_str());

    count_req++;
    timeout_video->setKind(TIMEOUT);
    scheduleAt(simTime()+ interestLifetime, timeout_video);

    downloads[string(ccn_i->getContentName())] = simTime().dbl();

    send(ccn_i, "ccnOut");
}

void CcnVideoApp::retransmiting() {

    CcnAppMessage * ccn_i = new CcnAppMessage("Interest");
    ccn_i->setType(CCN_APP_INTEREST);
    ccn_i->setSeqNr(video->getSeqN());
    ccn_i->setNumChunks(1);
    ccn_i->setChunkSize(100);
    string chunk = video->getChunk();

    ccn_i->setContentName(chunk.c_str());
    ccn_i->setAppId(appId);
    downloads[string(ccn_i->getContentName())] = simTime().dbl();


//    char msg[32];
//    sprintf(msg, "[ERROR] Retransmiting %s at %s",chunk.c_str(),getParentModule()->getName() );
//
   std::cerr << "[ERROR] Retransmiting " << chunk << " at " << getParentModule()->getName() << endl;

    timeout_video->setKind(TIMEOUT);
    scheduleAt(simTime()+ interestLifetime, timeout_video);

    send(ccn_i, "ccnOut");
}

void CcnVideoApp::handlerData(CcnAppMessage * msg) {

    int chunksBufferSize = msg->getByteArray().getDataArraySize();
    char *chunksBuffer = new char[chunksBufferSize];
    msg->copyDataToBuffer(chunksBuffer, chunksBufferSize);

    datachunk *chunk = (datachunk *) chunksBuffer;


    if (chunk->protocol == PT_VIDEO) {

        bytes_+= chunk->packetSize_;

        //Cancel timeout stuffs we got one packet.
        cancelEvent(event);
        retrans_attempts = 0;

        cancelEvent(timeout_video);

        video->receiveMessage(chunk);

        if (!video->getWasSent()) {

            int i;
            double nextSend;
            for (i = 0; i < video->getRemain(); i++) {

                CcnAppMessage * ccn_i = new CcnAppMessage("Interest");
                ccn_i->setType(CCN_APP_INTEREST);
                ccn_i->setContentName(video->getNextChunk().c_str());
                ccn_i->setSeqNr(video->getSeqN());
                ccn_i->setNumChunks(1);
                ccn_i->setChunkSize(1);
                ccn_i->setAppId(appId);
                ccn_i->setKind(CCN_APP_INTEREST);
                //nextSend += exponential(1 / lambda);
                nextSend += frame_interval;
                scheduleAt(simTime() + nextSend, ccn_i);
            }

            video->setWasSent(true);

            nextSend += frame_interval + interestLifetime;
            cMessage *eval = new cMessage("EVALUATE");
            eval->setKind(EVALUATE);
            scheduleAt(simTime() + nextSend, eval);
            //send(ccn_i, "ccnOut");
        }


    }

    string name(msg->getContentName());

    if(downloads.find(name) != downloads.end()){

        double rtt_ = downloads[name];
        rtt_sum += simTime().dbl() - rtt_;
        downloads.erase(name);
        nrtt++;

        if(simTime() - last_rtt  > BULK_TIME){
            rtt_vector.record(rtt_sum/nrtt);

            nrtt = 0;
            rtt_sum = 0;
            last_rtt = simTime();
        }

        if(chunk->protocol == PT_DUMMY)
            pktreceived++;

    }

    hit_hop.record(msg->getHops());

    delete msg;
    delete[] chunksBuffer;

}

void CcnVideoApp::finish() {

    static bool once = false;
    if(!once){
        cerr << "Begin at: " << begin << endl;
        cerr << "End at: " << Util::currentDateTime() << endl;
        clock_t ends = clock();
        double runningtime = (double) (ends - start) / CLOCKS_PER_SEC;

        cerr << "Running Time : " <<  ((int)runningtime)/60 << " m and "<<  ((int)runningtime)%60 << " s "<< endl;

        once = true;
    }

    char nome[32];
    sprintf(nome, "pkts_sent_%s", getParentModule()->getName());
    recordScalar(nome, pktsent);
    sprintf(nome, "pkts_received_%s", getParentModule()->getName());
    recordScalar(nome, pktreceived);

    sprintf(nome, "dropped", getParentModule()->getName());

    recordScalar(nome,pktsent - pktreceived );
   // for(int i = 0; i < (pktsent - pktreceived); i++)
   //     rtt_vector.record(0);

    downloads.clear();
}

