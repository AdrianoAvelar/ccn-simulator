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

package ccnpp.compounds.node;

import ccnpp.compounds.node.ccnx;
import ccnpp.Ccn;


module icn
{
    parameters:
        
        string interfaceTableModule;
        *.interfaceTableModule = default(interfaceTableModule);
        
        string forwardingTableModule;
		*.forwardingTableModule = default(forwardingTableModule);
        
    @display("bgl=5;bgb=241,195");
    gates:
        input upperIn[] @labels(CcnAppMessage);
        output upperOut[] @labels(CcnAppMessage);

        input ifIn[];
        output ifOut[];
        
        input ospfnIn @labels(ospnf);
        output ospfnOut @labels(ospnf);
        
    submodules:

        ccnx: ccnx {
            @display("p=190,37");

        }

        // --- Network Layer
        ccnd: Ccn {
            @display("p=47,97;i=block/broadcast");

            gates:
                upperIn[sizeof(upperIn)];
                upperOut[sizeof(upperOut)];

                ifOut[sizeof(ifOut)];
                ifIn[sizeof(ifIn)];
        }

    connections allowunconnected:

        ccnx.ccnd_port <--> { @display("ls=#038087,3,d"); } <--> ccnd.ccn_core;

		ospfnIn --> ccnd.ospfnIn;
		ccnd.ospfnOut --> ospfnOut;

        for i=0..sizeof(ifOut)-1 {
            ccnd.ifOut[i] --> { @display("m=s"); } --> ifOut[i];
        }
        for i=0..sizeof(ifIn)-1 {
            ccnd.ifIn[i] <-- { @display("m=s"); } <-- ifIn[i];
        }

        for i=0..sizeof(upperIn)-1 {
            ccnd.upperIn[i] <-- { @display("m=n"); } <-- upperIn[i];

        }
        for i=0..sizeof(upperOut)-1 {
            ccnd.upperOut[i] --> { @display("m=n"); } --> upperOut[i];
        }

}
