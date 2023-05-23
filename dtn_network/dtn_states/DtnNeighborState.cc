#include "inet/projects/dtn_network/dtn_states/DtnNeighborState.h"
namespace inet{
    void DtnNeighborState::changeState(DtnNeighbor* neighbor, DtnNeighborState *newState, DtnNeighborState *currentState){
        neighbor->neighborChangeState(newState, currentState);
    }
}