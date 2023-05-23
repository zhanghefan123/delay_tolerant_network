#ifndef __INET_DTN_NEIGHBOR_DETECTION_HANDLER_H
#define __INET_DTN_NEIGHBOR_DETECTION_HANDLER_H
#include "inet/projects/dtn_network/dtn_module/IMessageHandler.h"
namespace inet{
       class DtnNeighborDetectionHandler : public IMessageHandler{
         public:
              explicit DtnNeighborDetectionHandler(cSimpleModule* containingModule);
              void processPacket(Packet *packet, DtnNeighbor* neighbor) override;
              cSimpleModule* containingModule;
       };
}
#endif