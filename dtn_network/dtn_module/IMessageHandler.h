#ifndef __INET_DTN_IMESSAGE_HANDLER
#define __INET_DTN_IMESSAGE_HANDLER
#include "inet/common/packet/Packet.h"
#include "inet/projects/dtn_network/dtn_neighbors/DtnNeighbor.h"
namespace inet{
    class IMessageHandler{
    public:
        virtual void processPacket(Packet * packet, DtnNeighbor* neighbor) = 0;
    };
}
#endif