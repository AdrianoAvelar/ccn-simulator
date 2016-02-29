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

package ccnpp.topologies;

//Inet
import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.node.wireless.AccessPoint;
import inet.physicallayer.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.common.misc.ThruputMeteringChannel;

//ccn
import ccnpp.CcnAdmin;
import ccnpp.compounds.mobility.WirelessCCNHost;
import ccnpp.compounds.node.StandardCCNHost;

network ProviderMobility
{
    parameters:
        @display("bgb=791,663;bgl=2");


        double linkDataRate @unit(Mbps) = default(100Mbps);
        double linkLeftDelay @unit(ms) = default(20ms);
        double linkRightDelay @unit(ms) = default(7ms);
        double linkdelay @unit(ms) = default(10ms);

        double linkBer = default(1e-2);
    types:

        channel _100Mbps extends ThruputMeteringChannel
        {
            delay = linkdelay;//uniform(linkLeftDelay*2,linkRightDelay);
            datarate = linkDataRate;
            ber = linkBer;
            //thruputDisplayFormat = "#u";
            @display("ls=#208E1E");
        }

    submodules:

        admin: CcnAdmin {
            @display("b=5,5,rect;p=747,143;i=abstract/person;is=s");
        }

        host01: WirelessCCNHost {
            @display("p=50,116;r=,,#707070");
        }

        host02: WirelessCCNHost {
            @display("p=68,589;r=,,#707070");
        }

        router01: StandardCCNHost {
            @display("p=273,280;r=,,#707070");
            gates:
                ethg[4];
        }

        router02: StandardCCNHost {
            @display("p=507,280;r=,,#707070");
            gates:
                ethg[4];
        }


        router03: StandardCCNHost {
            @display("p=507,409;r=,,#707070");
            gates:
                ethg[4];
        }

        router04: StandardCCNHost {
            @display("p=273,409;r=,,#707070");
            gates:
                ethg[4];
        }

        poa1: AccessPoint {
            @display("p=178,204;r=,,#707070");
            gates:
                ethg[1];
        }

        poa2: AccessPoint {
            @display("p=614,198;r=,,#707070");
            gates:
                ethg[1];
        }

        poa3: AccessPoint {
            @display("p=620,485;r=,,#707070");
            gates:
                ethg[1];
        }

        poa4: AccessPoint {
            @display("p=190,469;r=,,#707070");
            gates:
                ethg[1];
        }

        radioMedium: Ieee80211ScalarRadioMedium {
            @display("p=746,78;is=s");
        }

        configurator: IPv4NetworkConfigurator {
            @display("p=747,25;is=s");
        }


    connections allowunconnected:

        poa1.ethg[0] <--> _100Mbps <--> router01.ethg[0];
        poa2.ethg[0] <--> _100Mbps <--> router02.ethg[0];

        router01.ethg[1] <--> _100Mbps <--> router03.ethg[0];
        router01.ethg[2] <--> _100Mbps <--> router02.ethg[2];

        router01.ethg[3] <--> _100Mbps <--> router04.ethg[0];
        router02.ethg[1] <--> _100Mbps <--> router03.ethg[1];

        router04.ethg[1] <--> _100Mbps <--> router02.ethg[3];
        router04.ethg[2] <--> _100Mbps <--> router03.ethg[2];

        router03.ethg[3] <--> _100Mbps <--> poa3.ethg[0];
        router04.ethg[3] <--> _100Mbps <--> poa4.ethg[0];

}
