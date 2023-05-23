#ifndef __INET_DTN_NEIGHBOR_STATE_TWO_WAY_H
#define __INET_DTN_NEIGHBOR_STATE_TWO_WAY_H
#include "inet/projects/dtn_network/dtn_states/DtnNeighborState.h"
namespace inet{
    class DtnNeighborStateTwoWay : public DtnNeighborState{
        public:
            void processEvent(DtnNeighbor *neighbor, DtnNeighbor::DtnNeighborEventType event) override;
            DtnNeighbor::DtnNeighborStateType getState() const override { return DtnNeighbor::NEIGHBOR_TWO_WAY_STATE;}
    };
}
#endif // ifndef __INET_DTN_NEIGHBOR_STATE_H