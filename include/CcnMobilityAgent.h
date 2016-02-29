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

#ifndef CcnMobilityAgent_H_
#define CcnMobilityAgent_H_

#include <omnetpp.h>
#include "CcnAppMessage_m.h"
#include "ICcnApp.h"
#include <boost/unordered_map.hpp>
#include "MobilityAppMessage_m.h"
#include "OSPFNRouting.h"

#define INTERVAL_REQUEST 0.5
#define NAME_SIZE 64
#define BULK_TIME 1.0

#define AGETIMER 5
#define EXPIRED_TIME_LIMIT 60
#define UPDATE_TIME 5

#define SEND_OTHER_VIDEO truncnormal(20,5)
#define AGE_MSG 0x123

#define APPID 100
typedef struct{
        chunk_t name;
        vector<chunk_t> contents;
        double time ;
}ActiveSession;



class CcnMobilityAgent : public cSimpleModule, public ICcnApp, public cListener {
public:
    typedef map<chunk_t,ActiveSession> ACTIVE_MAP;

    typedef std::vector<ActiveSession> ACTIVE_VECTOR_V;

    CcnMobilityAgent();
    virtual ~CcnMobilityAgent();
    virtual void handleMessage (cMessage *msg);
    virtual void registerMyselfInCcnLayer();
//virtual void receiveChangeNotification(int category, const cObject *details);
    /**
     * Initialization and termination of the module
     */
    virtual void    initialize(int);
protected:
    //ACTIVE_MAP::iterator find(chunk_t contentName);
    virtual int numInitStages() const  {return 6;}
    void notifyConsumers();
    void sendVirtualInterest(chunk_t name, std::vector<chunk_t>& contents);
    void handleSelfMessage(cMessage *msg);
    void ageTable();
    void processPacket(CcnAppMessage *pkt);
    void processMobilityMessage(CcnAppMessage* appmsg, MobilityAppMessage* mobmsg);

    /*
       * Signal handler for cObject, override cListener function.
       */
      virtual void receiveSignal(cComponent *source, simsignal_t signalID, cObject *obj) override;

private:
    int appId;
    //ACTIVE_VECTOR_V ACTIVE_VECTOR;
    ACTIVE_MAP sessionsMap;
    cMessage *ageTableTimer;
    //ForwardingTable *ft;
    OSPFN::Router* ospfnrouter;
};

#endif /* CcnMobilityAgent_H_ */
