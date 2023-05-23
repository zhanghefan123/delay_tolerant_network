#ifndef __INET_DTN_REAL_PACKET_HANDLER_H
#define __INET_DTN_REAL_PACKET_HANDLER_H
#include "inet/projects/dtn_network/dtn_module/IMessageHandler.h"
namespace inet{
    class DtnRealPacketHandler : public IMessageHandler{
    public:
        explicit DtnRealPacketHandler(cSimpleModule* containingModule);
        void processPacket(Packet *packet, DtnNeighbor* neighbor) override;
        cSimpleModule* containingModule;
    };
}
#endif