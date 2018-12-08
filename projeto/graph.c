#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

struct Graph *createGraph(int V)
{
	int i, j;

	struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
	graph->V = V;
	graph->visited = malloc(V * sizeof(int));
	graph->adj_matrix = malloc(V * sizeof(int *));
	for (i = 0; i < V; i++)
	{
		graph->adj_matrix[i] = malloc(V * sizeof(int));
		for (j = 0; j < V; j++)
		{
			graph->adj_matrix[i][j] = 0;
		}
	}

	return graph;
}

void printGraph(struct Graph *graph)
{
	int i, j;

	for (i = 0; i < graph->V; i++)
	{
		for (j = 0; j < graph->V; j++)
		{
			printf("%d ", graph->adj_matrix[i][j]);
		}
		printf("\n");
	}
}

void addEdge(struct Graph *graph, int src, int dest, int weight)
{
	graph->adj_matrix[src][dest] = weight;
	graph->adj_matrix[dest][src] = weight;
}

void removeEdge(struct Graph *graph, int src, int dest)
{
	graph->adj_matrix[src][dest] = 0;
	graph->adj_matrix[dest][src] = 0;
}

int getWeight(struct Graph *graph, int src, int dest)
{
	return graph->adj_matrix[src][dest];
}

void visitNode(struct Graph *graph, int node, int src)
{
	graph->visited[node] = src;
}

int whoVisitNode(struct Graph *graph, int node)
{
	return graph->visited[node];
}
