#ifndef __INET_DTN_NEIGHBOR_H
#define __INET_DTN_NEIGHBOR_H
#include "inet/networklayer/contract/ipv4/Ipv4Address.h"
#include "inet/projects/dtn_network/const_vars/DtnConst.h"
#include "inet/networklayer/common/NetworkInterface.h"
namespace inet{
    // inside DtnNeighbor we need to use DtnNeighborState
    // inside DtnNeighborState we need to use DtnNeighbor
    // to avoid circular dependency, we use forward declaration
    class DtnNeighborState;
    class DtnNeighbor{
        public:
            // we need to define the last time receive neighbor detection from neighbor
            simtime_t lastSeenTime;
            std::string neighborID;
            Ipv4Address neighborAddress;
            NetworkInterface* interface;
            cSimpleModule* dtn_module;
            DtnNeighborState *state; // store current state
            DtnNeighborState *previousState; // store previous state
            bool neighborAck = false; // have already received detection packet from neighbor
            std::set<std::string> requestIds; // about to request ids
            std::set<std::string> sendIds; // about to send ids
            // event type
            enum DtnNeighborEventType {
                DTN_INTERFACE_UP = 0, // interface up and we need to start the hello timer
                NEIGHBOR_DETECT_TIMER_RECEIVED = 1, // neighbor detect timer
                NEIGHBOR_EXPIRE_TIMER_RECEIVED = 2, // neighbor expire timer
                NEIGHBOR_DETECT_PACKET_RECEIVED = 3, // neighbor detect packet received
                NEIGHBOR_DETECT_PACKET_TWO_WAY_RECEIVED = 4, // neighbor detect packet two way received
                NEIGHBOR_START_EXCHANGE_MSG = 5,
                NEIGHBOR_SEND_REQUEST_IDS = 6,
                NEIGHBOR_SEND_REQUEST_PACKETS = 7,
            };
            enum DtnNeighborStateType {
                NEIGHBOR_DOWN_STATE = 0,
                NEIGHBOR_UP_STATE = 1,
                NEIGHBOR_TWO_WAY_STATE = 2,
            }; // the state that neighbor may in
            enum DtnNeighborMsgKind {
                NEIGHBOR_DETECT_MSG_KIND = 0,
                CHECK_NEIGH_EXPIRE_MSG_KIND = 1,
                NEIGHBOR_EXCHANGE_MSG_KIND = 2,
            };
            virtual ~DtnNeighbor(); // destructor
            DtnNeighbor(const std::string& id,
                                 NetworkInterface* interface,
                                 cSimpleModule* dtn_module,
                                 double neighbor_detection_interval,
                                 double neighbor_expiration_time,
                                 double check_neighbor_expiration_interval,
                                 double buffer_expiration_time,
                                 double check_buffer_expiration_interval,
                                 double neighbor_exchange_interval); // constructor
            void processEvent(DtnNeighborEventType event); // process event
            void neighborChangeState(DtnNeighborState* newState, DtnNeighborState* currentState); // change state
            void setNeighborID(const std::string& id) { neighborID = id; } // set neighbor id
            std::string getNeighborID() const { return neighborID; } // get neighbor id
            static std::string getStateString(DtnNeighborStateType state) ; // used to convert state to string
        public:
            // timer settings
            // neighbor detection timer
            cMessage* neighborDetectTimer = nullptr; // this var will be deleted
            // check neighbor expireTimer
            cMessage* neighborExpireTimer = nullptr; // this var will be deleted
            // neighbor exchange timer
            cMessage* neighborExchangeTimer = nullptr; // this var will be deleted
        public:
            // time settings
            // neighbor detection time
            double neighbor_detection_interval;
            double neighbor_expiration_time;
            double check_neighbor_expiration_interval;
            double buffer_expiration_time;
            double check_buffer_expiration_interval;
            double neighbor_exchange_interval;

            // packet sender
        public:
            void sendPacket(Packet* packet) const;
            Packet* createNeighborDetectPacket(const Ipv4Address& multicastAddress, short ttl) const;
            void sendNeighborDetectPacket(const Ipv4Address& multicastAddress, short ttl) const;
            Packet* createNeighborIdDbPacket(const Ipv4Address& multicastAddress, short ttl) const;
            void sendNeighborIdDbPacket(const Ipv4Address& multicastAddress, short ttl) const;
            Packet* createNeighborRealPacketRequest(const Ipv4Address& multicastAddress, short ttl) const;
            void sendNeighborRealPacketRequest(const Ipv4Address& multicastAddress, short ttl) const;
            void sendPacketsById(const inet::Ipv4Address &multicastAddress, short ttl);
    };
}

#endif
