#ifndef __REMOTESENSINGSYSTEM_ACCESSPOINT_H
#define __REMOTESENSINGSYSTEM_ACCESSPOINT_H

#include <omnetpp.h>

using namespace omnetpp;

namespace remotesensingsystem {

class AccessPoint : public cSimpleModule
{
    private:
        double x;
        double y;

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);

    public:
        AccessPoint();
};

};

#endif
