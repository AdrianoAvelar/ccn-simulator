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

#ifndef __INET_OSPFnCOMMON_H
#define __INET_OSPFnCOMMON_H

#include <ctype.h>
#include <functional>
#include <stdio.h>
#include <iostream>

#include <omnetpp.h>
#include "ccnsim.h"
using std::cout;
using std::cerr;

#include "MACAddress.h"

namespace OSPFN {

    enum Intervals{
        floodInterval = 5 //Flooding is allowed only after 5s of last flood.
    };
    enum NeighborEventType {
        HELLO_RECEIVED = 0,
        START = 1,
        TWOWAY_RECEIVED = 2,
        NEGOTIATION_DONE = 3,
        EXCHANGE_DONE = 4,
        BAD_LINK_STATE_REQUEST = 5,
        LOADING_DONE = 6,
        IS_ADJACENCY_OK = 7,
        SEQUENCE_NUMBER_MISMATCH = 8,
        ONEWAY_RECEIVED = 9,
        KILL_NEIGHBOR = 10,
        INACTIVITY_TIMER = 11,
        POLL_TIMER = 12,
        LINK_DOWN = 13,
        DD_RETRANSMISSION_TIMER = 14,
        UPDATE_RETRANSMISSION_TIMER = 15,
        REQUEST_RETRANSMISSION_TIMER = 16
    };

    enum NeighborStateType {
        DOWN_STATE = 0,
        ATTEMPT_STATE = 1,
        INIT_STATE = 2,
        TWOWAY_STATE = 4,
        EXCHANGE_START_STATE = 8,
        EXCHANGE_STATE = 16,
        LOADING_STATE = 32,
        FULL_STATE = 64
    };

    enum DatabaseExchangeRelationshipType {
        MASTER = 0, SLAVE = 1
};
}


//#define RouterID string
#define BACKOFF simTime()+ 5.0 + exponential(0.1)

//#define BROADCAST_PREFIX "broadcast"
#define ALL_OSPFN_ROUTERS_MCAST "broadcast"
#define ALL_NEIGHBOR_ROUTERS "all_neighbor"

#include "IPv4Address.h"
#include "L3AddressResolver.h"

// global constants
#define LS_REFRESH_TIME                     1800
#define MIN_LS_INTERVAL                     5
#define MIN_LS_ARRIVAL                      1
#define MAX_AGE                             3600
#define CHECK_AGE                           300
#define MAX_AGE_DIFF                        900
#define LS_INFINITY                         16777215
#define DEFAULT_DESTINATION_ADDRESS         0
#define DEFAULT_DESTINATION_MASK            0
#define INITIAL_SEQUENCE_NUMBER             -2147483647
#define MAX_SEQUENCE_NUMBER                 2147483647

#define VIRTUAL_LINK_TTL                    32
//#define IPV4_HEADER_LENGTH                  60    // use IP_MAX_HEADER_BYTES from IPv4Datagram_m.h
#define IPV4_DATAGRAM_LENGTH                65536
#define OSPF_HEADER_LENGTH                  24
#define OSPF_LSA_HEADER_LENGTH              20
#define OSPF_HELLO_HEADER_LENGTH            20
#define OSPF_DD_HEADER_LENGTH               8
#define OSPF_REQUEST_LENGTH                 12
#define OSPF_ROUTERLSA_HEADER_LENGTH        4
#define OSPF_LINK_HEADER_LENGTH             12
#define OSPF_TOS_LENGTH                     4
#define OSPF_NETWORKLSA_MASK_LENGTH         4
#define OSPF_NETWORKLSA_ADDRESS_LENGTH      4
#define OSPF_SUMMARYLSA_HEADER_LENGTH       8
#define OSPF_ASEXTERNALLSA_HEADER_LENGTH    16
#define OSPF_ASEXTERNALLSA_TOS_INFO_LENGTH  12
#define OSPF_EXTERNAL_ROUTES_LEARNED_BY_BGP 179
#define OSPF_BGP_DEFAULT_COST               1

using namespace inet;

namespace OSPFN {
typedef unsigned long Metric;

enum AuthenticationType {
    NULL_TYPE = 0, SIMPLE_PASSWORD_TYPE = 1, CRYTOGRAPHIC_TYPE = 2
};

struct AuthenticationKeyType {
    char bytes[8];
};

struct IPv4AddressRange {
    IPv4Address address;
    IPv4Address mask;
    IPv4AddressRange() :
            address(), mask() {
    }
    IPv4AddressRange(IPv4Address addressPar, IPv4Address maskPar) :
            address(addressPar), mask(maskPar) {
    }

    bool operator<(const IPv4AddressRange& other) const {
        return ((mask > other.mask)
                || ((mask == other.mask) && (address < other.address)));
    }
    bool operator==(const IPv4AddressRange& other) const {
        return (address == other.address) && (mask == other.mask);
    }
    bool contains(const IPv4Address& other) const {
        return IPv4Address::maskedAddrAreEqual(address, other, mask);
    }
    bool contains(const IPv4AddressRange& other) const {
        return IPv4Address::maskedAddrAreEqual(address, other.address, mask)
                && (mask <= other.mask);
    }
    bool containsRange(const IPv4Address& otherAddress,
            const IPv4Address& otherMask) const {
        return IPv4Address::maskedAddrAreEqual(address, otherAddress, mask)
                && (mask <= otherMask);
    }
    bool containedByRange(const IPv4Address& otherAddress,
            const IPv4Address& otherMask) const {
        return IPv4Address::maskedAddrAreEqual(otherAddress, address, otherMask)
                && (otherMask <= mask);
    }

//    bool operator!=(OSPF::IPv4AddressRange other) const {
//        return (! operator==(other));
//    }
    std::string str() const;
};

inline std::string IPv4AddressRange::str() const {
    std::string str(address.str(false));
    str += "/";
    str += mask.str(false);
    return str;
}

struct HostRouteParameters {
    unsigned char ifIndex;
    IPv4Address address;
    Metric linkCost;
};

typedef IPv4Address RouterID;
typedef IPv4Address AreaID;
typedef IPv4Address LinkStateID;

struct LSAKeyType {
    LinkStateID linkStateID;
    RouterID advertisingRouter;
};

class LSAKeyType_Less: public std::binary_function<LSAKeyType, LSAKeyType, bool> {
public:
    bool operator()(LSAKeyType leftKey, LSAKeyType rightKey) const;
};

struct DesignatedRouterID {
    RouterID routerID;
    IPv4Address ipInterfaceAddress;
};

const RouterID NULL_ROUTERID(0, 0, 0, 0);
const AreaID BACKBONE_AREAID(0, 0, 0, 0);
const LinkStateID NULL_LINKSTATEID(0, 0, 0, 0);
const IPv4Address NULL_IPV4ADDRESS(0, 0, 0, 0);
const IPv4AddressRange NULL_IPV4ADDRESSRANGE(IPv4Address(0, 0, 0, 0),
        IPv4Address(0, 0, 0, 0));
const DesignatedRouterID NULL_DESIGNATEDROUTERID = { IPv4Address(0, 0, 0, 0),
        IPv4Address(0, 0, 0, 0) };

} // namespace OSPF
//
//inline IPv4Address operator&(IPv4Address address, IPv4Address mask)
//{
//    IPv4Address maskedAddress;
//    maskedAddress.set(address.getInt() & mask.getInt());
//    return maskedAddress;
//}
//
//inline IPv4Address operator|(IPv4Address address, IPv4Address match)
//{
//    IPv4Address matchAddress;
//    matchAddress.set(address.getInt() | match.getInt());
//    return matchAddress;
//}
//
//inline bool isSameNetwork(IPv4Address address1, IPv4Address mask1, IPv4Address address2, IPv4Address mask2)
//{
//    return (mask1 == mask2) && ((address1 & mask1) == (address2 & mask2));
//}
//
//inline bool operator==(OSPF::DesignatedRouterID leftID, OSPF::DesignatedRouterID rightID)
//{
//    return (leftID.routerID == rightID.routerID &&
//            leftID.ipInterfaceAddress == rightID.ipInterfaceAddress);
//}
//
//inline bool operator!=(OSPF::DesignatedRouterID leftID, OSPF::DesignatedRouterID rightID)
//{
//    return (!(leftID == rightID));
//}
//
//inline bool OSPF::LSAKeyType_Less::operator() (OSPF::LSAKeyType leftKey, OSPF::LSAKeyType rightKey) const
//{
//    return ((leftKey.linkStateID < rightKey.linkStateID) ||
//            ((leftKey.linkStateID == rightKey.linkStateID) &&
//             (leftKey.advertisingRouter < rightKey.advertisingRouter)));
//}
//
//inline IPv4Address ipv4AddressFromAddressString(const char* charForm)
//{
//    return IPvXAddressResolver().resolve(charForm, IPvXAddressResolver::ADDR_IPv4).get4();
//}
//
//inline IPv4Address ipv4NetmaskFromAddressString(const char* charForm)
//{
//    return IPvXAddressResolver().resolve(charForm, IPvXAddressResolver::ADDR_IPv4|IPvXAddressResolver::ADDR_MASK).get4();
//}
//
//inline char hexCharToByte(char hex)
//{
//    switch (hex) {
//        case '0':   return 0;
//        case '1':   return 1;
//        case '2':   return 2;
//        case '3':   return 3;
//        case '4':   return 4;
//        case '5':   return 5;
//        case '6':   return 6;
//        case '7':   return 7;
//        case '8':   return 8;
//        case '9':   return 9;
//        case 'A':   return 10;
//        case 'B':   return 11;
//        case 'C':   return 12;
//        case 'D':   return 13;
//        case 'E':   return 14;
//        case 'F':   return 15;
//        case 'a':   return 10;
//        case 'b':   return 11;
//        case 'c':   return 12;
//        case 'd':   return 13;
//        case 'e':   return 14;
//        case 'f':   return 15;
//        default:    break;
//    };
//    return 0;
//}
//
//inline char hexPairToByte(char upperHex, char lowerHex)
//{
//    return ((hexCharToByte(upperHex) << 4) & (hexCharToByte(lowerHex)));
//}

#endif // __COMMON_HPP__
