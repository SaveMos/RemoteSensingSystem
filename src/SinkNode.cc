#include "SinkNode.h"
#include "Remote_Sensing_System_Message_m.h"

namespace remotesensingsystem {

Define_Module(SinkNode);

SinkNode::SinkNode(){

}

void SinkNode::initialize()
{

}

void SinkNode::handleMessage(cMessage *msg)
{
    cancelAndDelete(msg); // delete the message sent by the access point.
}

};
