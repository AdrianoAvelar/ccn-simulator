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

#ifndef ICCNAPP_H_
#define ICCNAPP_H_

#include "Ccn.h"


enum CCNAppTypes{
    CCN_DUMMY_APP = 100,
    CCN_VIDEO_APP = 200,
    CCN_OSPFN_APP = 89,
    CCN_CCNFLOW_APP = 88,
    CCN_MOBILITY_AGENT = 101

};



class ICcnApp {
public:

    virtual void registerMyselfInCcnLayer() = 0;
};

#endif /* ICCNAPP_H_ */
