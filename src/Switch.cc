#include "Switch.h"
#include "Remote_Sensing_System_Message_m.h"

namespace remotesensingsystem {

Define_Module(Switch);

Switch::Switch(){

}

void Switch::initialize()
{
    for(int i = 0 ; i < 3 ; i++){
        this->x_ap_coordinates.push_back(0);
        this->y_ap_coordinates.push_back(0);
    }
}

void Switch::handleMessage(cMessage *msg)
{
    Remote_Sensing_System_Message* msg_rem;
    msg_rem = check_and_cast<Remote_Sensing_System_Message*>(msg); // check and cast

    cGate *input_port = msg_rem->getArrivalGate();
    const unsigned int input_port_index = (input_port->getIndex()); //get the input port index.
    const double x_msg = msg_rem->getX();
    const double y_msg = msg_rem->getY();

    if( strcmp(msg_rem->getName() , "Access_Point_Send_Coordinates_to_Switch") == 0){
        // the switch received the coordinates of an access point.

        this->x_ap_coordinates.at(input_port_index) = x_msg;
        this->y_ap_coordinates.at(input_port_index) = y_msg;

        //EV << this->x_ap_coordinates.size() << endl;

        //delete msg_rem;

    }else if(strcmp(msg_rem->getName() , "Sensing_Node_Send_Message_To_Switch") == 0){
        // the switch received a message from a sensing node.

        const double D_msg = msg_rem->getD();

        // d(a , b) = sqrt( (xb - xa)^2 + (yb - ya)^2 )
        // a --> sensing node
        // b --> access point

        double distance = 0, x_sub = 0 , y_sub = 0;

        const unsigned int M = this->x_ap_coordinates.size();

        for(unsigned int i = 0 ; i < (M - 1); i++){

            x_sub = ((this->x_ap_coordinates.at(i)) - x_msg);
            y_sub = ((this->y_ap_coordinates.at(i)) - y_msg);

            distance = sqrt( ((x_sub)*(x_sub)) + ((y_sub)*(y_sub))); // distance between the access point and the sensing node.

            if(distance <= D_msg){
                // The Access point 'i' is in the trasmission range of
                // the sensing node that sends this message.
                Remote_Sensing_System_Message *msg_f = new Remote_Sensing_System_Message("Sensing_Node_Send_Message_To_Switch");
                msg_f->setX(msg_rem->getX());
                msg_f->setY(msg_rem->getY());
                msg_f->setD(msg_rem->getD());
                send(check_and_cast<cMessage*>(msg_f) , "out" , i);
                // So, the switch forwards the message
                // to the relative access point.
            }
        }
        cancelAndDelete(msg_rem);// delete the message sent by the sensing node.
    }
}

};
