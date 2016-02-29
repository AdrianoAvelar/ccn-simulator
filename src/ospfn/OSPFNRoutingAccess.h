
#ifndef __OSPFNRouting_h_
#define  __OSPFNRouting_h_

#include "ModuleAccess.h"
#include "OSPFNRouting.h"

/**
 * Gives access to OSPFN module.
 */
class INET_API OSPFNRoutingAccess : public ModuleAccess<OSPFNRouting>
{
    public:
        OSPFNRoutingAccess() : ModuleAccess<OSPFNRouting>("ospfn") {}
        //OSPFNRoutingAccess(unsigned int index) : ModuleAccess2<cSimpleModule>("ospf", index) {}
};

#endif // __OSPFNRouting_h_
