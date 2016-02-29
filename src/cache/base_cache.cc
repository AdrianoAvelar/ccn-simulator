/*
 * ccnSim is a scalable chunk-level simulator for Content Centric
 * Networks (CCN), that we developed in the context of ANR Connect
 * (http://www.anr-connect.org/)
 *
 * People:
 *    Giuseppe Rossini (lead developer, mailto giuseppe.rossini@enst.fr)
 *    Raffaele Chiocchetti (developer, mailto raffaele.chiocchetti@gmail.com)
 *    Dario Rossi (occasional debugger, mailto dario.rossi@enst.fr)
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <cmath>
#include "base_cache.h"
#include "statistics.h"

#include "fix_policy.h"
#include "lcd_policy.h"
#include "betweenness_centrality.h"
#include "never_policy.h"
#include "always_policy.h"
#include "decision_policy.h"

#include "prob_cache.h"
#include "Util.h"
#include "RankCache.h"

#include "ccnsim.h"
#include <ctime>

//Initialization function
void base_cache::initialize() {


    chunks = 0;
    tot_delay = 0;
    char nome[32];
    hitRateSignal = registerSignal("hit_rate");
    cacheDecisionTimeSignal = registerSignal("decisionTime");

    sprintf(nome, "velocity_%s", getParentModule()->getParentModule()->getName());

    cache_size = intuniform(10,90);
    string decision_policy = par("cache_policy");


    if (decision_policy.compare("lcd") == 0) {
        decisor = new LCD();
    } else if (decision_policy.find("fix") == 0) {
        string sp = decision_policy.substr(3);
        double dp = atof(sp.c_str());
        decisor = new Fix(dp);
    } else if (decision_policy.find("btw")==0) {
        double db = getAncestorPar("centrality");
        decisor = new Betweenness(db);
    } else if (decision_policy.find("prob_cache")==0){
        decisor = new prob_cache(cache_size);
    } else if (decision_policy.find("lce") == 0) {
        decisor = new Always();
    } else if (decision_policy.find("never") == 0){
        decisor = new Never();
    } else if (decision_policy.find("rank_cache") == 0){
        decisor = new RankCache(cache_size);
    }

    //Cache statistics
    //--Average
    miss = 0;
    hit = 0;
    last_rec = 0;

}

void base_cache::finish() {

}

//Base class function: a data has been received:
void base_cache::store(cMessage *msg) {
    cache_size = get_size();

    if (cache_size == 0)
        return;

    char name[16];
    CcnPacket *pkt = dynamic_cast<CcnPacket*>(msg);
    if (pkt) {

        clock_t start = clock();
        int decision  = decisor->data_to_cache(pkt);
        clock_t ends = clock();
       // totElapsedTime += (double) (ends - start) / CLOCKS_PER_SEC;
        emit(cacheDecisionTimeSignal,(double) (ends - start) / CLOCKS_PER_SEC);
        chunks++;

        if (decision){
            data_store(msg); //store is an interface funtion: each caching node should reimplement that function
            sprintf(name,"stored:%f",get_current_size());
            getParentModule()->getParentModule()->bubble(name);
        }
    }
}

//Base class function: lookup for a given data
//it wraps statistics on misses and hits
cache_response * base_cache::lookup(cMessage *msg) {

    cache_response * found = NULL;

    CcnPacket *ccnPkt = dynamic_cast<CcnPacket *>(msg);

    if(!ccnPkt)
        return found;

    double delay = ccnPkt->getSumDi();
    if(delay > 0)
    {
        tot_pkt++;
        tot_delay+= delay;
    }

    found = data_lookup(ccnPkt);

    if (found != NULL) {
        hit++;
    } else {
        miss++;
    }

    if(simTime() - last_rec  > Util::getBulkTime()){

        emit(hitRateSignal,hit * 1. / (hit + miss));
        last_rec = simTime();
    }

    ccnPkt = 0;

    return found;
}

//Clear all the statistics
void base_cache::clear_stat() {
    hit = miss = 0; //local statistics
    delete cache_stats;
    //  cache_stats = new cache_stat_entry[__file_bulk+1];
}

base_cache::~base_cache(){
delete decisor;

}
