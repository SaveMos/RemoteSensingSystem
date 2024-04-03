package remotesensingsystem.simulations;

import remotesensingsystem.Switch;
import remotesensingsystem.SinkNode;
import remotesensingsystem.AccessPoint;
import remotesensingsystem.Sensing_Node;

network RemoteSensingSystem
{
    @display("bgb=2000,2000");


    submodules:
        switch: Switch {
            @display("p=977.95197,961.92;is=vl");
        }

        sink: SinkNode {
            @display("p=1843.6799,961.92;is=vl");
        }

        accesspoint1: AccessPoint {
            @display("p=1414.824,573.144;is=vl");
        }

        accesspoint2: AccessPoint {
            @display("p=1414.824,961.92;is=vl");
        }

        accesspoint3: AccessPoint {
            @display("p=1414.824,1334.664;is=vl");
        }

        sensingnode1: Sensing_Node {
            @display("p=280.56,244.48799;is=vl");
        }

        sensingnode2: Sensing_Node {
            @display("p=280.56,525.048;is=vl");
        }

        sensingnode3: Sensing_Node {
            @display("p=280.56,805.608;is=vl");
        }

        sensingnode4: Sensing_Node {
            @display("p=280.56,1098.192;is=vl");
        }

        sensingnode5: Sensing_Node {
            @display("p=280.56,1406.808;is=vl");
        }

        sensingnode6: Sensing_Node {
            @display("p=280.56,1739.4719;is=vl");
        }

        sensingnode7: Sensing_Node {
            @display("p=601.2,112.224;is=vl");
        }

        sensingnode8: Sensing_Node {
            @display("p=689.376,1823.6399;is=vl");
        }

        sensingnode9: Sensing_Node {
            @display("p=1074.1439,1627.2479;is=vl");
        }

        sensingnode10: Sensing_Node {
            @display("p=949.896,244.48799;is=vl");
        }



    connections:
        accesspoint1.out_sink --> {  delay = 100ms; } --> sink.in++;
        accesspoint2.out_sink --> {  delay = 100ms; } --> sink.in++;
        accesspoint3.out_sink --> {  delay = 100ms; } --> sink.in++;

        accesspoint1.out_switch --> {  delay = 100ms; } --> switch.in_access_point++;
        accesspoint2.out_switch --> {  delay = 100ms; } --> switch.in_access_point++;
        accesspoint3.out_switch --> {  delay = 100ms; } --> switch.in_access_point++;

        sensingnode1.out --> {  delay = 100ms; } --> switch.in_sensing_nodes++;
        sensingnode2.out --> {  delay = 100ms; } --> switch.in_sensing_nodes++;
        sensingnode3.out --> {  delay = 100ms; } --> switch.in_sensing_nodes++;
        sensingnode4.out --> {  delay = 100ms; } --> switch.in_sensing_nodes++;
        sensingnode5.out --> {  delay = 100ms; } --> switch.in_sensing_nodes++;
        sensingnode6.out --> {  delay = 100ms; } --> switch.in_sensing_nodes++;
        sensingnode7.out --> {  delay = 100ms; } --> switch.in_sensing_nodes++;
        sensingnode8.out --> {  delay = 100ms; } --> switch.in_sensing_nodes++;
        sensingnode9.out --> {  delay = 100ms; } --> switch.in_sensing_nodes++;
        sensingnode10.out --> {  delay = 100ms; } --> switch.in_sensing_nodes++;


        switch.out++ --> {  delay = 100ms; } --> accesspoint1.in;
        switch.out++ --> {  delay = 100ms; } --> accesspoint2.in;
        switch.out++ --> {  delay = 100ms; } --> accesspoint3.in;

}
