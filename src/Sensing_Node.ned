
package remotesensingsystem;


simple Sensing_Node
{
    parameters:
        int H @unit(m) = default(1000m);
        int L @unit(m) = default(1000m);
        double D  @unit(m) = default(150m); 
        double T @unit(s) = default(2s);   
        double max_speed = default(3);
        int max_distance_movement @unit(m) = default(6m);
        int min_distance_movement @unit(m) = default(1m);
        
    gates:
        output out;
}
