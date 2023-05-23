//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package inet.projects.dtn_network;
import inet.common.misc.ThruputMeteringChannel;
import inet.projects.dtn_network.dtn_node.DtnRouter;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
network dtn
{
    @display("bgb=694,399");
    types:
        channel LINK_100 extends ThruputMeteringChannel
        {
            parameters:
                delay = 50us;
                datarate = 100Mbps;
                displayAsTooltip = true;
                thruputDisplayFormat = "#N";
        }
    submodules:
        configurator: Ipv4NetworkConfigurator {
            parameters:
                @display("p=307,95;is=s");
        }
        host1: DtnRouter {
            parameters:
                @display("p=128,205;i=device/pc");
            gates:
                ethg[3];
        }
        host2: DtnRouter {
            parameters:
                @display("p=284,205;i=device/pc");
            gates:
                ethg[2];
        }
        host3: DtnRouter {
            parameters:
                @display("p=450,205;i=device/pc");
            gates:
                ethg[2];
        }
        host4: DtnRouter {
            parameters:
                @display("p=598,205;i=device/pc");
            gates:
                ethg[1];
        }
        host5: DtnRouter {
            parameters:
                @display("p=128,330;i=device/pc");
            gates:
                ethg[1];
        }
        host6: DtnRouter {
            parameters:
                @display("p=128,70;i=device/pc");
            gates:
                ethg[1];
        }
    connections:
        host1.ethg[0] <--> LINK_100 <--> host2.ethg[0];
        host2.ethg[1] <--> LINK_100 <--> host3.ethg[0];
        host3.ethg[1] <--> LINK_100 <--> host4.ethg[0];
        host1.ethg[1] <--> LINK_100 <--> host5.ethg[0];
        host1.ethg[2] <--> LINK_100 <--> host6.ethg[0];
}
