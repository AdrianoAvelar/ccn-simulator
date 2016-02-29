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

package ccnpp.compounds.content;

simple Ccnr
{
    parameters:
        double file_size = default(10);
        int objects = default(100);
        double alpha = default(1);
        double q = default(0);
        double cut_off = default(1);

        @display("i=block/buffer2;is=l");
        
        gates:
            inout ccnd_port;

}
