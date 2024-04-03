#include "Sensing_Node.h"
#include "Remote_Sensing_System_Message_m.h"

namespace remotesensingsystem
{
    Define_Module(Sensing_Node);

    void Sensing_Node::update_coordinates(double l, double m)
    {
        if ((new_waypoint_x - actual_coordinate_x) < 0)
        {
            actual_coordinate_x = actual_coordinate_x - m;

            if ((new_waypoint_y - actual_coordinate_y) < 0)
            {
                actual_coordinate_y = actual_coordinate_y - l;
            }
            else
            {
                actual_coordinate_y = actual_coordinate_y + l;
            }
        }
        else
        {
            actual_coordinate_x = actual_coordinate_x + m;

            if ((new_waypoint_y - actual_coordinate_y) < 0)
            {
                actual_coordinate_y = actual_coordinate_y - l;
            }
            else
            {
                actual_coordinate_y = actual_coordinate_y + l;
            }
        }
    }

    void Sensing_Node::scheduler()
    {
        for (int i = 0; i < times; i++)
        {
            cMessage *msg_new = new cMessage("Sensing_Node_Must_Send_a_Message");
            scheduleAt(simTime() + (i + 1) * T, msg_new);
        }
    }

    int Sensing_Node::calculate_negative()
    {
        if (uniform(0, 2) < 1)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
    // calcola nuovo waypoint e velocità
    void Sensing_Node::computing_coordinates()
    {
        bool one = false, two = false;
        double distance_in_x = 0;
        double distance_in_y = 0;

        const int min_dist_mov = par("min_distance_movement").intValue();
        const int max_dist_mov = par("max_distance_movement").intValue();

        const int L_par = par("L").intValue();
        const int H_par = par("H").intValue();

        do
        {
            // compute the new waypoint
            distance_in_x = calculate_negative() * (uniform(min_dist_mov, max_dist_mov));
            distance_in_y = calculate_negative() * (uniform(min_dist_mov, max_dist_mov));

            // we need "calculate_negative" for conisder even backwards movements.
            one = false;
            two = false;
            // check that the waypoint does not go out of the limits.
            if ((actual_coordinate_x + distance_in_x) > L_par || (actual_coordinate_x + distance_in_x) < 0)
            { // se la x del nuovo waypoint sfora il piano
                one = false;
                continue; // we need to re-iterate again.
            }
            else
            {
                one = true;
            }

            if ((actual_coordinate_y + distance_in_y) > H_par || (actual_coordinate_y + distance_in_y) < 0)
            { // se la y del nuovo waypoint sfora il piano
                two = false;
                continue; // we need to re-iterate again.//o � negativa
            }
            else
            {
                two = true;
            }

        } while (!(one & two));

        new_waypoint_x = actual_coordinate_x + distance_in_x;
        new_waypoint_y = actual_coordinate_y + distance_in_y;

        // compute the new velocity of the sensing node.
        speed = uniform(1, par("max_speed").doubleValue());
    }
    void Sensing_Node::new_calculations()
    {
        computing_coordinates();

        // calcolo il tempo per arrivare al nuovo waypoint dalla posizione dove sono io
        double travel_time = sqrt(pow(new_waypoint_x - actual_coordinate_x, 2) + pow(new_waypoint_y - actual_coordinate_y, 2)) / speed;
        double travel_time_t = 0;

        travel_time += remaining_time;
        // sommo il tempo rimasto dal movimento precedente e lo aggiungo al tempo di viaggio successivo

        // come se fosse tempo in piu in cui viaggia, in modo tale da considerarlo come tempo in piu

        // per trasmettere

        // calcolo il numero di volte che il nodo prover� ad inviare il messaggio broadcast

        while (travel_time < T)
        {
            remaining_time = travel_time;
            actual_coordinate_x = new_waypoint_x;
            actual_coordinate_y = new_waypoint_y;

            computing_coordinates();

            travel_time_t = sqrt(pow(new_waypoint_x - actual_coordinate_x, 2) + pow(new_waypoint_y - actual_coordinate_y, 2)) / speed;

            travel_time_t += remaining_time;

            travel_time = travel_time_t;
        }

        // calcolo il numero di volte che il nodo prover� ad inviare il messaggio broadcast durante il nuovo viaggio
        times = floor(travel_time / T);

        remaining_time = (travel_time / T) - times;

        counter = times;

        // schedulo successivamente tot tentativi di Sensing_Node_Must_Send_a_Message agli access point a distanza di T secondi
        scheduler();
    }

    void Sensing_Node::initialize()
    {
        // inizializzo tutte le variabili
        posizione_iniziale_x = uniform(0, par("L").intValue());
        posizione_iniziale_y = uniform(0, par("H").intValue());
        times = 0;          // contatore di messaggi da inviare agli access point durante il tragitto
        remaining_time = 0; // tempo rimanente dovuto al fatto che il tragitto non dura un multiplo di T secondi
        counter = 0;        // contatore utile per capire quando ha trasmisso tutti i messaggi durante lo spostamento da un waypoint all'altro
        // inizializzo le coordinate iniziali
        actual_coordinate_x = posizione_iniziale_x;
        actual_coordinate_y = posizione_iniziale_y;
        // EV << "Mi trovo a " << "(" << actual_coordinate_x << ", " << actual_coordinate_y << ")" << endl;
        new_waypoint_x = 0;
        new_waypoint_y = 0;

        speed = 0;

        D = par("D").doubleValue();

        T = par("T").doubleValue();

        cMessage *msg = new cMessage("Sensing_Node_Start");  // message for the first movement
        scheduleAt(simTime() + uniform(0.1, 0.9), msg);
        // We add a little offset for desyncronize sensing nodes
    }

    void Sensing_Node::handleMessage(cMessage *msg)
    {
        if (msg->isSelfMessage())
        {
            if (strcmp(msg->getName(), "Sensing_Node_Start") == 0)
            {                         // se � l'automessaggio per iniziare la trasmissione
                cancelAndDelete(msg); // delete the message for save memory.
                new_calculations();   // calcolo tutti i nuovi parametri (velocit�, nuovo waypoint, num di mess da inviare durante lo spostamento)
            }else if(strcmp(msg->getName(), "Sensing_Node_Must_Send_a_Message") == 0){
                // mi � arrivato un messaggio che indica che il SS deve inviare un messaggio agli access point

                // update coordinates
                const double alfa = atan(abs(new_waypoint_y - actual_coordinate_y) / abs(new_waypoint_x - actual_coordinate_x));
                const double k = speed * T; // ipotenusa mini triangolo rettangolo
                const double l = k * sin(alfa);
                const double m = k * cos(alfa);

                cancelAndDelete(msg); // delete the message for save memory.

                update_coordinates(l, m); // update the coordinates of the sensing node.

                // send the message to the switch
                Remote_Sensing_System_Message *msg_r = new Remote_Sensing_System_Message("Sensing_Node_Send_Message_To_Switch");
                msg_r->setX(actual_coordinate_x);
                msg_r->setY(actual_coordinate_y);
                msg_r->setD(D);
                send(check_and_cast<cMessage*>(msg_r), "out");

                // I sended a message

                counter--; // decrease the message counter.

                if (counter <= 0){
                    // i just sent the last message in this path.
                    new_calculations();
                }
            }
        }
    }
};
