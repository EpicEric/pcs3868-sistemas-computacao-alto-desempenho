#include "state.h"

int compareStates(State* state1, State* state2) {
    if (state1->cost < state2->cost) {
        return -1;
    }
    if (state1->cost == state2->cost) {
        return 0;
    }
    return 1;
}
