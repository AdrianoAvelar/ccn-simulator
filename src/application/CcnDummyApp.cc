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

#include "CcnDummyApp.h"
#include "commons.h"

#include "Util.h"

Define_Module (CcnDummyApp);

CcnDummyApp::CcnDummyApp() {
    pktsent = 0;
    pktreceived = 0;
    metric = 0;
    rtt_sum = 0;
    rtt_tot = 0;
    nrtt = 0;
    dummy_active = false;
    bytes_ = 0;
}

CcnDummyApp::~CcnDummyApp() {

    if (arrival != 0)
        cancelAndDelete(arrival);

    if (event != 0)
        cancelAndDelete(event);

    if(thorugput_timer != 0)
        cancelAndDelete(thorugput_timer);

}

void CcnDummyApp::registerMyselfInCcnLayer(){

    if(gateSize("ccnOut") == 0)
    {
        error("This application cannot be unconnected");
    }
    Ccn* ccn = getModuleFromPar<Ccn>(par("ccndModule"), this);
    cGate *mygate = gate("ccnIn");
    ccn->registerApp(appId,mygate);
}

/**
 * Initialization and termination of the module
 */
void CcnDummyApp::initialize(int stage) {

    if(stage ==4 ){
    //Timers
    begin = Util::currentDateTime();
    start = clock();

    appId = CCN_DUMMY_APP + getIndex();

    base_contentname = par("base_contentname").stringValue();

    lambda = par("lambda").doubleValue();

    double ds_start = par("startTime");
    double ds_stop = par("stopTime");

    if (ds_stop > 0) {
        cMessage* end = new cMessage("STOP_SIMULATION");
        end->setKind(STOP_SIMULATION);
        scheduleAt(simTime() + ds_stop, end);
    } else
        opp_error("You have to define a stop time for dummy traffic.");


    registerMyselfInCcnLayer();

    arrival = new cMessage("START_DUMMY");
    arrival->setKind(START_DUMMY);
    dummy_active = true;
    scheduleAt(simTime() + ds_start, arrival);

 //   char nome[32];
//    sprintf(nome, "hit_hop_%s", getParentModule()->getName());
    hitHopSignal = registerSignal("hit_hop");

//    sprintf(nome, "rtt_all_pkts_%s", getParentModule()->getName());
//    rtt_vector.setName(nome);
    rttSignal = registerSignal("rtt_all_pkts");
    last_rtt = simTime();

    //app throughput
    app_throughput = registerSignal("app_throughput");
    thorugput_timer = new cMessage("AppThroughput");
    scheduleAt(simTime() + ds_start, thorugput_timer);
    }
}

void CcnDummyApp::handleMessage(cMessage *msg) {

    if (msg->isSelfMessage()) {

        if (msg->getKind() == CCN_APP_INTEREST) {

            CcnAppMessage * ccn_i = static_cast<CcnAppMessage *>(msg);

            downloads[string(ccn_i->getContentName())] = simTime().dbl();
            ccn_i = 0;
            send(msg, "ccnOut");

        } else if (msg->getKind() == START_DUMMY) {

            if (dummy_active) {
                requestDummyFile();

                pktsent++;
                arrival->setKind(START_DUMMY);
                double nextDummySend = exponential(1 / lambda);
                scheduleAt(simTime() + nextDummySend, arrival);
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
            fprintf(stderr, "CcnDummyApp::handleMessage/ Unknown Action!");
            delete msg;
        }
    }
}

void CcnDummyApp::requestDummyFile() {

    getParentModule()->bubble("send dummy");
    CcnAppMessage * ccn_i = new CcnAppMessage("Interest");
    ccn_i->setType(CCN_APP_INTEREST);
    ccn_i->setSeqNr(1);
    ccn_i->setNumChunks(1);
    ccn_i->setChunkSize(par("chunkSize"));
    ccn_i->setAppId(appId);

    unsigned int number = Ccnr::zipf.value(dblrand());
    char name[NAME_SIZE];
    sprintf(name, "%s%s%u", base_contentname.c_str(), DUMMY_TAG, number);

    ccn_i->setContentName(name);

    downloads[string(ccn_i->getContentName())] = simTime().dbl();
    send(ccn_i, "ccnOut");
}

void CcnDummyApp::handlerData(CcnAppMessage * msg) {

    string name(msg->getContentName());

    if (downloads.find(name) != downloads.end() && msg->getType() == CCN_APP_CONTENT) {

        double rtt_ = downloads[name];
        bytes_ += msg->getChunkSize();
        rtt_sum += simTime().dbl() - rtt_;
        downloads.erase(name);
        nrtt++;

        if (simTime() - last_rtt > BULK_TIME) {

            emit(rttSignal, rtt_sum/nrtt);
           // rtt_vector.record(rtt_sum / nrtt);

            nrtt = 0;
            rtt_sum = 0;
            last_rtt = simTime();
        }

        pktreceived++;
        emit(hitHopSignal,msg->getHops());
    }


    delete msg;
}

void CcnDummyApp::finish() {

    static bool once = false;
    if (!once) {
        cerr << "Begin at: " << begin << endl;
        cerr << "End at: " << Util::currentDateTime() << endl;
        clock_t ends = clock();
        cerr << "Running Time : " << (double) (ends - start) / CLOCKS_PER_SEC
                << " s" << endl;

        once = true;
    }

    char nome[32];
    sprintf(nome, "pkts_sent_%s", getParentModule()->getName());
    recordScalar(nome, pktsent);
    sprintf(nome, "pkts_received_%s", getParentModule()->getName());
    recordScalar(nome, pktreceived);

    sprintf(nome, "pkts_dropped_%s", getParentModule()->getName());
    recordScalar(nome, pktsent - pktreceived);
    // for(int i = 0; i < (pktsent - pktreceived); i++)
    //     rtt_vector.record(0);

    downloads.clear();
}

