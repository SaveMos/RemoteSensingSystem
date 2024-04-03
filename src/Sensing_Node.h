

#ifndef __PROGETTO_TCX_H
#define __PROGETTO_TCX_H

#include <omnetpp.h>


using namespace omnetpp;

namespace remotesensingsystem {


class Sensing_Node : public cSimpleModule
{
private:
  double posizione_iniziale_x;
  double posizione_iniziale_y;

  double actual_coordinate_x;
  double actual_coordinate_y;

  double new_waypoint_x;
  double new_waypoint_y;

  double remaining_time;

  double D;

  int counter;

  double speed;

  double T;

  int times;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  private:
    int calculate_negative();
    virtual void new_calculations();
    virtual void computing_coordinates();
    virtual void scheduler();
    virtual void update_coordinates(double l, double m);
};

}; // namespace

#endif
