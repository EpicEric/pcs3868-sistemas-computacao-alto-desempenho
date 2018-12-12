#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "heap.h"

void printPath(Graph *graph, State *startsideNode, State *endsideNode)
{
	int start, end, i;
	int *array = malloc(graph->V * sizeof(int));
	start = graph->V / 2;
	end = start;
	do {
		array[start--] = startsideNode->node;
		startsideNode = graph->visited_from_start[startsideNode->prev];
	} while (startsideNode->prev != startsideNode->node);
	array[start] = startsideNode->node;
	do {
		array[end++] = endsideNode->node;
		endsideNode = graph->visited_from_end[endsideNode->prev];
	} while (endsideNode->prev != endsideNode->node);
	array[end] = endsideNode->node;
	for (i = start; i <= end; i++) {
		printf("%d", array[i]);
		if (i < end) {
			printf(" -> ");
		}
	}
	printf("\n");
	return;
}

int bidirectionalSearch(Graph *graph, int startNode, int endNode)
{
	int i;
	State *currentNode, *iterNode;
	heap *h_start = malloc(sizeof(heap));
	heap *h_end = malloc(sizeof(heap));
	heap_create(h_start, graph->V, (int (*)(void*, void*)) compareStates);
	heap_create(h_end, graph->V, (int (*)(void*, void*)) compareStates);

	currentNode = malloc(sizeof(State));
	currentNode->node = startNode;
	currentNode->cost = 0;
	currentNode->prev = startNode;
	heap_insert(h_start, currentNode, currentNode);
	graph->visited_from_start[currentNode->node] = currentNode;

	currentNode = malloc(sizeof(State));
	currentNode->node = endNode;
	currentNode->cost = 0;
	currentNode->prev = endNode;
	heap_insert(h_end, currentNode, currentNode);
	graph->visited_from_end[currentNode->node] = currentNode;

	while (heap_size(h_start) && heap_size(h_end))
	{
		// Iterate on start
		heap_delmin(h_start, (void**) &currentNode, (void**) &currentNode);
		if (currentNode->cost <= graph->visited_from_start[currentNode->node]->cost)
		{
			graph->visited_from_start[currentNode->node] = currentNode;
			printf("DEBUG START: Visited %d\n", currentNode->node);
			if (graph->visited_from_end[currentNode->node]) {
				printf("DEBUG START: Completed path.\n");
				printPath(graph, currentNode, graph->visited_from_end[currentNode->node]);
				return 0;
			}
			for (i = 0; i < graph->V; i++) {
				if (i != currentNode->node &&
				    graph->adj_matrix[currentNode->node][i] > 0 &&
						!(graph->visited_from_start[i]))
				{
					iterNode = visitNodeFromStart(graph, i, currentNode->node);
					heap_insert(h_start, iterNode, iterNode);
				}
			}
		}
		// Iterate on end
		heap_delmin(h_end, (void **) &currentNode, (void **) &currentNode);
		if (currentNode->cost <= graph->visited_from_end[currentNode->node]->cost)
		{
			graph->visited_from_end[currentNode->node] = currentNode;
			printf("DEBUG END: Visited %d\n", currentNode->node);
			if (graph->visited_from_start[currentNode->node]) {
				printf("DEBUG END: Completed path.\n");
				printPath(graph, graph->visited_from_start[currentNode->node], currentNode);
				return 0;
			}
			for (i = 0; i < graph->V; i++) {
				if (i != currentNode->node &&
				    graph->adj_matrix[currentNode->node][i] > 0 &&
						!(graph->visited_from_end[i]))
				{
					iterNode = visitNodeFromEnd(graph, i, currentNode->node);
					heap_insert(h_end, iterNode, iterNode);
				}
			}
		}
	}
	return -1;
}

int main()
{
	int path;
	Graph *graph = createGraph(6);
	addEdge(graph, 0, 1, 1);
	addEdge(graph, 0, 5, 1);
	addEdge(graph, 1, 4, 1);
	addEdge(graph, 2, 3, 1);
	addEdge(graph, 3, 4, 1);
	printGraph(graph);

	path = bidirectionalSearch(graph, 0, 3);
	if (!path)
	{
		printf("Path found!\n");
	}
	else
	{
		printf("No path found.\n");
	}
}
