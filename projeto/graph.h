typedef struct graphStruct {
    int **adj_matrix;
    int V;
    int *visited;
} Graph;

Graph* createGraph(int V);
void addEdge(Graph* graph, int src, int dest, int weight);
void removeEdge(Graph* graph, int src, int dest);
int getWeight(Graph* graph, int src, int dest);
void printGraph(Graph* graph);
