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

import ccnpp.compounds.node.StandardCCNHost;
import ccnpp.CcnAdmin;
import ned.DatarateChannel;
import inet.common.misc.ThruputMeteringChannel;

network RNP_IPE_DELAY_ICN
{
    parameters:
        @display("bgb=568,520;bgi=maps/RNP_IPE");

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

        channel _100Mbps extends ThruputMeteringChannel
        {
            delay = linkdelay;//uniform(linkLeftDelay*2,linkRightDelay);
            datarate = linkDataRate/100;
            ber = linkBer;
            //thruputDisplayFormat = "#u";
            @display("ls=#208E1E");
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

        channel _40Mbps extends ThruputMeteringChannel
        {
            delay = linkdelay;//uniform(linkLeftDelay*10,linkRightDelay);
            datarate = linkDataRate/1000;
            ber = linkBer;
            //thruputDisplayFormat = "#u";
            @display("ls=#DADA37");
        }

    submodules:

        admin: CcnAdmin {
            @display("p=31,55;b=,,rect,#170909");
        }

        RR: StandardCCNHost {
            @display("p=184,48;is=vs");
            gates:
                ethg[2];
        }
        AM: StandardCCNHost {
            @display("p=163,125;is=vs");
            gates:
                ethg[2];
        }
        AP: StandardCCNHost {
            @display("p=311,48;is=vs");
            gates:
                ethg[1];
        }
        PA: StandardCCNHost {
            @display("p=357,88;is=vs");
            gates:
                ethg[3];
        }
        MA: StandardCCNHost {
            @display("p=419,114;is=vs");
            gates:
                ethg[2];
        }
        CE: StandardCCNHost {
            @display("p=473,136;is=vs");
            gates:
                ethg[5];
        }
        PB2: StandardCCNHost {
            @display("p=495,168;is=vs");
            gates:
                ethg[2];
        }
        RN: StandardCCNHost {
            @display("p=525,147;is=vs");
            gates:
                ethg[2];
        }
        PB: StandardCCNHost {
            @display("p=540,168;is=vs");
            gates:
                ethg[2];
        }

        PI: StandardCCNHost {
            @display("p=424,168;is=vs");
            gates:
                ethg[2];
        }
        PE: StandardCCNHost {
            @display("p=533,197;is=vs");
            gates:
                ethg[3];
        }
        AL: StandardCCNHost {
            @display("p=510,208;is=vs");
            gates:
                ethg[2];
        }
        SE: StandardCCNHost {
            @display("p=495,225;is=vs");
            gates:
                ethg[2];
        }
        BA: StandardCCNHost {
            @display("p=465,242;is=vs");
            gates:
                ethg[3];
        }
        TO: StandardCCNHost {
            @display("p=357,208;is=vs");
            gates:
                ethg[1];
        }
        AC: StandardCCNHost {
            @display("p=76,208;is=vs");
            gates:
                ethg[1];
        }
        RO: StandardCCNHost {
            @display("p=163,225;is=vs");
            gates:
                ethg[2];
        }
        MT: StandardCCNHost {
            @display("p=263,242;is=vs");
            gates:
                ethg[3];
        }
        GO: StandardCCNHost {
            @display("p=311,316;is=vs");
            gates:
                ethg[3];
        }
        BH: StandardCCNHost {
            @display("p=357,297;is=vs");
            gates:
                ethg[5];
        }
        MG: StandardCCNHost {
            @display("p=419,316;is=vs");
            gates:
                ethg[4];
        }
        ES: StandardCCNHost {
            @display("p=465,336;is=vs");
            gates:
                ethg[2];
        }
        SP: StandardCCNHost {
            @display("p=372,400;is=vs");
            gates:
                ethg[4];
        }
        MS: StandardCCNHost {
            @display("p=248,351;is=vs");
            gates:
                ethg[2];
        }
        PR: StandardCCNHost {
            @display("p=311,411;is=vs");
            gates:
                ethg[3];
        }
        RJ: StandardCCNHost {
            @display("p=439,383;is=vs");
            gates:
                ethg[3];
        }
        SC: StandardCCNHost {
            @display("p=341,455;is=vs");
            gates:
                ethg[2];
        }
        RS: StandardCCNHost {
            @display("p=278,490;is=vs");
            gates:
                ethg[2];
        }

    connections:


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
        RR.ethg[1] <--> _40Mbps <--> CE.ethg[1];
        PE.ethg[0] <--> _3Gbps <--> PI.ethg[1];
        PB2.ethg[0] <--> _10Gbps <--> PB.ethg[0];
        PB2.ethg[1] <--> _10Gbps <--> RN.ethg[0];
        MA.ethg[1] <--> _3Gbps <--> CE.ethg[0];
}
