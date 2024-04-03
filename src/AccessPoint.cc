#include "AccessPoint.h"
#include "Remote_Sensing_System_Message_m.h"

namespace remotesensingsystem {

Define_Module(AccessPoint);

AccessPoint::AccessPoint(){

}

void AccessPoint::initialize()
{
    this->x = uniform(0 , par("H").intValue()); // generate its own coordinates.
    this->y = uniform(0 , par("L").intValue());

    Remote_Sensing_System_Message *msg_r = new Remote_Sensing_System_Message("Access_Point_Send_Coordinates_to_Switch");
    msg_r->setX(this->x);
    msg_r->setY(this->y);
    msg_r->setD(0);

    send(check_and_cast<cMessage*>(msg_r), "out_switch"); // send its coordinates to the switch.
}

void AccessPoint::handleMessage(cMessage *msg)
{
    send(msg, "out_sink"); // forward the message to the sink node.
}

};
