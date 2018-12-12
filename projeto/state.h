typedef struct stateStruct {
    int node;
    int cost;
    int prev;
} State;

int compareStates(State* state1, State* state2);
