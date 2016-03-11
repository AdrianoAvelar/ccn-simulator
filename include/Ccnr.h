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
#ifndef Ccnr_H
#define Ccnr_H
#include <omnetpp.h>
#include <boost/unordered_map.hpp>
#include "CcnPacket_m.h"
#include "ccnsim.h"
#include "zipf.h"


#pragma pack(push)
#pragma pack(1)
//
//This structure is very critical in terms of space. 
//In fact, it accounts for the startup memory requirement
//of the simulator, and should be keep as small as possible.
//
//


/*This struct is used to response a lookup.*/
struct ccnr_response {
    void *data;
    int size;
    double time;
};


struct __chunk {
    int priority_;
    int packetSize_;
    unsigned long pkt_id_;
    int packetType_;
    int frametype_ ;
    double stime_; //Sender Time
    double rtime_; //Receiver time.
    int protocol;
    int remain;
};


struct file {
    info_t info;
};

#pragma pack(pop)


typedef struct __chunk datachunk;

typedef std::vector<datachunk> chunks_entry;

using namespace std;

class Ccnr : public cSimpleModule {

    protected:
	virtual void initialize();
	virtual void handleMessage(cMessage *){;}
	virtual void finish();


    public:

	void init();

	//ccnr_response * lookup(chunk_t contentName);
	ccnr_response * lookup(CcnPacket *ccnPkt);
	int  getChunkId(chunk_t contentName);
	std::string removeChunkId(chunk_t contentName);
	void init_content();
	int *init_repos(vector<int>);
	int *init_clients(vector<int>);

	typedef map< chunk_t , chunks_entry > DATABASE;

	static vector<file> catalog;
	static zipf_distribution zipf;

	static name_t perfile_bulk;
	static name_t stabilization_bulk; 
	static name_t cut_off;
	static int  *repositories;
	static int  *clients;

	enum ids {
	    NONE = 0x1,
	    MP4FILE = 0x2
	};

	void addToCache(const char* contentName, const char* localPath);
	void addToDummyCache(const char *contentName, const int numChunks, const int chunkSize);
    private:

	chunks_entry CHUNK_ENTRY;
	DATABASE CCNR;
	DATABASE DB;
	vector<int> binary_strings(int,int);

	//INI parameters
	int num_repos;
	int num_clients;
	int nodes;
	int degree;
	int cardF;
	int F;

	double alpha;
	double q;

	uint32_t tot_pkt;
	double tot_delay;

};

#endif
