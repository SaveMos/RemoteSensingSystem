package remotesensingsystem;

simple AccessPoint
{
    parameters:	
        int H @unit(m) = default(1000m);
        int L @unit(m) = default(1000m);
    	  
    gates:
        input in;
        output out_sink;
        output out_switch;
}
