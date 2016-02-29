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

#ifndef UTIL_H_
#define UTIL_H_

#include <string>
#include "ccnsim.h"
#include "commons.h"
using std::string;
#include <algorithm>

#define BOOL_FROM_INT(x) x > 0 ? true : false

class Util {
public:
    Util();
    virtual ~Util();

    //FIXME[EAMA] Mover para UTIL
    static string getNoExt(string withext);

    //String Manipulation
    static std::string removeChunkId(chunk_t contentName);
    static int getChunkId(chunk_t contentName);
    static void replace(string &s, char from, char to);
    static std::string getResourceFromPrefix(const std::string& str);
    static string getPrefixSource(const std::string& str);

    static void setBulkTime(double stat_bulk_t);
    static double getBulkTime();
    static const std::string currentDateTime();
    static int getArrivalId(string gate_name);
    static std::string getPrefixContentName(const std::string& str);

    static int getProtocolTypeByName(chunk_t name);
    static int getAndRemoveProtocol(chunk_t & gate_name);

    static bool isDummyApp(chunk_t contentName);

private:
    static double stat_bulk_t;

};

#endif /* UTIL_H_ */
