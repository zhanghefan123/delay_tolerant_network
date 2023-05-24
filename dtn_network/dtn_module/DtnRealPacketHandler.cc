#include "inet/projects/dtn_network/dtn_module/DtnRealPacketHandler.h"
#include "inet/projects/dtn_network/dtn_module/dtn.h"
#include "inet/projects/dtn_network/dtn_packets/EpidemicHeader_m.h"
#include "inet/projects/dtn_network/dtn_states/DtnNeighborState.h"
#include "inet/networklayer/common/InterfaceTable.h"
namespace inet{
    DtnRealPacketHandler::DtnRealPacketHandler(cSimpleModule* containingModule) {
        this->containingModule = containingModule;
    }

    void DtnRealPacketHandler::processPacket(Packet * packet, DtnNeighbor* dtnNeighbor) {
        std::cout << "received real packet" << std::endl;
        dtn* dtn_module = dynamic_cast<dtn*>(this->containingModule);
        auto * ift = dynamic_cast<InterfaceTable*>(this->containingModule->getParentModule()->getSubmodule("interfaceTable"));
        // get neighborAck
        auto epidemicHeader = packet->peekAtFront<EpidemicHeader>();
        // get the packet id
        std::string packetId = epidemicHeader->getUuid();
        // judge the key
        if(dtn_module->packets_buffer.count(packetId) > 0)
        {
            delete packet;
        } else {
            // store the packet in on buffer
            dtn_module->packets_buffer[packetId] = std::make_pair(packet, simTime());
            dtn_module->packetIds.insert(packetId);// store the packet id in dtn -- used for later swap
            // get the destination address of the packet
            Ipv4Address destAddr = epidemicHeader->getDestAddr();
            if(ift->isLocalAddress(destAddr)){
                std::cout << "reach final destination" << std::endl;
            }
            // resolve the request
            dtnNeighbor->requestIds.erase(packetId);
        }
        std::cout << "received packet id: " << packetId << std::endl;
    }
}
