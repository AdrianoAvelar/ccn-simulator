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

package ccnpp.compounds.node.strategy;

moduleinterface strategy
{
    gates:
    	inout strategy_port;
}

simple strategy_layer like strategy
{
    parameters:
    	@display("i=block/buffer2;is=l");
	string routing_file=default("");
    gates:
	inout strategy_port;
}

simple spr extends strategy_layer
{
    @class(spr);
}

simple random_repository extends strategy_layer
{
    @class(random_repository);
}

simple parallel_repository extends strategy_layer
{
    @class(parallel_repository);
}


simple nrr1 extends strategy_layer{
    parameters:
	int cut_off = default(1);
	int TTL1 = default(1000);
    @class(nrr1);
}

simple nrr extends strategy_layer{
    parameters:
	int TTL2 = default(1000);
    @class(nrr);
}

