#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "board.h"
#include <omp.h>

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
	free(array);
	return;
}

int searchIteration(Graph* graph, heap *h, State **visitedNodes, State **foundNodes) {
	int i;
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
	if (currentNode->cost <= visitedNodes[currentNode->node]->cost)
	{
		#pragma omp critical
		{
			visitedNodes[currentNode->node] = currentNode;
		}
		printf("%s DEBUG: Visited %d. Thread: %d\n", debugPrefix, currentNode->node, omp_get_thread_num());
		// If node is on the other side, we found a path
		if (foundNodes[currentNode->node]) {
			printf("%s DEBUG: Completed path.\n", debugPrefix);
			if (graph->visited_from_start == visitedNodes) {
				printPath(graph, currentNode, foundNodes[currentNode->node]);
			} else {
				printPath(graph, foundNodes[currentNode->node], currentNode);
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
	graph->visited_from_start[startNode] = node;

	node = malloc(sizeof(State));
	node->node = endNode;
	node->cost = 0;
	node->prev = endNode;
	heap_insert(h_end, node, node);
	graph->visited_from_end[endNode] = node;

    #pragma omp parallel num_threads(4) shared(graph, i)
	{
	// Iterate while there are still unexplored nodes on both sides
		#pragma omp single
		{
			#pragma omp task 
			{
				while (heap_size(h_start))
				{
					// Iterate on start
					i = searchIteration(graph, h_start, graph->visited_from_start, graph->visited_from_end);
					if (i) break;
				}
			}
			#pragma omp task 
			{
				while (heap_size(h_end))
				{
					// Iterate on end
					i = searchIteration(graph, h_end, graph->visited_from_end, graph->visited_from_start);
					if (i) break;
				}
			}
		}
	}
	if (i) return 0;
	return -1;
}

int main()
{
	int gaps[] = {95};
	int path;
	Graph *graph = createBoard(100);
	createObstacleInRow(graph, 100, 1, gaps, 1);
	printf("\n");

	path = bidirectionalSearch(graph, 0, 9999);
	if (!path)
	{
		printf("Path found!\n");
	}
	else
	{
		printf("No path found.\n");
	}
}
