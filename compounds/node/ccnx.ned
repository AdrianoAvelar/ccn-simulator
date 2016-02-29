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

import ccnpp.compounds.node.strategy.*;
import ccnpp.compounds.node.cache.*;
import ccnpp.Ccn;
import ccnpp.compounds.content.Ccnr;
import ccnpp.compounds.node.CcnCore;

module ccnx
{
    parameters:
        string forwardingTableModule;
        *.forwardingTableModule = default(forwardingTableModule);
        
        string RS = default("lru_cache");
        string FS = default("spr");

        int level = default(-1);
        double centrality = default(-1);
        content_store.DS = default("lce");
        bool hasCcnr = default(false); //has Ccnr attached?

        @display("i=abstract/dispatcher;is=n");
    gates:
        inout ccnd_port @labels(CcnCore);

    submodules:

        content_store: <"ccnpp.compounds.node.cache." + RS> like cache {
            @display("i=block/buffer2;is=n;p=121,24");
        }

        ccnr: Ccnr if (hasCcnr == true) {
            @display("p=121,187;i=abstract/cache;is=n");
        }

        core_layer: CcnCore {
            @display("p=59,108;b=,,rect,#D68888,black,0;is=n");
        }

    //connections:
    connections allowunconnected:

        core_layer.content_store_port <--> { @display("ls=dodgerBlue,3,da"); } <--> content_store.cache_port;
        
        if (hasCcnr == true) {
        core_layer.ccnr_port <--> { @display("ls=dodgerBlue,3,da"); } <--> ccnr.ccnd_port;
        }
        core_layer.ccnd_port <--> { @display("ls=dodgerBlue,3,da"); } <--> ccnd_port;
}
