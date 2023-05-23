#include "inet/projects/dtn_network/dtn_module/DtnNeighborIdDbHandler.h"
#include "inet/projects/dtn_network/dtn_packets/EpidemicHeader_m.h"
#include "inet/projects/dtn_network/dtn_module/dtn.h"
#include <set>
namespace inet{
    DtnNeighborIdDbHandler::DtnNeighborIdDbHandler(omnetpp::cSimpleModule *containingModule) {
        this->containingModule = containingModule;
    }

    void DtnNeighborIdDbHandler::processPacket(inet::Packet *packet, inet::DtnNeighbor *neighbor) {
        // convert to dtn_module
        dtn* dtn_module = dynamic_cast<dtn*>(this->containingModule);
        std::cout << dtn_module->getFullPath() << " received dtn neighbor id db packet" << std::endl;
        // auto epidemicHeader
        auto epidemicHeader = packet->peekAtFront<EpidemicHeader>();
        // get length of ids
        int length = epidemicHeader->getMsgIdLength();
        std::set<std::string> neighborIds;
        // get all the ids
        for(int i = 0; i < length; i++){
            // get the id
            std::string id = epidemicHeader->getMsgIds(i);
            // add the id to the neighborIds
            neighborIds.insert(id);
        }
        // do the difference
        std::set_difference(neighborIds.begin(), neighborIds.end(),
                            dtn_module->packetIds.begin(), dtn_module->packetIds.end(),
                            std::inserter(neighbor->requestIds, neighbor->requestIds.begin()));
        // cout the id about to request
        for(const auto& id : neighbor->requestIds){
            std::cout << "about to request id: " << id << std::endl;
        }
        // process event
        neighbor->processEvent(DtnNeighbor::NEIGHBOR_SEND_REQUEST_IDS);
        // delete packet
        delete packet;
    }
}