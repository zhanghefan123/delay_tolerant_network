#include "inet/projects/dtn_network/dtn_states/DtnNeighborStateTwoWay.h"
#include "inet/projects/dtn_network/dtn_states/DtnNeighborStateDown.h"
#include "inet/projects/dtn_network/dtn_module/dtn.h"
namespace inet{
    void DtnNeighborStateTwoWay::processEvent(inet::DtnNeighbor *neighbor, DtnNeighbor::DtnNeighborEventType event) {
        switch(event){
            case DtnNeighbor::NEIGHBOR_DETECT_TIMER_RECEIVED:
            {
                EV_INFO << "NEIGHBOR_DETECT_TIMER" << std::endl;
                neighbor->sendNeighborDetectPacket(Ipv4Address::DTN_NEIGHBOR_DETECTION_MCAST, 1);
                // restart the timer to send neighbor detect packet
                dtn* dtn_module = dynamic_cast<dtn*>(neighbor->dtn_module);
                dtn_module->messageHandler->startTimer(neighbor->neighborDetectTimer, neighbor->neighbor_detection_interval);
                break;
            }
            case DtnNeighbor::NEIGHBOR_EXPIRE_TIMER_RECEIVED:
            {
                // we gonna test if the neighbor is still alive
                // here we need to check if neighbor long time no seen
                if(((simTime())-neighbor->lastSeenTime) > neighbor->neighbor_expiration_time){
                    // change the neighbor state from up to down
                    std::cout << "(expired) time period since last seen: " << (simTime()) - neighbor->lastSeenTime << " s" << std::endl;
                    neighbor->neighborAck = false;
                    this->changeState(neighbor, new DtnNeighborStateDown(), this);
                    dtn* dtn_module = dynamic_cast<dtn*>(neighbor->dtn_module);
                    dtn_module->messageHandler->startTimer(neighbor->neighborExpireTimer, neighbor->check_neighbor_expiration_interval);
                } else {
                    std::cout << "(not expired) time period since last seen: " << (simTime()) - neighbor->lastSeenTime << " s" << std::endl;
                    // restart the timer to send neighbor expire check timer
                    dtn* dtn_module = dynamic_cast<dtn*>(neighbor->dtn_module);
                    dtn_module->messageHandler->startTimer(neighbor->neighborExpireTimer, neighbor->check_neighbor_expiration_interval);
                }
                break;
            }
            case DtnNeighbor::NEIGHBOR_DETECT_PACKET_RECEIVED:
            {
                // we do nothing here
                break;
            }
            case DtnNeighbor::NEIGHBOR_DETECT_PACKET_TWO_WAY_RECEIVED:
            {
                // we do nothing here
                std::cout << "case called" << std::endl;
                break;
            }
            case DtnNeighbor::NEIGHBOR_START_EXCHANGE_MSG:
            {
                // start exchange msg
                dtn* dtn_module = dynamic_cast<dtn*>(neighbor->dtn_module);
                if(!dtn_module->packetIds.empty()){
                    std::cout << "start sending neighbor id db packet" << std::endl;
                    // send ids msg
                    neighbor->sendNeighborIdDbPacket(Ipv4Address::DTN_NEIGHBOR_DETECTION_MCAST, 1);
                } else {
                    std::cout << "not sending neighbor id db packet because packetIds is empty" << std::endl;
                }
                // we should start the timer prepare for next sending neighbor start exchange msg
                dtn_module->messageHandler->startTimer(neighbor->neighborExchangeTimer, neighbor->neighbor_exchange_interval);
                break;
            }
            case DtnNeighbor::NEIGHBOR_SEND_REQUEST_IDS:
            {
                // send request ids
                if(!neighbor->requestIds.empty()){
                    std::cout << neighbor->dtn_module->getFullPath() << " send request ids" << std::endl;
                    neighbor->sendNeighborRealPacketRequest(Ipv4Address::DTN_NEIGHBOR_DETECTION_MCAST, 1);
                } else {
                    std::cout << " not send request ids because requestIds is empty" << std::endl;
                }
                break;
            }
            case DtnNeighbor::NEIGHBOR_SEND_REQUEST_PACKETS:
            {
                dtn* dtn_module = dynamic_cast<dtn*>(neighbor->dtn_module);
                // send neighbor request packets
                neighbor->sendPacketsById(Ipv4Address::DTN_NEIGHBOR_DETECTION_MCAST, 1);
            }
        }
    }
}