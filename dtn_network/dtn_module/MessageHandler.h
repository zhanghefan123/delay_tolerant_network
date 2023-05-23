#ifndef __INET_DTN_MESSAGE_HANDLER
#define __INET_DTN_MESSAGE_HANDLER
#include "inet/projects/dtn_network/dtn_module/IMessageHandler.h"
#include "inet/projects/dtn_network/dtn_module/DtnNeighborDetectionHandler.h"
#include "inet/projects/dtn_network/dtn_module/DtnNeighborIdDbHandler.h"
#include "inet/projects/dtn_network/dtn_module/DtnNeighborRequestHandler.h"
#include "inet/projects/dtn_network/dtn_module/DtnRealPacketHandler.h"
namespace inet{
    class MessageHandler{
        // all kinds of packet handler
        public:
            DtnNeighborDetectionHandler *dtnNeighborDetectionHandler;
            DtnNeighborIdDbHandler *dtnNeighborIdDbHandler;
            DtnNeighborRequestHandler *dtnNeighborRequestHandler;
            DtnRealPacketHandler *dtnRealPacketHandler;
            cSimpleModule *containingModule;
        public:
            explicit MessageHandler(cSimpleModule* containingModule);
            virtual ~MessageHandler();
            void messageReceived(cMessage* message); // all kinds of msg
            void handleTimer(cMessage* timer); // handle timer
            void processPacket(Packet * packet) const;
            void startTimer(cMessage* timer, const simtime_t& delay) const;
            void clearTimer(cMessage* timer) const;
    };
}
#endif