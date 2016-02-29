#include "RankCache.h"
#include "Util.h"

RankCache::RankCache(uint32_t cache_size) {

    this->cache_size = cache_size;
    T = 5;
    alpha = 0.05;
    K = 0.7;
    n = 0;
    Rc = 1;
    tot = 0;

    calcOut.setName("rc");

    pos = 0;
    neg = 0;
}

bool RankCache::data_to_cache(CcnPacket *data) {

    n++;
    bool decision = false;
    double prc = 0;
    chunk_t name = Util::removeChunkId(std::string(data->getName()));
    int seqn = Util::getChunkId(std::string(data->getName()));
   // __history ::iterator it = history.find(name);

    int Hc = data->getTSB();
    int Hh = data->getTSI();
    double Rp = ((double) Hc / Hh);
    prc = Rp*Rc;

 /*
     if ( it != history.end()) {
        (it)->second.npkts += 1;

        double phat = 1.0*pos/n;
        Rc = (phat + z*z/(2*n) - z * sqrt((phat*(1-phat)+z*z/(4*n))/n))/(1+z*z/n);
        (it)->second.t = simTime();
    }
*/
    //prop.record(prc);

    double x = dblrand();
    if (x < prc) {

        decision = true;
        //data->setAS(true);
#ifdef HISTORY_POLICE
        hist_entry entry;
        entry.t = simTime();
        entry.last_seqn = seqn;
        entry.npkts = 1;
        history[name] = entry;
#endif

    }

    if(decision)
        pos++;
    else
        neg++;

    return decision;
}

//bool RankCache::data_to_cache(CcnPacket *data) {
//
//    n++;
//    bool decision = false;
//    //double prc = 0;
//    // chunk_t name = Util::removeChunkId(std::string(data->getName()));
//    //int seqn = Util::getChunkId(std::string(data->getName()));
//    // __history ::iterator it = history.find(name);
//    int rank = data->getRank();
//    if (rank < Rc) {
//        data->setRank(Rc);
//        decision = true;
//    } else
//        decision = false;
//
//
////     int Hc = data->getTSB();
////     int Hh = data->getTSI();
////     double Rp = ((double) Hc / Hh);
////     prc = Rp*Rc;
//
//    /*
//     if ( it != history.end()) {
//     (it)->second.npkts += 1;
//     data->setPop((it)->second.npkts);
//     double phat = 1.0*pos/n;
//     Rc = (phat + z*z/(2*n) - z * sqrt((phat*(1-phat)+z*z/(4*n))/n))/(1+z*z/n);
//     (it)->second.t = simTime();
//     }
//     */
//    //prop.record(prc);
////     double x = dblrand();
////     if (x < prc) {
////
////         decision = true;
////         //data->setAS(true);
//// #ifdef HISTORY_POLICE
////         hist_entry entry;
////         entry.t = simTime();
////         entry.last_seqn = seqn;
////         entry.npkts = 1;
////         hi story[name] = entry;
//// #endif
////
////     }
//    if (decision)
//        pos++;
//    else
//        neg++;
//
//    if (pos % 100)
//        updateRank();
//
//    return decision;
//}

void RankCache::updateRank() {


    double phat = 1.0 * pos / n;
    Rc = (phat + z * z / (2 * n) - z * sqrt((phat * (1 - phat) + z * z / (4 * n)) / n)) / (1 + z * z / n);

    calcOut.record(Rc);

}
