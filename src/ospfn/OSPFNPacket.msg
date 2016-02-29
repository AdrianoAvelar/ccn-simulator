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

cplusplus {{
#include "IPv4Address.h"
#include "MACAddress.h"
using namespace inet;
}}


class noncobject IPv4Address;
class noncobject MACAddress;


enum OSPFNPacketType
{
    OSPFN_HELLO_PACKET = 1;
    OSPFN_DATABASE_DESCRIPTION_PACKET = 2;
    OSPFN_LINKSTATE_REQUEST_PACKET = 3;
    OSPFN_LINKSTATE_UPDATE_PACKET = 4;
    OSPFN_LINKSTATE_ACKNOWLEDGEMENT_PACKET = 5;
}

// should be a byte long bitfield
struct OSPFNOptions
{
    bool unused_1;
    bool E_ExternalRoutingCapability;
    bool MC_MulticastForwarding;
    bool NP_Type7LSA;
    bool EA_ForwardExternalLSAs;
    bool DC_DemandCircuits;
    bool unused_2;
    bool unused_3;
}

//
// Represents an OSPFN packet header
//
packet OSPFNPacket
{
    char version = 2;
    char type enum(OSPFNPacketType);
    string routerID;
    string destination;

    //MACAddress areaID;

    //short authenticationType = 0;
    //char authentication[8];
}

//
// Represents an OSPFN Hello packet
//
packet OSPFNHelloPacket extends OSPFNPacket
{
    string contentName;
    short helloInterval = 5;
	type = OSPFN_HELLO_PACKET; //6.2.10 Assignment of Inherited Fields
 //   OSPFNOptions options;

    char routerPriority = 0;
    long routerDeadInterval = 0;

	
    MACAddress designatedRouter;
    MACAddress backupDesignatedRouter;
    MACAddress neighbor[];
}

//
enum OSPFNLSAType
{
    OFPSN_ROUTERLSA_TYPE = 1;
    OFPSN_NETWORKLSA_TYPE = 2;
    OFPSN_SUMMARYLSA_NETWORKS_TYPE = 3;
    OFPSN_SUMMARYLSA_ASBOUNDARYROUTERS_TYPE = 4;
    OFPSN_AS_EXTERNAL_LSA_TYPE = 5;
}
//
////
//// Represents an OSPFN LSA header
////
class OSPFNLSAHeader
{
    unsigned short lsAge = 0;
    OSPFNOptions lsOptions;
    char lsType enum(OSPFNLSAType) = OFPSN_ROUTERLSA_TYPE;
    IPv4Address linkStateID;
    IPv4Address advertisingRouter;
    long lsSequenceNumber = 0;
    unsigned short lsaLength = 0;
}
//
////
//// common ancestor type for all LSAs
////
//class OSPFNLSA
//{
//    OSPFNLSAHeader header;
//}
//
//enum LinkType
//{
//    POINTTOPOINT_LINK = 1;
//    TRANSIT_LINK = 2;
//    STUB_LINK = 3;
//    VIRTUAL_LINK = 4;
//}
//
//struct TOSData
//{
//    unsigned char tos;
//    unsigned char tosMetric[3];
//}
//
//class Link
//{
//    IPv4Address linkID;
//    unsigned long linkData = 0;
//    unsigned char type enum(LinkType) = POINTTOPOINT_LINK;
//    unsigned char numberOfTOS = 0;
//    unsigned long linkCost = 1;
//    TOSData tosData[];
//}
//
////
//// Represents an OSPFN Router LSA
////
//class OSPFNRouterLSA extends OSPFNLSA
//{
//    bool V_VirtualLinkEndpoint = false;
//    bool E_ASBoundaryRouter = false;
//    bool B_AreaBorderRouter = false;
//    unsigned short numberOfLinks = 0;
//    Link links[];
//}
//
////
//// Represents an OSPFN Network LSA
////
//class OSPFNNetworkLSA extends OSPFNLSA
//{
//    IPv4Address networkMask;
//    IPv4Address attachedRouters[];
//}
//
////
//// Represents an OSPFN Summary LSA
////
//class OSPFNSummaryLSA extends OSPFNLSA
//{
//    IPv4Address networkMask;
//    unsigned long routeCost = 1;
//    TOSData tosData[];
//}
//
//struct ExternalTOSInfo
//{
//    TOSData tosData;
//    bool E_ExternalMetricType;
//    IPv4Address forwardingAddress;
//    long externalRouteTag;
//}
//
////
//// Represents the contents of an OSPFN AS External LSA
////
//class OSPFNASExternalLSAContents
//{
//    IPv4Address networkMask;
//    bool E_ExternalMetricType = false;
//    unsigned long routeCost = 1;
//    IPv4Address forwardingAddress;
//    long externalRouteTag = 0;
//    ExternalTOSInfo externalTOSInfo[];
//}
//
////
//// Represents an OSPFN AS External LSA
////
//class OSPFNASExternalLSA extends OSPFNLSA
//{
//    OSPFNASExternalLSAContents contents;
//}
//
//
//// should be a byte long bitfield
struct OSPFNDDOptions
{
    bool unused_1;
    bool unused_2;
    bool unused_3;
    bool unused_4;
    bool unused_5;
    bool I_Init;
    bool M_More;
    bool MS_MasterSlave;
}
//
////
//// Represents an OSPFN Database Description packet
////
packet OSPFNDatabaseDescriptionPacket extends OSPFNPacket
{
    unsigned short interfaceMTU;
    type = OSPFN_DATABASE_DESCRIPTION_PACKET;
    OSPFNOptions options;
    OSPFNDDOptions ddOptions;
    unsigned long ddSequenceNumber;
    //OSPFNLSAHeader lsaHeaders[];
    string lsaHeaders[];
    
}
//
struct OSPFNLSARequest
{
    unsigned long lsType;
    IPv4Address linkStateID;
    IPv4Address advertisingRouter;
}
//
////
//// Represents an OSPFN Link State Request packet
////
packet OSPFNLinkStateRequestPacket extends OSPFNPacket
{
    OSPFNLSARequest requests[];
    string LSAs[];
  //  int hops[];
}
//
////
//// Represents an OSPFN Link State Update packet
////
//packet OSPFNLinkStateUpdatePacket extends OSPFNPacket
//{
//    unsigned long numberOfLSAs;
//    OSPFNRouterLSA routerLSAs[];
//    OSPFNNetworkLSA networkLSAs[];
//    OSPFNSummaryLSA summaryLSAs[];
//    OSPFNASExternalLSA asExternalLSAs[];
//}
//
////
//// Represents an OSPFN Link State Acknowledgement packet
////
packet OSPFNLinkStateAcknowledgementPacket extends OSPFNPacket
{
    string LSAs[];
    int hops[];
}
