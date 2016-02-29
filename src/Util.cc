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

#include "Util.h"

double Util::stat_bulk_t = 1.0;

Util::Util() {
    // TODO Auto-generated constructor stub

}

Util::~Util() {
    // TODO Auto-generated destructor stub
}

string Util::getNoExt(string withext) {

    size_t found = -1;

    if ((found = withext.find(".") != std::string::npos)) {
        found = withext.find_last_of(".");
    }

    string noext = withext.substr(0, found);

    return noext;
}

void Util::replace(string &s, char from, char to){
    std::replace( s.begin(),s.end(), from, to);
}

std::string Util::removeChunkId(chunk_t contentName) {

    unsigned found = 0 ;

    if ((found = contentName.find(VIDEO_TAG) != std::string::npos)) {
           found = contentName.find_last_of(VIDEO_TAG);
       } else if ((found = contentName.find(DUMMY_TAG) != std::string::npos)) {
           found = contentName.find_last_of(DUMMY_TAG);
       }

    if(!found)
        return contentName;

    return contentName.substr(0, found);
}

bool Util::isDummyApp(chunk_t contentName){

    std::size_t found = -1;
    return ((found = contentName.find(DUMMY_TAG) != std::string::npos));
}
int Util::getChunkId(chunk_t contentName) {

    std::size_t found = -1;

//    if ((found = contentName.find("#") != std::string::npos)) {
//        found = contentName.find_last_of("#");
//    } else if ((found = contentName.find("_") != std::string::npos)) {
//        found = contentName.find_last_of("_");
//    }

    if ((found = contentName.find(VIDEO_TAG) != std::string::npos)) {
           found = contentName.find_last_of(VIDEO_TAG);
       } else if ((found = contentName.find(DUMMY_TAG) != std::string::npos)) {
           found = contentName.find_last_of(DUMMY_TAG);
       }

    if (found < 0)
        return found;

    contentName = contentName.substr(found + 1, contentName.size());
//
//    contentName = contentName.substr(found + 1, contentName.size());
//           return atoi(contentName.c_str());
//
//    unsigned found = contentName.find_last_of("#");
//    contentName = contentName.substr(found + 1, contentName.size());

    return atoi(contentName.c_str());
}

const std::string Util::currentDateTime() {

    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d | %X", &tstruct);

    return buf;
}

void Util::setBulkTime(double stat_bulk_t) {
    stat_bulk_t = stat_bulk_t > 0 ? stat_bulk_t : 1.0;
}

double Util::getBulkTime() {
    return stat_bulk_t;
}

string Util::getPrefixSource(const std::string& str) {

    unsigned found = str.find_last_of("/\\");
    string temp = str.substr(0, found);

    found = temp.find_last_of("/\\");

    return temp.substr(found, temp.length());
}

/*
 * get "/cin/ufpe/br/movie.mp4" and returns "/cin/ufpe/br"
 */
std::string Util::getPrefixContentName(const std::string& str) {
    unsigned found = str.find_last_of("/\\");
    return str.substr(0, found);
}

std::string Util::getResourceFromPrefix(const std::string& str) {
    unsigned found = str.find_last_of("/\\");
    return str.substr(found + 1, str.length());
}

int Util::getArrivalId(string gate_name) {

    unsigned found = gate_name.find_last_of(":");
    return atoi(gate_name.substr(found + 1, gate_name.size()).c_str());
}

int Util::getProtocolTypeByName(chunk_t name) {

    if (name.compare("ccnx") == 0)
        return 0;
    else if (name.compare("ospfn") == 0)
        return 89;
    else
        return -1;
}

int Util::getAndRemoveProtocol(chunk_t & gate_name) {

    unsigned found = gate_name.find_last_of(":");

    gate_name = gate_name.substr(found + 1, gate_name.size()).c_str();

    return getProtocolTypeByName(gate_name.substr(0, found).c_str());

}
