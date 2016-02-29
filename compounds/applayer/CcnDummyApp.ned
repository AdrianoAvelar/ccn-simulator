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

package ccnpp.compounds.applayer;

simple CcnDummyApp like ICcnApp
{
    parameters:
        @display("i=block/app2");
           
        @signal[hitHop](type="long");
        @signal[rttAll](type="long");
        
        @statistic[appThroughput](title="App Throughput"; source="app_throughput"; record=vector,mean; interpolationmode=none);
        @statistic[hitHop](title="Hit Hop"; source="hit_hop"; record=vector,mean; interpolationmode=none);
        @statistic[rttAll](title="RTT All"; source="rtt_all_pkts"; record=vector,mean; interpolationmode=none);
        
        string base_contentname = default("/cin/ufpe/movie");
        
        int chunkSize @unit(kb) = default(500kb);

        //Sender interval: exponential(1/lambda).
        double lambda = default(0.5);

        double startTime @unit(s) = default(0);
        double stopTime @unit(s) = default(0);
        
        string ccndModule = "^.ccnlayer.ccnd";

    gates:
        input ccnIn @labels(CCNControlInfo/up);
        output ccnOut @labels(CCNControlInfo/down);

}
