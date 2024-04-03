#ifndef __REMOTESENSINGSYSTEM_SWITCH_H
#define __REMOTESENSINGSYSTEM_SWITCH_H

#include <omnetpp.h>
#include <vector>

using namespace omnetpp;

namespace remotesensingsystem {

class Switch : public cSimpleModule
{
    private:
        std::vector<double> x_ap_coordinates;
        std::vector<double> y_ap_coordinates;

    protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);

    public:
        Switch();
};

};

#endif
