#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "board.h"

void printPath(Graph *graph, State *startsideNode, State *endsideNode)
{
	int start, end, i;
	int *array = malloc(2 * graph->V * sizeof(int));
	start = graph->V;
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
	free(array);
	return;
}

int searchIteration(Graph* graph, heap *h, State **visitedNodes, State **foundNodes) {
	int i;
	State *currentNode, *iterNode;
	// Get element currently with less cost from heap
	heap_delmin(h, (void **) &currentNode, (void **) &currentNode);
	// If cost is not higher, then we can iterate this node
	if (currentNode->cost <= visitedNodes[currentNode->node]->cost)
	{
		visitedNodes[currentNode->node] = currentNode;
		printf("DEBUG: Visited %d\n", currentNode->node);
		// If node is on the other side, we found a path
		if (foundNodes[currentNode->node]) {
			printf("DEBUG: Completed path.\n");
			printPath(graph, foundNodes[currentNode->node], currentNode);
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
				// 
				heap_insert(h, iterNode, iterNode);
			}
		}
	// Generated node is useless; remove from memory
	} else {
		free(currentNode);
	}
	return 0;
}

int bidirectionalSearch(Graph *graph, int startNode, int endNode)
{
	int i;
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
	graph->visited_from_start[node->node] = node;

	node = malloc(sizeof(State));
	node->node = endNode;
	node->cost = 0;
	node->prev = endNode;
	heap_insert(h_end, node, node);
	graph->visited_from_end[node->node] = node;

	// Iterate while there are still unexplored nodes on both sides
	while (heap_size(h_start) && heap_size(h_end))
	{
		// Iterate on start
		i = searchIteration(graph, h_start, graph->visited_from_start, graph->visited_from_end);
		if (i) return 0;
		// Iterate on end
		i = searchIteration(graph, h_end, graph->visited_from_end, graph->visited_from_start);
		if (i) return 0;
	}
	return -1;
}

int main()
{
	int gaps[] = {0};
	int path;
	Graph *graph = createBoard(3);
	createObstacleInRow(graph, 3, 1, gaps, 1);
	printGraph(graph);
	printf("\n");

	path = bidirectionalSearch(graph, 0, 8);
	if (!path)
	{
		printf("Path found!\n");
	}
	else
	{
		printf("No path found.\n");
	}
}
