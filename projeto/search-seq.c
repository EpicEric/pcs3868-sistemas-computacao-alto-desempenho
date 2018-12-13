#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "board.h"

#define DEBUG 0
#define min(x, y) ((x < y) ? x : y)

int *pathArray = NULL;
int pathStart = 0;
int pathEnd = 0;

void buildPath(Graph *graph, State *startsideNode, State *endsideNode)
{
	pathArray = malloc(graph->V * sizeof(int));
	pathStart = graph->V / 2;
	pathEnd = pathStart;
	do {
		pathArray[pathStart--] = startsideNode->node;
		startsideNode = graph->visited_from_start[startsideNode->prev];
	} while (startsideNode->prev != startsideNode->node);
	pathArray[pathStart] = startsideNode->node;
	do {
		pathArray[pathEnd++] = endsideNode->node;
		endsideNode = graph->visited_from_end[endsideNode->prev];
	} while (endsideNode->prev != endsideNode->node);
	pathArray[pathEnd] = endsideNode->node;
}

int searchIteration(Graph* graph, heap *h, State **visitedNodes, State **foundNodes) {
	int i, cost;
	State *currentNode, *iterNode;
	char *debugPrefix;
	if (graph->visited_from_start == visitedNodes) {
		debugPrefix = "START";
	} else {
		debugPrefix = "END";
	}
	// Get element currently with less cost from heap
	heap_delmin(h, (void **) &currentNode, (void **) &currentNode);
	// If cost is not higher, then we can iterate this node
	cost = visitedNodes[currentNode->node]->cost;
	if (currentNode->cost <= cost)
	{
		visitedNodes[currentNode->node] = currentNode;
		if (DEBUG) printf("%s DEBUG: Visited %d\n", debugPrefix, currentNode->node);
		// If node is on the other side, we found a path
		if (foundNodes[currentNode->node]) {
			if (DEBUG) printf("%s DEBUG: Completed path.\n", debugPrefix);
			if (graph->visited_from_start == visitedNodes) {
				buildPath(graph, currentNode, foundNodes[currentNode->node]);
			} else {
				buildPath(graph, foundNodes[currentNode->node], currentNode);
			}
			return 1;
		}
		// If node is not on other side, find all neighbors and add to heap
		for (i = 0; i < graph->V; i++) {
			if (i != currentNode->node &&
					graph->adj_matrix[currentNode->node][i] > 0 &&
					!(visitedNodes[i]))
			{
				// Add to list of visited nodes on left side
				iterNode = visitNode(graph, visitedNodes, i, currentNode->node);
				// Insert in heap to iterate later
				heap_insert(h, iterNode, iterNode);
			}
		}
	// Generated node is useless; remove from memory
	} else {
		free(currentNode);
	}
	return 0;
}

void bidirectionalSearch(Graph *graph, int startNode, int endNode)
{
	int size, result, i, maxThreads;
	State *node;
	heap *h_start = malloc(sizeof(heap));
	heap *h_end = malloc(sizeof(heap));
	heap_create(h_start, graph->V, (int (*)(void*, void*)) compareStates);
	heap_create(h_end, graph->V, (int (*)(void*, void*)) compareStates);

	node = malloc(sizeof(State));
	node->node = startNode;
	node->cost = 0;
	node->prev = startNode;
	heap_insert(h_start, node, node);
	graph->visited_from_start[startNode] = node;

	node = malloc(sizeof(State));
	node->node = endNode;
	node->cost = 0;
	node->prev = endNode;
	heap_insert(h_end, node, node);
	graph->visited_from_end[endNode] = node;

	// Iterate while there are still unexplored nodes on both sides
	while (heap_size(h_start) || heap_size(h_end))
	{
		// Iterate on start
		if (searchIteration(graph, h_start, graph->visited_from_start, graph->visited_from_end)) return;
		// Iterate on end
		if (searchIteration(graph, h_end, graph->visited_from_end, graph->visited_from_start)) return;
	}
}

int main()
{
	int gaps[] = {95};
	int i;
	Graph *graph = createBoard(100);
	createObstacleInRow(graph, 100, 1, gaps, 1);

	bidirectionalSearch(graph, 0, 9999);
	if (pathArray)
	{
		printf("Path found!\n");
		for (i = pathStart; i <= pathEnd; i++) {
			printf("%d", pathArray[i]);
			if (i < pathEnd) {
				printf(" -> ");
			}
		}
		printf("\n");
	}
	else
	{
		printf("No path found.\n");
	}
}
