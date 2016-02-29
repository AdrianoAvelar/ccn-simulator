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

simple CcnVideoApp like ICcnApp
{
    parameters:
        @display("i=block/browser");
        int video_count = default(1);
        string base_contentname = default("/cin/ufpe/movie");
        double max_delay @unit(ms) = default(5ms);
        int sender = default(0);
        //https://www.ccnx.org/releases/latest/doc/technical/InterestMessage.html
        double interestLifetime @unit(ms) = default(4000ms);
        
        int max_retrans_attempts = default(10);//10 tries to retransmite
        
        //Sender interval: exponential(1/lambda).
        double lambda = default(0.5);
        double frame_interval= default(0.010);
        
        //DummySender
        int dummysender = default(0);
        int num_dummy_chunks = default(1000);
        double startTime @unit(s) = default(0);
        double stopTime @unit(s) = default(0);
        
        bool cleanall = default(false);
        bool evaluate = default(false);
        bool toYuv = default(false);
        bool qoe_metrics = default(false);
        
        string ccndModule = "^.ccnlayer.ccnd";
    
      gates:
        input ccnIn;
        output ccnOut;
  		
}