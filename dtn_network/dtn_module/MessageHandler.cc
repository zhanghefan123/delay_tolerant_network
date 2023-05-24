#include "inet/projects/dtn_network/dtn_module/MessageHandler.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/projects/dtn_network/dtn_neighbors/DtnNeighbor.h"
#include "inet/projects/dtn_network/dtn_packets/EpidemicHeader_m.h"
#include "inet/projects/dtn_network/dtn_packets/EpidemicPacket.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include "inet/projects/dtn_network/dtn_module/dtn.h"
namespace inet{
    MessageHandler::MessageHandler(cSimpleModule* containingModule) {
        this->dtnNeighborDetectionHandler = new DtnNeighborDetectionHandler(containingModule);
        this->dtnNeighborIdDbHandler = new DtnNeighborIdDbHandler(containingModule);
        this->dtnNeighborRequestHandler = new DtnNeighborRequestHandler(containingModule);
        this->dtnRealPacketHandler = new DtnRealPacketHandler(containingModule);
        this->containingModule = containingModule;
    }

    MessageHandler::~MessageHandler() {
        delete this->dtnNeighborDetectionHandler;
        delete this->dtnNeighborIdDbHandler;
        delete this->dtnNeighborRequestHandler;
        delete this->dtnRealPacketHandler;
    }

    void MessageHandler::messageReceived(omnetpp::cMessage *message) {
        // judge is self msg or packet
        if(message->isSelfMessage()){
            handleTimer(message);
        }
        else {
            auto * pk = check_and_cast<Packet*>(message);
            auto protocol = pk->getTag<PacketProtocolTag>()->getProtocol();
            if(protocol == &Protocol::dtn){
                processPacket(pk);
            }
        }
    }
    // handle self timer
    void MessageHandler::handleTimer(omnetpp::cMessage *timer) {
        DtnNeighbor* neighbor;
        switch(timer->getKind()){
            case DtnNeighbor::NEIGHBOR_DETECT_MSG_KIND:{
                if(!(neighbor = reinterpret_cast<DtnNeighbor*>(timer->getContextPointer()))){
                    EV_ERROR << "Error: DtnNeighbor::NEIGHBOR_DETECT_MSG_KIND: no neighbor found" << std::endl;
                    delete timer;
                } else {
                    // neighbor inside timer to process event
                    neighbor->processEvent(DtnNeighbor::NEIGHBOR_DETECT_TIMER_RECEIVED);
                }
                break;
            }
            case DtnNeighbor::CHECK_NEIGH_EXPIRE_MSG_KIND:
            {
                if(!(neighbor = reinterpret_cast<DtnNeighbor*>(timer->getContextPointer()))){
                    EV_ERROR << "Error: DtnNeighbor::CHECK_NEIGH_EXPIRE_MSG_KIND: no neighbor found" << std::endl;
                    delete timer;
                } else {
                    // neighbor inside timer to process event
                    neighbor->processEvent(DtnNeighbor::NEIGHBOR_EXPIRE_TIMER_RECEIVED);
                }
                break;
            }
            case DtnNeighbor::NEIGHBOR_EXCHANGE_MSG_KIND:
            {
                if(!(neighbor = reinterpret_cast<DtnNeighbor*>(timer->getContextPointer()))){
                    EV_ERROR << "Error: DtnNeighbor::NEIGHBOR_EXCHANGE_MSG_KIND: no neighbor found" << std::endl;
                    delete timer;
                } else {
                    // neighbor inside timer to process event
                    neighbor->processEvent(DtnNeighbor::NEIGHBOR_START_EXCHANGE_MSG);
                }
                break;
            }
            case DtnNeighbor::NEIGHBOR_SEND_PACKET_MSG_KIND:
            {
                if(!(neighbor = reinterpret_cast<DtnNeighbor*>(timer->getContextPointer()))){
                    EV_ERROR << "Error: DtnNeighbor::NEIGHBOR_SEND_PACKET_MSG_KIND: no neighbor found" << std::endl;
                    delete timer;
                } else {
                    // neighbor inside timer to process event
                    neighbor->processEvent(DtnNeighbor::DtnNeighborEventType::NEIGHBOR_SEND_REQUEST_PACKETS);
                }
                break;
            }
        }
    }

    void MessageHandler::processPacket(Packet * packet) const {
        auto epidemicHeader = packet->peekAtFront<EpidemicHeader>();
        auto dtn_module = dynamic_cast<dtn*>(this->containingModule);
        auto incomingInterfaceId = packet->getTag<InterfaceInd>()->getInterfaceId();
        DtnNeighbor* correspondingNeighbor = dtn_module->findNeighborByInterfaceId(incomingInterfaceId);
        switch (EpidemicPacket::Type(epidemicHeader->getType())){
            case EpidemicPacket::NEIGHBOR_DETECTION_PACKET_TYPE:
            {
                // call the dtn_neighbor_detection_handler to process the packet
                this->dtnNeighborDetectionHandler->processPacket(packet, correspondingNeighbor);
                break;
            }
            case EpidemicPacket::NEIGHBOR_ID_DB_PACKET_TYPE:
            {
                // call the dtn_neighbor_id_db_handler to process the packet
                this->dtnNeighborIdDbHandler->processPacket(packet, correspondingNeighbor);
                break;
            }
            case EpidemicPacket::NEIGHBOR_REAL_PACKET_REQUEST_TYPE:
            {
                // call the dtn neighbor request handler
                this->dtnNeighborRequestHandler->processPacket(packet, correspondingNeighbor);
                break;
            }
            case EpidemicPacket::NEIGHBOR_REAL_PACKET_TYPE:
            {
                this->dtnRealPacketHandler->processPacket(packet, correspondingNeighbor);
                break;
            }
            default:{
                std::cout << "undefined packet type" << std::endl;
                delete packet;
            }

        }
    }

    void MessageHandler::startTimer(omnetpp::cMessage *timer, const simtime_t& delay) const {
        this->containingModule->scheduleAfter(delay, timer);
    }

    void MessageHandler::clearTimer(cMessage* timer) const{
        this->containingModule->cancelEvent(timer);
    }
}