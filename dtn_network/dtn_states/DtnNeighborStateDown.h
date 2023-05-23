#ifndef __INET_DTN_NEIGHBOR_STATE_DOWN_H
#define __INET_DTN_NEIGHBOR_STATE_DOWN_H
#include "inet/projects/dtn_network/dtn_states/DtnNeighborState.h"
namespace inet{
    class DtnNeighborStateDown : public DtnNeighborState{
        public:
            void processEvent(DtnNeighbor *neighbor, DtnNeighbor::DtnNeighborEventType event) override;
            DtnNeighbor::DtnNeighborStateType getState() const override { return DtnNeighbor::NEIGHBOR_DOWN_STATE;}
    };
}


#endif /* __INET_DTN_NEIGHBOR_STATE_DOWN_H */