#include "inet/projects/dtn_network/dtn_neighbors/DtnNeighbor.h"
#include "inet/projects/dtn_network/dtn_states/DtnNeighborState.h"
#include "inet/projects/dtn_network/dtn_states/DtnNeighborStateDown.h"
#include "inet/projects/dtn_network/dtn_packets/EpidemicHeader_m.h"
#include "inet/projects/dtn_network/dtn_packets/EpidemicPacket.h"
#include "inet/projects/dtn_network/dtn_module/dtn.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/networklayer/common/HopLimitTag_m.h"
#include "inet/linklayer/common/InterfaceTag_m.h"
#include <iostream>
namespace inet{
    DtnNeighbor::~DtnNeighbor(){
        std::cout << "DtnNeighbor destructor called" << std::endl;
        if(this->neighborDetectTimer != nullptr){
            delete this->neighborDetectTimer; // has error here ? why ? because the timer is not deleted
        }
        if(this->neighborExpireTimer != nullptr){
            delete this->neighborExpireTimer;
        }
        if(this->neighborExchangeTimer != nullptr){
            delete this->neighborExchangeTimer;
        }
        if(this->neighborSendPacketTimer != nullptr){
            delete this->neighborSendPacketTimer;
        }
        if(this->previousState != nullptr)
            delete this->previousState;
        if(this->state != nullptr){
            delete this->state;
        }
    }
    DtnNeighbor::DtnNeighbor(const std::string& neighborID,
                             NetworkInterface* interface,
                             cSimpleModule* dtn_module,
                             double neighbor_detection_interval,
                             double neighbor_expiration_time,
                             double check_neighbor_expiration_interval,
                             double buffer_expiration_time,
                             double check_buffer_expiration_interval,
                             double neighbor_exchange_interval,
                             double send_packet_interval){
        // timer set up
        this->neighborDetectTimer = new cMessage(NEIGHBOR_DETECT_MSG_NAME.c_str(),NEIGHBOR_DETECT_MSG_KIND);
        this->neighborDetectTimer->setContextPointer(this); // setting context pointer to this
        this->neighborExpireTimer = new cMessage(CHECK_NEIGH_EXPIRE_MSG_NAME.c_str(), CHECK_NEIGH_EXPIRE_MSG_KIND);
        this->neighborExpireTimer->setContextPointer(this); // setting context pointer to this
        this->neighborExchangeTimer = new cMessage(NEIGHBOR_EXCHANGE_MSG_NAME.c_str(), NEIGHBOR_EXCHANGE_MSG_KIND);
        this->neighborExchangeTimer->setContextPointer(this); // setting context pointer
        this->neighborSendPacketTimer = new cMessage(NEIGHBOR_SEND_PACKET_TIMER.c_str(), NEIGHBOR_SEND_PACKET_MSG_KIND);
        this->neighborSendPacketTimer->setContextPointer(this); // setting context pointer


        // parameters set up
        this->neighborID = neighborID;
        this->interface = interface;
        this->dtn_module = dtn_module;
        this->neighbor_detection_interval = neighbor_detection_interval;
        this->neighbor_expiration_time = neighbor_expiration_time;
        this->check_neighbor_expiration_interval = check_neighbor_expiration_interval;
        this->buffer_expiration_time = buffer_expiration_time;
        this->check_buffer_expiration_interval = check_buffer_expiration_interval;
        this->neighbor_exchange_interval = neighbor_exchange_interval;
        this->send_packet_interval = send_packet_interval;

        // states set up
        this->lastSeenTime = simTime();
        state = new DtnNeighborStateDown(); // the first time the dtn is created the neighbor is up
        previousState = nullptr;
    }

    void DtnNeighbor::processEvent(DtnNeighborEventType event){
        this->state->processEvent(this, event);
    }

    std::string DtnNeighbor::getStateString(DtnNeighborStateType state) {
        switch (state) {
            case DtnNeighbor::NEIGHBOR_DOWN_STATE:
                return "NEIGHBOR_DOWN_STATE";
            case DtnNeighbor::NEIGHBOR_UP_STATE:
                return "NEIGHBOR_UP_STATE";
            case DtnNeighbor::NEIGHBOR_TWO_WAY_STATE:
                return "NEIGHBOR_TWO_WAY_STATE";
            default:
                return "UNKNOWN_STATE";
        }
    }

    void DtnNeighbor::neighborChangeState(DtnNeighborState *newState, DtnNeighborState *currentState) {
        EV_INFO << "Changing neighborhood state of " << this->getNeighborID()
                << " from '" << getStateString(currentState->getState())
                << "' to '" << getStateString(newState->getState()) << "'" << std::endl;

        // zhf add code
        if(newState->getState() == DtnNeighbor::DtnNeighborStateType::NEIGHBOR_TWO_WAY_STATE){
            // start the timer
            dtn* dtn_module_tmp = dynamic_cast<dtn*>(this->dtn_module);
            dtn_module_tmp->messageHandler->startTimer(this->neighborSendPacketTimer, this->send_packet_interval);
        }
        if((newState->getState() == DtnNeighbor::DtnNeighborStateType::NEIGHBOR_DOWN_STATE) &&
                (currentState->getState() == DtnNeighbor::DtnNeighborStateType::NEIGHBOR_TWO_WAY_STATE)){
            // cancel the possible send packet timer
            if(this->neighborSendPacketTimer->isScheduled())
            {
                this->dtn_module->cancelEvent(this->neighborSendPacketTimer);
            }
        }

        if (previousState != nullptr) {
            delete previousState;
        }

        state = newState;
        previousState = currentState;
    }

    void DtnNeighbor::sendPacket(Packet* packet) const{
        this->dtn_module->send(packet, "ipOut");
    }

    Packet* DtnNeighbor::createNeighborDetectPacket(const inet::Ipv4Address &multicastAddress, short ttl) const {
        auto *pk = new Packet();
        // set name
        pk->setName(NEIGHBOR_DETECT_PACKET_NAME.c_str());

        // add application packet
        // here we need to create a EpidemicHeader
        const auto& epidemicHeader = makeShared<EpidemicHeader>();
        epidemicHeader->setType(EpidemicPacket::Type::NEIGHBOR_DETECTION_PACKET_TYPE);
        epidemicHeader->setChunkLength(B(100));
        if(this->neighborAck){
            std::cout << "send true neighbor ack" << std::endl;
            epidemicHeader->setNeighborAck(this->neighborAck);
        } else {
            std::cout << "send false neighbor ack" << std::endl;
            epidemicHeader->setNeighborAck(this->neighborAck);
        }
        pk->insertAtBack(epidemicHeader);
        pk->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::dtn); // set packet protocol
        pk->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::ipv4); // next layer protocol
        pk->addTagIfAbsent<InterfaceReq>()->setInterfaceId(this->interface->getInterfaceId());
        pk->addTagIfAbsent<L3AddressReq>()->setDestAddress(multicastAddress);
        pk->addTagIfAbsent<HopLimitReq>()->setHopLimit(ttl);
        return pk;
    }

    void DtnNeighbor::sendNeighborDetectPacket(const Ipv4Address& multicastAddress, short ttl) const {
        this->sendPacket(this->createNeighborDetectPacket(multicastAddress, ttl));
    }

    Packet* DtnNeighbor::createNeighborIdDbPacket(const inet::Ipv4Address &multicastAddress, short ttl) const {
        // dtn_module
        dtn* dtn_module_tmp = check_and_cast<dtn*>(this->dtn_module);
        auto *pk = new Packet();
        // set name
        pk->setName(NEIGHBOR_ID_DB_PACKET_NAME.c_str());
        // add application packet
        // here we need to create a EpidemicHeader
        const auto& epidemicHeader = makeShared<EpidemicHeader>();
        epidemicHeader->setType(EpidemicPacket::Type::NEIGHBOR_ID_DB_PACKET_TYPE);
        epidemicHeader->setChunkLength(B(100));
        epidemicHeader->setMsgIdLength(int(dtn_module_tmp->packetIds.size()));
        for(const auto & packetId : dtn_module_tmp->packetIds){
            epidemicHeader->appendMsgIds(packetId.c_str());
        }
        pk->insertAtBack(epidemicHeader);
        pk->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::dtn); // set packet protocol
        pk->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::ipv4); // next layer protocol
        pk->addTagIfAbsent<InterfaceReq>()->setInterfaceId(this->interface->getInterfaceId());
        pk->addTagIfAbsent<L3AddressReq>()->setDestAddress(multicastAddress);
        pk->addTagIfAbsent<HopLimitReq>()->setHopLimit(ttl);
        return pk;
    }

    void DtnNeighbor::sendNeighborIdDbPacket(const inet::Ipv4Address &multicastAddress, short ttl) const {
        this->sendPacket(this->createNeighborIdDbPacket(multicastAddress, ttl));
    }

    Packet* DtnNeighbor::createNeighborRealPacketRequest(const inet::Ipv4Address &multicastAddress, short ttl) const {
        // dtn_module
        dtn* dtn_module_tmp = check_and_cast<dtn*>(this->dtn_module);
        auto *pk = new Packet();
        // set name
        pk->setName(NEIGHBOR_REAL_PACKET_REQUEST_NAME.c_str());
        // add application packet
        // here we need to create a EpidemicHeader
        const auto& epidemicHeader = makeShared<EpidemicHeader>();
        epidemicHeader->setType(EpidemicPacket::Type::NEIGHBOR_REAL_PACKET_REQUEST_TYPE);
        epidemicHeader->setChunkLength(B(100));
        epidemicHeader->setMsgIdLength(int(this->requestIds.size()));
        for(const auto & packetId : this->requestIds){
            epidemicHeader->appendMsgIds(packetId.c_str());
        }
        pk->insertAtBack(epidemicHeader);
        pk->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::dtn); // set packet protocol
        pk->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::ipv4); // next layer protocol
        pk->addTagIfAbsent<InterfaceReq>()->setInterfaceId(this->interface->getInterfaceId());
        pk->addTagIfAbsent<L3AddressReq>()->setDestAddress(multicastAddress);
        pk->addTagIfAbsent<HopLimitReq>()->setHopLimit(ttl);
        return pk;
    }

    void DtnNeighbor::sendNeighborRealPacketRequest(const inet::Ipv4Address &multicastAddress, short ttl) const {
        this->sendPacket(this->createNeighborRealPacketRequest(multicastAddress, ttl));
    }

    void DtnNeighbor::sendPacketsById(const inet::Ipv4Address &multicastAddress, short ttl) {
        dtn* dtn_module_tmp = check_and_cast<dtn*>(this->dtn_module);
        std::string sendPacketId = "";
        // copy the packet in the buffer and send out the packet
        for(const auto& sendPacketIdTmp : this->sendIds){
            sendPacketId = sendPacketIdTmp;
            break;
        }
        // judge if there is no packet in the buffer
        if(strcmp(sendPacketId.c_str(), "") == 0){
            // not sending packet
        } else {
            std::cout << "send packet by id" << std::endl;
            std::cout << "packet id:" << sendPacketId << std::endl;
            // find in the buffer
            Packet* pk = dtn_module_tmp->packets_buffer[sendPacketId].first->dup();
            // send out the packet
            pk->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::dtn); // set packet protocol
            pk->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::ipv4); // next layer protocol
            pk->addTagIfAbsent<InterfaceReq>()->setInterfaceId(this->interface->getInterfaceId());
            pk->addTagIfAbsent<L3AddressReq>()->setDestAddress(multicastAddress);
            pk->addTagIfAbsent<HopLimitReq>()->setHopLimit(ttl);
            // call send function
            this->sendPacket(pk);
            // remove the sendIds
            this->sendIds.erase(sendPacketId);
        }
    }

}
