#ifndef __REMOTESENSINGSYSTEM_SINKNODE_H
#define __REMOTESENSINGSYSTEM_SINKNODE_H

#include <omnetpp.h>

using namespace omnetpp;

namespace remotesensingsystem {

class SinkNode : public cSimpleModule
{

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);

    public:
        SinkNode();
};

};

#endif
