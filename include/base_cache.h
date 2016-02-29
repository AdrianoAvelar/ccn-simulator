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
#ifndef B_CACHE_H_
#define B_CACHE_H_

#include "ccnsim.h"
#include "CcnPacket_m.h"

class DecisionPolicy;

//Base cache class: it implements the basic behaviour of every cache by the mean of two abstract functions:
//
//-) data_store: stores chunks within the cache with a given policy
//-) data_lookup: return if the given chunk exists within the cache
//
struct cache_stat_entry{
    unsigned int  miss; //Total number of misses
    unsigned int  hit; //Totatle number of hit
    cache_stat_entry():miss(0),hit(0){;}
    double rate(){ return hit *1./(hit+miss);} //return the miss rate of the class
};

struct cache_response{
    void *data;
    int size;
};

class base_cache : public abstract_node{
    friend class statistics;

    public:

    virtual ~base_cache();
    //Inteface function (depending by internal data structures of each cache)
    virtual void data_store (cMessage *msg) = 0;
    virtual cache_response* data_lookup(CcnPacket *) = 0;

    protected:

	void initialize();
	void handleMessage (cMessage *){;}
	void finish();

	//virtual bool isfull();
	virtual void dump(){cout<<"Not implemented"<<endl;}
	
    public:
	//Outside function behaviour
	double get_size() { return cache_size; }

	virtual double get_current_size(){return -1;};

	cache_response * lookup(cMessage *msg);

	void store (cMessage *);
	//void store(chunk_t,void*,int);

	void clear_stat();

    private:
	double  cache_size;
	int  nodes;
	int level;

	DecisionPolicy *decisor;

	//Average statistics
	uint32_t miss;
	uint32_t hit;

	uint32_t tot_pkt;
	double tot_delay;

	//cOutVector cacheSize;
	simsignal_t hitRateSignal;
	simsignal_t cacheDecisionTimeSignal;

	simtime_t last_rec;

	//Per file statistics
	cache_stat_entry *cache_stats;

	long chunks;
	double totElapsedTime;

};

#endif
