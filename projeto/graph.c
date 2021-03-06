#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include <omp.h>

Graph *createGraph(int V)
{
	int i, j;

	Graph *graph = (Graph *)malloc(sizeof(Graph));
	graph->V = V;
	graph->visited_from_start = malloc(V * sizeof(State *));
	graph->visited_from_end = malloc(V * sizeof(State *));
	graph->adj_matrix = malloc(V * sizeof(int *));
	for (i = 0; i < V; i++)
	{
		graph->adj_matrix[i] = malloc(V * sizeof(int));
		graph->visited_from_start[i] = NULL;
		graph->visited_from_end[i] = NULL;
		for (j = 0; j < V; j++)
		{
			graph->adj_matrix[i][j] = 0;
		}
	}

	return graph;
}

void printGraph(Graph *graph)
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

void addEdge(Graph *graph, int src, int dest, int weight)
{
	graph->adj_matrix[src][dest] = weight;
	graph->adj_matrix[dest][src] = weight;
}

void removeEdge(Graph *graph, int src, int dest)
{
	graph->adj_matrix[src][dest] = 0;
	graph->adj_matrix[dest][src] = 0;
}

int getWeight(Graph *graph, int src, int dest)
{
	return graph->adj_matrix[src][dest];
}

State *visitNode(Graph *graph, State **visitList, int node, int src)
{
	State *state = malloc(sizeof(State));
	state->node = node;
	state->prev = src;
	state->cost = visitList[src]->cost + getWeight(graph, src, node);
	if (!visitList[node] || visitList[node]->cost > state->cost) {
		#pragma omp critical
    	{
			visitList[node] = state;
		}
	} else {
		free(state);
		state = visitList[node];
	}
	return state;
}
