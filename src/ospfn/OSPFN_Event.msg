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

cplusplus {{
#include "MACAddress.h"
using namespace inet;
}}

class noncobject MACAddress;

enum EventType {

	SEND_HELLO_PACKET = 1;
	FLOOD_HELLO_PACKET = 2;
	SEND_LSA = 3;
	    
}


packet OSPFN_Event {
    char eventType enum(EventType) = SEND_HELLO_PACKET;
}


packet OSPFN_Event_Hello extends OSPFN_Event {
    
    MACAddress destination;
}


