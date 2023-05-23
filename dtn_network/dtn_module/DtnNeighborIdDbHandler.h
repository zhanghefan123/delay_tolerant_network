#ifndef __INET_DTN_NEIGHBOR_ID_DB_HANDLER_H
#define __INET_DTN_NEIGHBOR_ID_DB_HANDLER_H
#include "inet/projects/dtn_network/dtn_module/IMessageHandler.h"
namespace inet{
    class DtnNeighborIdDbHandler : public IMessageHandler{
        public:
            explicit DtnNeighborIdDbHandler(cSimpleModule* containingModule);
            void processPacket(Packet *packet, DtnNeighbor* neighbor) override;
            cSimpleModule* containingModule;
    };
}
#endif