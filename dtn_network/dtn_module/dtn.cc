#include "inet/projects/dtn_network/dtn_module/dtn.h"
#include "inet/projects/dtn_network/dtn_states/DtnNeighborState.h"
#include "inet/common/IProtocolRegistrationListener.h"
#include "inet/common/Protocol.h"
#include "inet/projects/dtn_network/uuid/uuid4.h"
#include "inet/projects/dtn_network/const_vars/DtnConst.h"
#include "inet/networklayer/common/InterfaceTable.h"
#include "inet/networklayer/ipv4/Ipv4InterfaceData.h"
namespace inet {
    Define_Module(dtn);
    dtn::dtn() = default;

    dtn::~dtn(){
        // we need to delete the packet inside the packet buffer
        for(const auto& packet : this->packets_buffer){
            delete packet.second.first;
        }
        for(const auto& neighbor : this->neighbor_map){
            if(neighbor.second->neighborDetectTimer->isScheduled()){
                cancelEvent(neighbor.second->neighborDetectTimer);
            }
            if(neighbor.second->neighborExpireTimer->isScheduled()){
                cancelEvent(neighbor.second->neighborExpireTimer);
            }
            delete neighbor.second;
        }
        // we need to delete the message handler
        delete this->messageHandler;

    };

    std::string dtn::generateUuid() {
        char buf[UUID4_LEN];
        uuid4_init();
        uuid4_generate(buf);
        return std::string{buf};
    }

    void dtn::initializeNeighbors(){
        // get interface table
        auto* ift = dynamic_cast<InterfaceTable*>(this->getParentModule()->getSubmodule(INTERFACE_TABLE_NAME.c_str()));
        // traverse all the interfaces except loopback interface
        for(auto interface : ift->idToInterface){
            std::string interfaceName = interface->getInterfaceName();
            if(interfaceName.find(LOOPBACK_INTERFACE_NAME) != std::string::npos){
                continue;
            } else {
                // create a new neighbor
                // generate uuid
                std::string uuid = dtn::generateUuid();
                auto* neighbor = new DtnNeighbor(uuid,
                                                 interface,
                                                  this, // why can we past dtn* to cSimpleModule*? because dtn is a subclass of cSimpleModule
                                                  this->neighbor_detection_interval,
                                                  this->neighbor_expiration_time,
                                                  this->check_neighbor_expiration_interval,
                                                  this->buffer_expiration_time,
                                                  this->check_buffer_expiration_interval,
                                                  this->neighbor_exchange_interval);
                // add the neighbor to the neighbor map
                this->neighbor_map[uuid] = neighbor;
            }
        }
    }

    void dtn::allNeighborsInterfaceUp() {
        // traverse all the neighbors
        for(auto neighbor : this->neighbor_map){
            // process event
            neighbor.second->processEvent(DtnNeighbor::DTN_INTERFACE_UP);
        }
    }

    void dtn::allInterfacesJoinMulticastGroups() {
        auto* interfaceTable = dynamic_cast<InterfaceTable*>(this->getParentModule()->getSubmodule(INTERFACE_TABLE_NAME.c_str()));
        for(auto interface : interfaceTable->idToInterface){
            // get the interface name
            std::string interfaceName = interface->getInterfaceName();
            // if the interface name contains loopback, then we skip it
            if(interfaceName.find(LOOPBACK_INTERFACE_NAME) != std::string::npos){
                continue;
            } else {
                // join the multicast group
                auto ipv4Data = interface->getProtocolDataForUpdate<Ipv4InterfaceData>();
                ipv4Data->joinMulticastGroup(Ipv4Address::DTN_NEIGHBOR_DETECTION_MCAST);
            }
        }
    }

    DtnNeighbor* dtn::findNeighborByInterfaceId(int interfaceId) {
        for(const auto& neighbor : this->neighbor_map){
            if(neighbor.second->interface->getInterfaceId() == interfaceId){
                return neighbor.second;
            }
        }
        return nullptr;
    }


    void dtn::handleStartOperation(LifecycleOperation *operation) {
        this->dtn_start_msg = new cMessage(DTN_START_MSG_NAME.c_str());
        scheduleAt(simTime(), this->dtn_start_msg);
        this->check_buffer_expired_timer = new cMessage(CHECK_BUFFER_EXPIRE_MSG_NAME.c_str());
        scheduleAt(simTime(), this->check_buffer_expired_timer);
    }

    void dtn::handleStopOperation(LifecycleOperation *operation) {
    }

    void dtn::handleCrashOperation(LifecycleOperation *operation) {
    }

    void dtn::handleMessageWhenUp(cMessage *msg) {
        if(std::strcmp(msg->getName(), DTN_START_MSG_NAME.c_str()) == 0){
            // then we gonna delete the msg
            delete msg;
            this->dtn_start_msg = nullptr;
            // then we gonna initialize the neighbors
            this->initializeNeighbors();
            // then we gonna start interface up for all the neighbors
            this->allNeighborsInterfaceUp();
            // we gonna let all interface except loopback interface join the multicast group
            this->allInterfacesJoinMulticastGroups();
        } else if (std::strcmp(msg->getName(), CHECK_BUFFER_EXPIRE_MSG_NAME.c_str()) == 0){
            this->checkBufferExpired();
            // print neighbor state
            for(const auto& neighbor : this->neighbor_map){
                std::cout << "neighbor state: " << DtnNeighbor::getStateString(neighbor.second->state->getState()) << endl;
            }
            // we gonna call the buffer check method and restart timer
            scheduleAt(simTime() + this->check_buffer_expiration_interval, this->check_buffer_expired_timer);
        }
        else {
            this->messageHandler->messageReceived(msg);
        }
    }

    void dtn::checkBufferExpired(){
        // traverse the buffer
        for(auto iter = this->packets_buffer.begin(); iter != this->packets_buffer.end(); ){
            if((simTime() - iter->second.second) > this->buffer_expiration_time){
                // then we gonna delete the packet
                delete iter->second.first;
                // then we gonna delete the item
                iter = this->packets_buffer.erase(iter);
            } else {
                iter++;
            }
        }
    }


    void dtn::initialize(int stage) {
        OperationalBase::initialize(stage);
        if(stage == INITSTAGE_LOCAL){
            this->neighbor_detection_interval = par(PAR_NEIGHBOR_DETECTION_INTERVAL.c_str()).doubleValue();
            this->neighbor_expiration_time = par(PAR_NEIGHBOR_EXPIRATION_TIME.c_str()).doubleValue();
            this->check_neighbor_expiration_interval = par(PAR_CHECK_NEIGHBOR_EXPIRATION_INTERVAL.c_str()).doubleValue();
            this->buffer_expiration_time = par(PAR_BUFFER_EXPIRATION_TIME.c_str()).doubleValue();
            this->check_buffer_expiration_interval = par(PAR_CHECK_BUFFER_EXPIRATION_INTERVAL.c_str()).doubleValue();
            this->neighbor_exchange_interval = par(PAR_NEIGHBOR_EXCHANGE_INTERVAL.c_str()).doubleValue();
            this->messageHandler = new MessageHandler(this);
        }
        else if(stage == INITSTAGE_ROUTING_PROTOCOLS){
            registerProtocol(Protocol::dtn, gate("ipOut"), gate("ipIn"));
        }
    }

}
