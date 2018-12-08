struct Graph {
    int **adj_matrix;
    int V;
    int *visited;
};

struct Graph* createGraph(int V);
void addEdge(struct Graph* graph, int src, int dest, int weight);
void removeEdge(struct Graph* graph, int src, int dest);
int getWeight(struct Graph* graph, int src, int dest);
void printGraph(struct Graph* graph);
