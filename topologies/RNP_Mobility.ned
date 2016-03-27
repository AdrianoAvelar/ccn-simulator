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
import ccnpp.CcnAdmin;
import ned.DatarateChannel;

import ccnpp.compounds.node.StandardCCNHost;

import ccnpp.CcnAdmin;
import ned.DatarateChannel;
import inet.common.misc.ThruputMeteringChannel;


//Inet
import inet.networklayer.configurator.ipv4.IPv4NetworkConfigurator;
import inet.node.wireless.AccessPoint;
import inet.physicallayer.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.common.misc.ThruputMeteringChannel;

//ccn
import ccnpp.CcnAdmin;
import ccnpp.compounds.mobility.WirelessCCNHost;
import ccnpp.compounds.node.StandardCCNHost;

//Mapa WiFi http://mapawifi.com.br/cidade/S%C3%A3o%20Paulo

network RNP_IPE_MOBILITY
{
    parameters:
        @display("bgb=1223,1094;bgl=4");

        int defaultDebugLevel = default(3);		// 0=none, 1=Info, 2=Warning, 3=Error, 4=Detail
        bool auxDebug = default(false);			// enable console output for debugging
        double linkDataRate @unit(Gbps) = default(1Gbps);
        double linkLeftDelay @unit(ms) = default(20ms);
        double linkRightDelay @unit(ms) = default(7ms);
        double linkdelay @unit(ms) = default(10ms);
        double linkBer = default(1e-2);

    types:
        //uniformized:
        // 10 Gbs = 1
        // 3 Gbs  = 0.3
        // 1 Gbs  = 0.1
        // 100Mbs = 0.01
        // 68Mbs  = 0.0068
        // 40Mbs  = 0.0040
        channel _10Gbps extends ThruputMeteringChannel
        {
            delay = linkdelay;//uniform(linkLeftDelay,linkRightDelay);
            datarate = linkDataRate;
            ber = linkBer;
            //thruputDisplayFormat = "#u";
            @display("ls=#F20000,3");
        }

        channel _3Gbps extends ThruputMeteringChannel
        {
            delay = linkdelay;//uniform(linkLeftDelay,linkRightDelay);
            datarate = linkDataRate/10;
            //datarate = linkDataRate;
            ber = linkBer;
            //thruputDisplayFormat = "#u";
            @display("ls=dodgerBlue,2");
        }

        channel _1Gbs extends ThruputMeteringChannel
        {
            delay = linkdelay;//uniform(linkLeftDelay,linkRightDelay);
            datarate = linkDataRate/10;
            ber = linkBer;
            //thruputDisplayFormat = "#u";
            @display("ls=orange,2");
        }

        channel apNodeConection extends ThruputMeteringChannel
        {
            delay = linkdelay;//uniform(linkLeftDelay*2,linkRightDelay);
            datarate = 100 Mbps;
            ber = linkBer;
            //thruputDisplayFormat = "#u";
            @display("ls=#208E1E");
        }

        channel _100Mbps extends ThruputMeteringChannel
        {
            delay = linkdelay;//uniform(linkLeftDelay*2,linkRightDelay);
            datarate = linkDataRate/100;
            ber = linkBer;
            //thruputDisplayFormat = "#u";
            @display("ls=#208E1E");
        }

        channel _40Mbps extends ThruputMeteringChannel
        {
            delay = linkdelay;//uniform(linkLeftDelay*10,linkRightDelay);
            datarate = linkDataRate/1000;
            ber = linkBer;
            //thruputDisplayFormat = "#u";
            @display("ls=#DADA37");
        }

        channel _68Mbs extends ThruputMeteringChannel
        {
            delay = linkdelay;//uniform(linkLeftDelay*4,linkRightDelay);
            //datarate = 68Mbps;
            datarate = linkDataRate/100;
            ber = linkBer;
            //thruputDisplayFormat = "#u";
            @display("ls=lightGreen");
        }

    submodules:

        poa1: AccessPoint {
            @display("p=337,622;r=,,#707070");
            gates:
                ethg[1];
        }

        poa2: AccessPoint {
            @display("p=168,622;r=,,#707070");
            gates:
                ethg[1];
        }
        poa3: AccessPoint {
            @display("r=,,#707070;p=195,811");
            gates:
                ethg[1];
        }
        poa4: AccessPoint {
            @display("p=458,832;r=,,#707070");
            gates:
                ethg[1];
        }
        poa5: AccessPoint {
            @display("p=927,708;r=,,#707070");
            gates:
                ethg[1];
        }
        poa6: AccessPoint {
            @display("p=793,787;r=,,#707070");
            gates:
                ethg[1];
        }
        poa7: AccessPoint {
            @display("p=969,296;r=,,#707070");
            gates:
                ethg[1];
        }
        poa8: AccessPoint {
            @display("p=931,537;r=,,#707070");
            gates:
                ethg[1];
        }
        poa9: AccessPoint {
            @display("p=678,466;r=,,#707070");
            gates:
                ethg[1];
        }
        poa10: AccessPoint {
            @display("p=531,395;r=,,#707070");
            gates:
                ethg[1];
        }
        poa11: AccessPoint {
            @display("p=205,216;r=,,#707070");
            gates:
                ethg[1];
        }
        poa12: AccessPoint {
            @display("p=404,429;r=,,#707070");
            gates:
                ethg[1];
        }
        poa13: AccessPoint {
            @display("p=916,406;r=,,#707070");
            gates:
                ethg[1];
        }
        poa14: AccessPoint {
            @display("p=857,165;r=,,#707070");
            gates:
                ethg[1];
        }
        poa15: AccessPoint {
            @display("p=722,140;r=,,#707070");
            gates:
                ethg[1];
        }
        poa16: AccessPoint {
            @display("p=452,311;r=,,#707070");
            gates:
                ethg[1];
        }
        poa17: AccessPoint {
            @display("p=612,135;r=,,#707070");
            gates:
                ethg[1];
        }

        poa18: AccessPoint {
            @display("p=404,140;r=,,#707070");
            gates:
                ethg[1];
        }

        poa19: AccessPoint {
            @display("p=260,500;r=,,#707070");
            gates:
                ethg[1];
        }

        poa20: AccessPoint {
            @display("p=142,348;r=,,#707070");
            gates:
                ethg[1];
        }

        poa21: AccessPoint {
            @display("p=624,800;r=,,#707070");
            gates:
                ethg[1];
        }

        poa22: AccessPoint {
            @display("p=443,663;r=,,#707070");
            gates:
                ethg[1];
        }

        poa23: AccessPoint {
            @display("p=667,541;r=,,#707070");
            gates:
                ethg[1];
        }

        admin: CcnAdmin {
            @display("p=37,41;b=,,rect,#170909");
        }

        RR: StandardCCNHost {
            @display("p=377,216;is=vs");
            gates:
                ethg[3];
        }
        AM: StandardCCNHost {
            @display("p=310,301;is=vs");
            gates:
                ethg[3];
        }
        AP: StandardCCNHost {
            @display("p=512,218;is=vs");
            gates:
                ethg[2];
        }
        PA: StandardCCNHost {
            @display("p=531,266;is=vs");
            gates:
                ethg[4];
        }
        MA: StandardCCNHost {
            @display("p=639,227;is=vs");
            gates:
                ethg[3];
        }
        CE: StandardCCNHost {
            @display("p=661,332;is=vs");
            gates:
                ethg[5];
        }
        PB2: StandardCCNHost {
            @display("p=847,310;is=vs");
            gates:
                ethg[3];
        }
        RN: StandardCCNHost {
            @display("p=770,227;is=vs");
            gates:
                ethg[3];
        }
        PB: StandardCCNHost {
            @display("p=823,375;is=vs");
            gates:
                ethg[2];
        }

        PI: StandardCCNHost {
            @display("p=573,347;is=vs");
            gates:
                ethg[3];
        }
        PE: StandardCCNHost {
            @display("p=734,419;is=vs");
            gates:
                ethg[4];
        }
        AL: StandardCCNHost {
            @display("p=800,436;is=vs");
            gates:
                ethg[3];
        }
        SE: StandardCCNHost {
            @display("p=815,527;is=vs");
            gates:
                ethg[3];
        }
        BA: StandardCCNHost {
            @display("p=742,706;is=vs");
            gates:
                ethg[4];
        }
        TO: StandardCCNHost {
            @display("p=404,622;is=vs");
            gates:
                ethg[2];
        }
        AC: StandardCCNHost {
            @display("p=223,385;is=vs");
            gates:
                ethg[2];
        }
        RO: StandardCCNHost {
            @display("p=337,436;is=vs");
            gates:
                ethg[3];
        }
        MT: StandardCCNHost {
            @display("p=392,500;is=vs");
            gates:
                ethg[3];
        }
        GO: StandardCCNHost {
            @display("p=458,597;is=vs");
            gates:
                ethg[4];
        }
        BH: StandardCCNHost {
            @display("p=531,489;is=vs");
            gates:
                ethg[6];
        }
        MG: StandardCCNHost {
            @display("p=555,607;is=vs");
            gates:
                ethg[5];
        }
        ES: StandardCCNHost {
            @display("p=818,640;is=vs");
            gates:
                ethg[3];
        }
        SP: StandardCCNHost {
            @display("p=624,730;is=vs");
            gates:
                ethg[5];
        }
        MS: StandardCCNHost {
            @display("p=263,586;is=vs");
            gates:
                ethg[3];
        }
        PR: StandardCCNHost {
            @display("p=310,690;is=vs");
            gates:
                ethg[3];
        }
        RJ: StandardCCNHost {
            @display("p=690,597;is=vs");
            gates:
                ethg[3];
        }
        SC: StandardCCNHost {
            @display("p=407,778;is=vs");
            gates:
                ethg[3];
        }
        RS: StandardCCNHost {
            @display("p=223,748;is=vs");
            gates:
                ethg[3];
        }

        radioMedium: Ieee80211ScalarRadioMedium {
            @display("p=46,176;is=s");
        }

        configurator: IPv4NetworkConfigurator {
            @display("p=37,109;is=s");
        }


        provider_host02: WirelessCCNHost {
            @display("r=,,#707070;p=187,133;is=l");
        }

        host01: WirelessCCNHost {
            @display("r=,,#707070;p=98,250;is=l");
        }

//        host03: WirelessCCNHost {
//            @display("r=,,#707070;p=1003,214;is=l");
//        }
//
//        host04: WirelessCCNHost {
//            @display("r=,,#707070;p=85,725;is=l");
//        }
//
//        host05: WirelessCCNHost {
//            @display("r=,,#707070;p=456,70;is=l");
//        }
//
//        host06: WirelessCCNHost {
//            @display("r=,,#707070;p=377,927;is=l");
//        }
//
//        host07: WirelessCCNHost {
//            @display("r=,,#707070;p=806,863;is=l");
//        }
//
//        host08: WirelessCCNHost {
//            @display("r=,,#707070;p=917,619;is=l");
//        }
//
//        host09: WirelessCCNHost {
//            @display("r=,,#707070;p=522,662;is=l");
//        }

    connections allowunconnected:



        SP.ethg[0] <--> _10Gbps <--> SC.ethg[1];
        PR.ethg[0] <--> _10Gbps <--> SP.ethg[3];
        RS.ethg[0] <--> _10Gbps <--> PR.ethg[1];
        SC.ethg[0] <--> _10Gbps <--> RS.ethg[1];
        RJ.ethg[0] <--> _10Gbps <--> SP.ethg[1];
        ES.ethg[0] <--> _10Gbps <--> RJ.ethg[1];
        SP.ethg[2] <--> _10Gbps <--> MG.ethg[3];
        BA.ethg[1] <--> _10Gbps <--> ES.ethg[1];
        SE.ethg[1] <--> _10Gbps <--> BA.ethg[2];
        AL.ethg[0] <--> _10Gbps <--> SE.ethg[0];
        PE.ethg[1] <--> _10Gbps <--> AL.ethg[1];
        PB.ethg[1] <--> _10Gbps <--> PE.ethg[2];
        BH.ethg[1] <--> _10Gbps <--> RJ.ethg[2];
        BH.ethg[0] <--> _10Gbps <--> MG.ethg[0];
        MG.ethg[1] <--> _10Gbps <--> BA.ethg[0];
        MG.ethg[2] <--> _10Gbps <--> CE.ethg[2];
        GO.ethg[2] <--> _10Gbps <--> BH.ethg[2];
        CE.ethg[3] <--> _10Gbps <--> BH.ethg[3];
        RN.ethg[1] <--> _10Gbps <--> CE.ethg[4];
        MS.ethg[1] <--> _3Gbps <--> PR.ethg[2];
        MT.ethg[0] <--> _3Gbps <--> MS.ethg[0];
        MT.ethg[1] <--> _3Gbps <--> GO.ethg[1];
        TO.ethg[0] <--> _3Gbps <--> GO.ethg[0];
        RO.ethg[1] <--> _3Gbps <--> MT.ethg[2];
        AC.ethg[0] <--> _3Gbps <--> RO.ethg[0];
        PA.ethg[1] <--> _3Gbps <--> MA.ethg[0];
        PA.ethg[0] <--> _3Gbps <--> PI.ethg[0];
        AM.ethg[0] <--> _1Gbs <--> BH.ethg[4];
        RR.ethg[0] <--> _100Mbps <--> AM.ethg[1];
        AP.ethg[0] <--> _68Mbs <--> PA.ethg[2];
        //   RR.ethg[1] <--> _40Mbps <--> CE.ethg[1];
        PE.ethg[0] <--> _3Gbps <--> PI.ethg[1];
        PB2.ethg[0] <--> _10Gbps <--> PB.ethg[0];
        PB2.ethg[1] <--> _10Gbps <--> RN.ethg[0];
        MA.ethg[1] <--> _3Gbps <--> CE.ethg[0];


        poa20.ethg[0] <--> apNodeConection <--> AC.ethg[1];
        poa12.ethg[0] <--> apNodeConection <--> BH.ethg[5];
        poa16.ethg[0] <--> apNodeConection <--> PA.ethg[3];
        poa18.ethg[0] <--> apNodeConection <--> RR.ethg[2];
        poa17.ethg[0] <--> apNodeConection <--> AP.ethg[1];
        poa11.ethg[0] <--> apNodeConection <--> AM.ethg[2];
        poa15.ethg[0] <--> apNodeConection <--> MA.ethg[2];
        poa10.ethg[0] <--> apNodeConection <--> PI.ethg[2];
        poa9.ethg[0] <--> apNodeConection <--> PE.ethg[3];
        poa14.ethg[0] <--> apNodeConection <--> RN.ethg[2];
        poa7.ethg[0] <--> apNodeConection <--> PB2.ethg[2];
        poa6.ethg[0] <--> apNodeConection <--> BA.ethg[3];
        poa5.ethg[0] <--> apNodeConection <--> ES.ethg[2];
        poa2.ethg[0] <--> apNodeConection <--> MS.ethg[2];
        poa3.ethg[0] <--> apNodeConection <--> RS.ethg[2];
        poa4.ethg[0] <--> apNodeConection <--> SC.ethg[2];
        poa1.ethg[0] <--> apNodeConection <--> TO.ethg[1];
        poa23.ethg[0] <--> apNodeConection <--> MG.ethg[4];
        poa22.ethg[0] <--> apNodeConection <--> GO.ethg[3];
        poa13.ethg[0] <--> apNodeConection <--> AL.ethg[2];
        poa8.ethg[0] <--> apNodeConection <--> SE.ethg[2];
        poa21.ethg[0] <--> apNodeConection <--> SP.ethg[4];
        poa19.ethg[0] <--> apNodeConection <--> RO.ethg[2];
}
