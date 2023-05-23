#ifndef __INET_DTN_NEIGHBOR_STATE_H
#define __INET_DTN_NEIGHBOR_STATE_H
#include "inet/projects/dtn_network/dtn_neighbors/DtnNeighbor.h"
namespace inet{

    class DtnNeighborState{
    public:
        void changeState(DtnNeighbor* neighbor, DtnNeighborState *newState, DtnNeighborState *currentState);
        virtual ~DtnNeighborState() = default;
        virtual void processEvent(DtnNeighbor *neighbor, DtnNeighbor::DtnNeighborEventType event) = 0;
        virtual DtnNeighbor::DtnNeighborStateType getState() const = 0;
    };
}
#endif
