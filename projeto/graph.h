#include "state.h"

typedef struct graphStruct {
    int **adj_matrix;
    int V;
    State **visited_from_start;
    State **visited_from_end;
} Graph;

Graph* createGraph(int V);
void printGraph(Graph *graph);
void addEdge(Graph* graph, int src, int dest, int weight);
void removeEdge(Graph* graph, int src, int dest);
int getWeight(Graph* graph, int src, int dest);
State *visitNode(Graph *graph, State **visitList, int node, int src);
