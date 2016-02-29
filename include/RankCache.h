/*
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
#ifndef PRIORITY_CACHE_H_
#define PRIORITY_CACHE_H_

#include "decision_policy.h"
#include <boost/unordered_map.hpp>
#include "ccnsim.h"

//#define DEBUG_CACHE
#define HISTORY_POLICE
#define GROUP_FLOW 100
#define BEST_EFFORT 3

#define z 1.96 //for 95% of Confidence Level
#define PENALTY_TIME 1

struct hist{
    int npkts;
    int last_seqn;
    simtime_t t;
};


class RankCache: public DecisionPolicy {
public:
    RankCache(uint32_t cache_size); //: k(0.5){; } //(int c):N(c){;}
    bool data_to_cache(CcnPacket *data);
    void updateRank();

private:

    typedef struct hist hist_entry;
    typedef boost::unordered_map < chunk_t , hist_entry > __history;
    __history history;

    double T;

     double K;
     double alpha;
     uint32_t cache_size;
     int n ;

     cOutVector calcOut;

     double Rc;
     uint32_t tot;
     uint32_t pos;
     uint32_t neg;
};

#endif

