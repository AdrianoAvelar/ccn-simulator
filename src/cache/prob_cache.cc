#include "prob_cache.h"

bool prob_cache::data_to_cache(CcnPacket *data) {

    /*
     std::cerr<<"Capacity:"<<data->getCapacity()<<endl;
     std::cerr<<"TSB:"<< data->getTSB()<<endl;
     std::cerr<<"TSI:"<< data->getTSI()<<endl;
     */

    double times_in, w, p, x;
    bool decision = false;

    times_in = data->getCapacity() * 1. / (10 * N);
    w = data->getTSB() * 1. / data->getTSI();
    p = w * times_in;
    x = dblrand();


#ifdef DEBUG
    std::cerr << "************\nTimesIn: " << times_in << endl;
    std::cerr << "Weight: " << w << endl;
    std::cerr << x << " < " << p << " ? = "
            << ((x < p) == 0 ? "don't store!" : "store!") << endl;
#endif

    if (x < p) {
        decision = true;
    }

    data->setCapacity(data->getCapacity() - N);
    data->setTSB(data->getTSB() + 1);
    return decision;

}
