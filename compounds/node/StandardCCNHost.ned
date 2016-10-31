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

import ccnpp.compounds.ospfn.OSPFNRouting;
import ccnpp.compounds.node.CCNNodeBase;
import ccnpp.compounds.applayer.CcnMobilityAgent;

module StandardCCNHost extends CCNNodeBase
{
    parameters:

        bool ospfn = default(false);
        bool mobilityproposal = default(false);
        
        @display("bgb=705,476;i=abstract/router");
        
    submodules:
        ospfn: OSPFNRouting if ospfn == true {
            @display("p=446,181");
        }

        mobilityAgent: CcnMobilityAgent if mobilityproposal == true {
            @display("p=215,119");
        }
        
    connections allowunconnected:

        if (ospfn == true) {
            ccnlayer.upperOut++ --> ospfn.ipIn;
            ccnlayer.upperIn++ <-- ospfn.ipOut;
        }
        
        if(mobilityproposal == true){
          	ccnlayer.upperOut++ --> mobilityAgent.ccnIn;
            ccnlayer.upperIn++ <-- mobilityAgent.ccnOut;   
        }
}
