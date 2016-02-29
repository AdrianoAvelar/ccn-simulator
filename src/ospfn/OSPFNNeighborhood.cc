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

#include "OSPFNNeighborhood.h"

OSPFNNeighborhood::OSPFNNeighborhood(std::string routerid) {
    this->routerid = routerid;
}

OSPFNNeighborhood::~OSPFNNeighborhood() {
    clear();
}

void OSPFNNeighborhood::addNeighbor(chunk_t prefixName, int cost) {

//FIXME[EAMA] Is it necessary to check if is it a new insertion or just an update?
//    NeighborMap::iterator it = neighborhood.find(id);
//
//    if (it == neighborhood.end()) {
        //new
        neighbor_info info;
        info.cost = cost;
        neighborhood[prefixName] = info;
//    } else {
//        //update
//        neighbor_info info;
//        info.cost = cost;
//        neighborhood[id] = info;
//    }
}


void OSPFNNeighborhood::clear(){

    neighborhood.clear();
}

void OSPFNNeighborhood::printNeighborhoodTable() {

    cerr << "Neighbor Table (" << routerid  << "):\nNeighbor    |    cost    \n";

    if (neighborhood.size() > 0) {
        NeighborMap::const_iterator it = neighborhood.begin();
        for (; it != neighborhood.end(); it++) {
            cerr << it->first << "\t" << it->second.cost << endl;
        }

    } else {
        cerr << "empty.\n";
    }

}

