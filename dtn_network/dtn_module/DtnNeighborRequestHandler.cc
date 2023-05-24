#include "inet/projects/dtn_network/dtn_module/DtnNeighborRequestHandler.h"
#include "inet/projects/dtn_network/dtn_packets/EpidemicHeader_m.h"
#include "inet/projects/dtn_network/dtn_module/dtn.h"
#include <set>
namespace inet{
    DtnNeighborRequestHandler::DtnNeighborRequestHandler(omnetpp::cSimpleModule *containingModule) {
        this->containingModule = containingModule;
    }

    void DtnNeighborRequestHandler::processPacket(inet::Packet *packet, inet::DtnNeighbor *neighbor) {
        // convert to dtn_module
        dtn* dtn_module = dynamic_cast<dtn*>(this->containingModule);
        std::cout << dtn_module->getFullPath() << " received dtn neighbor request packet" << std::endl;
        // auto epidemicHeader
        auto epidemicHeader = packet->peekAtFront<EpidemicHeader>();
        // get length of ids
        int length = epidemicHeader->getMsgIdLength();
        // place into sendids
        for(int i = 0; i < length; i++){
            // get the id
            std::string id = epidemicHeader->getMsgIds(i);
            // add the id to the neighborIds
            neighbor->sendIds.insert(id);
        }
        // neighbor->processEvent(DtnNeighbor::NEIGHBOR_SEND_REQUEST_PACKETS);
        // delete packet
        delete packet;
    }
}