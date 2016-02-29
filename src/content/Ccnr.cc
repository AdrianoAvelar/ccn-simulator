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
#include "ccnsim.h"
#include "Ccnr.h"
#include "zipf.h"
//#include "content_distribution.h"
#include <algorithm>
#include "videotraffic/FileHandlers/SenderTrace.h"
#include "videotraffic/VideoTraffic.h"
#include "Util.h"

Register_Class (Ccnr);

vector<file> Ccnr::catalog;
zipf_distribution Ccnr::zipf;

name_t Ccnr::stabilization_bulk = 0;
name_t Ccnr::perfile_bulk = 0;
name_t Ccnr::cut_off = 0;
int *Ccnr::repositories = 0;
int *Ccnr::clients = 0;

//Initialize the catalog, the Ccnr, and distributes contents among them.
void Ccnr::initialize() {


        nodes = 1;//getAncestorPar("n");

        num_repos = 1;//getAncestorPar("num_repos"); //Number of repositories (specifically ccn_node(s) who a repository is connected to)
        num_clients = 1;//getAncestorPar("num_clients");

        alpha = par("alpha");

        q = par("q");
        cardF = par("objects"); //Number of files within the system
        F = par("file_size"); //Average chunk size
        degree = 1;//getAncestorPar("replicas");

        catalog.resize(cardF + 1); // initialize content catalog

        tot_delay = 0;

}

void Ccnr::init() {

    double coff = par("cut_off");
    //
    //Zipf initialization
    //
    zipf = zipf_distribution(alpha, q, cardF);
    zipf.zipf_initialize();

    cut_off = zipf.value(coff);
    stabilization_bulk = zipf.value(0.9);
    perfile_bulk = zipf.value(0.5);

    char name[15];
    //
    //Repositories initialization
    //
    //cStringTokenizer tokenizer(getAncestorPar("node_repos"), ",");
    cStringTokenizer tokenizer("", ",");
    repositories = init_repos(tokenizer.asIntVector());

    //Useful for statitics: write out the name of each repository within the network
    for (int i = 0; i < num_repos; i++) {
        sprintf(name, "repo-%d", i);
        recordScalar(name, repositories[i]);
    }

    //
    //Clients initialization
    //
    if (num_clients < 0) //If num_clients is < 0 all nodes of the network are clients
        num_clients = nodes;

    //tokenizer = cStringTokenizer(getAncestorPar("node_clients"), ",");
    tokenizer = cStringTokenizer("", ",");
    clients = init_clients(tokenizer.asIntVector());

    //Useful for statitics: write out the name of each repository within the network
    for (int i = 0; i < num_clients; i++) {
        sprintf(name, "client-%d", i);
        recordScalar(name, clients[i]);
    }

    //
    //Content initialization
    //
    cout << "Start content initialization..." << endl;
    init_content();
    cout << "Content initialized" << endl;
}

void Ccnr::addToDummyCache(const char *contentName, const int numChunks,
        const int chunkSize) {

    datachunk chunk;
    chunks_entry chunks;

    string name;
    std::stringstream out;

    for (int i = 0; i < (numChunks+1); i++) {
        chunk.pkt_id_ = i;
        chunk.packetSize_ = chunkSize;
        chunk.protocol = PT_DUMMY;

        //out << i;
        name = contentName;
        //name.append("_");

        //name.append(out.str());
        //out.str("");
        chunks.push_back(chunk);

        DB.insert(std::make_pair(name, chunks));
        chunks.clear();
    }

}

void Ccnr::addToCache(const char* contentName, const char* localPath) {

//    unsigned found = localPath.find_last_of(".");
//    std::string extension = str.substr(0,found);

    SenderTrace *file = new SenderTrace();
    file->setFileName(localPath);

    VideoTrafficGenerator* traffic = new VideoTrafficGenerator();
    traffic->setTraceFile(file);
    traffic->init();

    datachunk chunk; //= (videochunk *) malloc(sizeof(videochunk));

    //FIXME: Otimizar essa inserção...
    chunks_entry chunks;
    while (traffic->fillchunk(&chunk)) {
        chunk.protocol = PT_VIDEO;
        chunks.push_back(chunk);

//        fprintf(stderr,"frametype: %d size: %d type: %d id: %d time: %f vsize: %d\n",chunk->frametype_,chunk->packetSize_,
//                                   chunk->packetType_,
//                                   chunk->frame_pkt_id_,chunk->time_, chunks.size());

    }



    DB.insert(std::make_pair(contentName, chunks));

//    DATABASE::iterator db = DB.find(contentName);
//    chunk_entry::iterator dbIt;
//
//    for (dbIt = (db->second).begin(); dbIt != (db->second).end(); dbIt++) {
//        chunk = *dbIt;
//        fprintf(stderr, "type: %d size: %d type: %d id: %d time: %f\n",
//                chunk.frametype_, chunk.packetSize_, chunk.packetType_,
//                chunk.frame_pkt_id_, chunk.time_);
//    }

    //delete traffic;
}

ccnr_response * Ccnr::lookup(CcnPacket *ccnPkt) {

    chunk_t contentName = std::string(ccnPkt->getName());
    Enter_Method("Ccnr::lookup");

    std::string content = Util::removeChunkId(contentName);

    double delay = ccnPkt->getSumDi();
    if (delay > 0) {
        tot_pkt++;
        tot_delay += delay;
    }

    /*
     * Here you're using a hack to remove dup chunks ids.
     * Dup Chunks is used to have a database with zipf distribution of videochunks
     * which are pointing to the same file, thus saving memory usage.
     * e.g /cin/ufpe/movie#3#4 is getting the chunk 4 of zipf 3. Don't matter zipf,
     * value all chunk '4' is pointing for the same video file chunk.
     */
    content = Util::removeChunkId(content);

    unsigned long requestedChunkId = Util::getChunkId(contentName);
    DATABASE::iterator db = DB.find(content);

    if (db != DB.end()) {

        if (Util::isDummyApp(contentName)) {

            datachunk chunk;
            chunk.pkt_id_ = requestedChunkId;
            chunk.packetSize_ = 100;
            chunk.protocol = PT_DUMMY;

            ccnr_response *res = new ccnr_response;
            res->time = 0;
            res->data = &chunk;
            res->size = 100;
            return res;

        } else {

            chunks_entry::iterator dbIt;
        for (dbIt = (db->second).begin(); dbIt != (db->second).end(); dbIt++) {
            /**
             fprintf(stderr, "type: %d size: %d type: %d id: %d time: %f\n",
             (*dbIt).frametype_, (*dbIt).packetSize_, (*dbIt).packetType_,
             (*dbIt).frame_pkt_id_, (*dbIt).time_); **/
            unsigned long pkt_id = (*dbIt).pkt_id_;

            if (pkt_id == requestedChunkId) {

                //Tell to AppLayer how many chunks are left.
                (*dbIt).remain = ((db->second).size() - requestedChunkId) - 1;

                ccnr_response *res = new ccnr_response;
                res->time = (*dbIt).stime_ > 0 ? (*dbIt).stime_ : 0;

                (*dbIt).stime_ = simTime().dbl();
                datachunk *data_chunk = new datachunk();
                memcpy(data_chunk, &(*dbIt), sizeof(datachunk));

                res->data = data_chunk;
                //res->data = &(*dbIt);
                res->size = sizeof(datachunk);

                int p_ = (*dbIt).frametype_;
//
//                switch((*dbIt).frametype_){
//                case 1 :
//                    p_ = 1;
//                    break;
//                case 2 :
//                    p_ = 2;
//                    break;
//                case 3 :
//                    p_ = 4;
//                    break;
//                }

//                ccnPkt->setPriority(p_);

                return res;
            }
        }

        return NULL; //Nothing found
        }
    }

    return NULL; //Nothing found
}


/* 
 * Generate all possible combinations of binary strings of a given length with
 * a given number of bits set.
 */
vector<int> Ccnr::binary_strings(int num_ones, int len) {
    vector<int> bins;
    int ones, bin;
    for (int i = 1; i < (1 << len); i++) {
        bin = i;
        ones = 0;
        //Count the number of ones
        while (bin) {
            ones += bin & 1;
            bin >>= 1;
        }
        //If the ones are equal to the number of repositories this is a good
        //binary number
        if (ones == num_ones)
            bins.push_back(i);
    }
    return bins;

}

//Store information about the content:
void Ccnr::init_content() {
    //As the repositories are represented as a string of bits, the function
    //binary_string is used for generating binary strings of length num_repos
    //with exactly degree ones
    vector<int> repo_strings = binary_strings(degree, num_repos);

    for (int d = 1; d <= cardF; d++) {
        //Reset the information field of a given content
        __info(d)= 0;

        if (F > 1) {
            //Set the file size (distributed like a geometric)
            filesize_t s = geometric( 1.0 / F ) + 1;
            __ssize ( d, s );
        } else
        __ssize( d , 1);

        //Set the repositories
        if (num_repos==1) {
            __srepo ( d , 1 );
        } else {
            repo_t repos = repo_strings[intrand(repo_strings.size())];
            __srepo (d ,repos);
        }

    }

}

/*
 * Initialize the repositories vector. This vector is composed by the
 * repositories specified by the ini file.  In addition some random repositories
 * are added if one wished more repositories than the fixed number specified
 * (see omnet.ini for further comments).
 */
int *Ccnr::init_repos(vector<int> node_repos) {

    if (node_repos.size() > (unsigned) num_repos)
        error("You try to distribute too much repositories.");

    int *repositories = new int[num_repos];

    int i = 0;
    while (node_repos.size()) {
        int r = node_repos[i];
        node_repos.pop_back();
        repositories[i++] = r;
    }

    int new_rep;
    while (i < num_repos) {
        new_rep = intrand(nodes);
        if (find(repositories, repositories + i, new_rep) == repositories + i) {
            repositories[i++] = new_rep;
        }
    }
    return repositories;
}

/*
 * Initialize the clients vector. This vector is composed by the clients
 * specified into the ini file.  In addition, some random clients are added if
 * one wished more repositories than the fixed number specified (see omnet.ini
 * for further comments).
 */
int *Ccnr::init_clients(vector<int> node_clients) {}
//
//    if (node_clients.size() > (unsigned) num_clients)
//        error("You try to distribute too much clients.");
//
//    if (clients != 0)
//        return clients;
//
//    int *clients = new int[num_clients];
//
//    int i = 0;
//    while (node_clients.size()) {
//        int r = node_clients[i];
//        node_clients.pop_back();
//        clients[i++] = r;
//    }
//
//    int new_c;
//    while (i < num_clients) {
//        new_c = intrand(nodes);
//        //NOTE: in this way a client can be attached to a node
//        //where a repository is already attached.
//        if (find(clients, clients + i, new_c) == clients + i)
//            clients[i++] = new_c;
//    }
//    return clients;
//
//}


void Ccnr::finish(){

    if(tot_delay > 0){
        char nome[32];
        sprintf(nome,"tot_mean_delay");
        recordScalar(nome,tot_delay/tot_pkt);
    }
}
