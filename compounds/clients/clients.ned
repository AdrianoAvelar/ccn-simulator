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

package ccnpp.compounds.clients;

simple client{
    parameters:
    	@display("i=abstract/people;is=l");
    	double lambda = default(1);
	double W = default(1); //TODO
	double check_time = default(0.1);
	double RTT = default(0.1);
    gates:
    	inout client_port;
}

