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

#ifndef __OSPFN_IMESSAGEHANDLER_H
#define __OSPFN_IMESSAGEHANDLER_H

#include "OSPFNPacket_m.h"

namespace OSPFN {

class Router;

class IMessageHandler
{
protected:
    Router* router;

public:
    IMessageHandler(Router* containingRouter)  { router = containingRouter; }
    virtual ~IMessageHandler() {}

    //virtual void processPacket(OSPFPacket*, Interface* intf, Neighbor* neighbor) = 0;
    virtual void processPacket(OSPFNPacket*) = 0;//,Interface* intf , OSPFN::Neighbor* neighbor) = 0;
};

} // namespace OSPF

#endif // __INET_IMESSAGEHANDLER_H
