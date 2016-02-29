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

simple CcnCore
{
    parameters:
      
        @class(CcnCore);
        @display("i=block/cogwheel;is=l");
        

        @signal[pitSize](type="int");
        @statistic[pitSize](title="pit size"; source="pit_size"; record=vector,mean; interpolationmode=none);

        double RTT @unit(s) = default(3s);
        double pit_timeout @unit(s) = default(0s);
        double fib_timeout @unit(s) = default(0s);
        
        //string forwardingTableModule = default("^.^.^.forwardingTable");
		string forwardingTableModule;
		
    gates:

        inout strategy_port;
        inout ccnr_port;
        inout content_store_port;
        inout ccnd_port;
}


