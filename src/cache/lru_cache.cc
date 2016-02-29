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

#include <iostream>
#include "lru_cache.h"
#include "CcnPacket_m.h"
#include "shared.h"
#include "Ccnr.h"

Register_Class (lru_cache);

void lru_cache::data_store(cMessage *msg) {

    CcnPacket *ccnPkt = dynamic_cast<CcnPacket *>(msg);

    if ((!ccnPkt) || (ccnPkt->getKind() != PROT_CCN)) {
        return;
    }

    int size = ccnPkt->getByteArray().getDataArraySize();
    char *data = new char[size];
    int dataLen = ccnPkt->copyDataToBuffer(data, size);

    chunk_t elem = std::string(ccnPkt->getName());

    //When the element is already stored within the cache, simply update the 
    //position of the element within the list and exit

    if (data_lookup(ccnPkt))
        return;

    //lru_pos *p = (lru_pos *) malloc(sizeof(lru_pos)); //position for the new element
    lru_pos *p = new lru_pos;
    p->k = elem;
    p->hit_time = simTime();
    p->data = data;
    p->size = dataLen;
    p->newer = 0;
    p->older = 0;

    //The cache is empty. Add just one element. The mru and lru element are the
    //same
    if (actual_size == 0) {
        actual_size += (double)dataLen/1024; //Bytes to Kbytes
        lru = mru = p;
        cache[elem] = p;
        return;
    }

    //The cache is not empty. The new element is the newest. Add in the front
    //of the list
    p->older = mru; // mru swaps in second position (in terms of utilization rank)
    mru->newer = p; // update the newer element for the secon newest element
    mru = p; //update the mru (which becomes that just inserted)

    if (isfull()) {
        //if the cache is full, delete the last element
        //
        chunk_t k = lru->k;
        lru_pos *tmp = lru;
        lru = tmp->newer; //the new lru is the element before the least recently used

        lru->older = 0; //as it is still in memory for a while set the actual lru point to null (CHECK this)
        tmp->older = 0;
        tmp->newer = 0;

        free(tmp);
        cache.erase(k); //erase from the cache the most unused element
    } else
        //otherwise do nothing, just update the actual_size of the cache
        actual_size += (double)dataLen/1024; //Bytes to Kbytes
    cache[elem] = p; //store the new element together with its position
}

/**
 * Return the data stored in founded entry.
 * If nothing has been found return null.
 * */
cache_response * lru_cache::data_lookup(CcnPacket* ccnPkt) {

    chunk_t elem = std::string(ccnPkt->getName());

    //updating an element is just a matter of manipulating the list
    unordered_map<chunk_t, lru_pos *>::iterator it = cache.find(elem);

    //look for the elements
    if (it == cache.end()) {
        //if not found return false and do nothing
        return NULL;
    }

    lru_pos* pos_elem = it->second;

    //FIXME[EAMA] It's not generic, but it's the only way to get transmition time
    datachunk* vc = dynamic_cast<datachunk*>((datachunk*) pos_elem->data);

    if (vc) {
        ccnPkt->setPriority(vc->frametype_);
        vc->stime_ = simTime().dbl();
    }

    if (pos_elem->older && pos_elem->newer) {
        //if the element is in the middle remove the element from the list
        pos_elem->newer->older = pos_elem->older;
        pos_elem->older->newer = pos_elem->newer;

    } else if (!pos_elem->newer) {

        //if the element is the mru only return.
        cache_response *res = (cache_response *) malloc(sizeof(cache_response));
        res->data = pos_elem->data;
        res->size = pos_elem->size;
        return res;

    } else {
        //if the element is the lru, remove the element from the bottom of the list
        lru = pos_elem->newer;
        lru->older = 0;
    }

    replace++;

    emit(replacementsSignal,replace);
    //replacements.record(replace);

    //Place the elements as in front of the position list (it's the newest one)
    pos_elem->older = mru;
    pos_elem->newer = 0;
    mru->newer = pos_elem;

    //update the mru
    mru = pos_elem;
    mru->hit_time = simTime();

    cache_response *res = (cache_response *) malloc(sizeof(cache_response));

    res->data = pos_elem->data;
    res->size = pos_elem->size;

    return res;
}

void lru_cache::dump() {

//    lru_pos *it = mru;
//    int p = 1;
//    while (it){
//        cout<<p++<<" ]"<< __id(it->k)<<"/"<<__chunk(it->k)<<endl;
//        it = it->older;
//    }
}

bool lru_cache::isfull() {
    return (actual_size >= get_size());
}

