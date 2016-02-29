//
// Copyright (C) 2006 Andras Babos and Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#ifndef __INET_OSPFNEIGHBORSTATEDOWN_H
#define __INET_OSPFNEIGHBORSTATEDOWN_H

#include "OSPFNNeighborState.h"

namespace OSPFN {

class NeighborStateDown : public NeighborState
{
public:
    virtual void processEvent(Neighbor* neighbor, OSPFN::NeighborEventType event);
    virtual OSPFN::NeighborStateType getState() const { return OSPFN::DOWN_STATE; }
};

} // namespace OSPF

#endif // __INET_OSPFNEIGHBORSTATEDOWN_H

