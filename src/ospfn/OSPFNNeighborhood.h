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

#ifndef OSPFNNEIGHBORHOOD_H_
#define OSPFNNEIGHBORHOOD_H_

#include "OSPFNcommon.h"


struct s_neighbor_info{
    //interface de saida ???
    int cost;
};

typedef s_neighbor_info neighbor_info;
typedef std::map<std::string, neighbor_info> NeighborMap;

class OSPFNNeighborhood {

public:

    OSPFNNeighborhood(std::string routerid);
    virtual ~OSPFNNeighborhood();

    void addNeighbor(chunk_t prefixName, int cost);
    void printNeighborhoodTable();
    void clear();

    NeighborMap getNeighborTable(){
        return neighborhood;
    }


    inline int getSize(){return neighborhood.size();};
    inline bool isEmpty(){ return neighborhood.size() > 0 ? true : false;};

private:

    std::string routerid;
    NeighborMap neighborhood;
};

#endif /* OSPFNNEIGHBORHOOD_H_ */
