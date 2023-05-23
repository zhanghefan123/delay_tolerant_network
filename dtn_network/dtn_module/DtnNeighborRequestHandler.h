#ifndef __INET_DTN_NEIGHBOR_REQUEST_HANDLER_H
#define __INET_DTN_NEIGHBOR_REQUEST_HANDLER_H
#include "inet/projects/dtn_network/dtn_module/IMessageHandler.h"
namespace inet{
    class DtnNeighborRequestHandler : public IMessageHandler{
    public:
        explicit DtnNeighborRequestHandler(cSimpleModule* containingModule);
        void processPacket(Packet *packet, DtnNeighbor* neighbor) override;
        cSimpleModule* containingModule;
    };
}
#endif