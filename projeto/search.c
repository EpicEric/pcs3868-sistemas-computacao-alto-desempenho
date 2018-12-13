#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "board.h"
#include <omp.h>

#define NTHREADS 8
#define DEBUG 0
#define min(x, y) ((x < y) ? x : y)

int *pathArray = NULL;
int pathStart = 0;
int pathEnd = 0;

void buildPath(Graph *graph, State *startsideNode, State *endsideNode)
{
	int *tempPathArray;
	#pragma omp critical
	{
		tempPathArray = pathArray;
		if (!tempPathArray) {
			pathArray = malloc(graph->V * sizeof(int));
		}
	}
	if (tempPathArray) {
		if (DEBUG) printf("DEBUG: Path already built; skipping\n");
		return;
	}
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

void searchIteration(Graph* graph, heap *h, State **visitedNodes, State **foundNodes, int thread_num) {
	int i;
	State *currentNode, *iterNode;
	char *debugPrefix;
	if (graph->visited_from_start == visitedNodes) {
		debugPrefix = "START";
	} else {
		debugPrefix = "END";
	}
	// Get element currently with less cost from heap
	#pragma omp critical
	{
		heap_delmin(h, (void **) &currentNode, (void **) &currentNode);
	}
	iterNode = NULL;
	// If cost is not higher, then we can iterate this node
	#pragma omp critical
	{
		iterNode = visitedNodes[currentNode->node];
		if (currentNode->cost <= iterNode->cost) {
			visitedNodes[currentNode->node] = currentNode;
			// Remove old node from memory
			if (iterNode != currentNode) free(iterNode);
			iterNode = NULL;
		}
	}
	if (!iterNode)
	{
		if (DEBUG) printf("%s DEBUG: Visited %d. Thread: %d\n", debugPrefix, currentNode->node, thread_num);
		// If node is on the other side, we found a path
		if (foundNodes[currentNode->node]) {
			if (DEBUG) printf("%s DEBUG: Completed path.\n", debugPrefix);
			if (graph->visited_from_start == visitedNodes) {
				buildPath(graph, currentNode, foundNodes[currentNode->node]);
			} else {
				buildPath(graph, foundNodes[currentNode->node], currentNode);
			}
			return;
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
				#pragma omp critical
				{
					heap_insert(h, iterNode, iterNode);
				}
			}
		}
	// Generated node is useless; remove from memory
	} else {
		free(currentNode);
	}
}

void bidirectionalSearch(Graph *graph, int startNode, int endNode)
{
	int size, maxThreads;
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

	omp_set_nested(1);

  #pragma omp parallel num_threads(2)
	{
		// Iterate while there are still unexplored nodes on both sides
		if (omp_get_thread_num() == 0)
		{
			// Iterate on start
			while (1) {
				size = heap_size(h_start);
				if (!size) break;
				maxThreads = min(size, NTHREADS >> 1);
				#pragma omp parallel num_threads(maxThreads)
				{
					searchIteration(graph, h_start, graph->visited_from_start, graph->visited_from_end, omp_get_thread_num());
				}
				if (pathArray) break;
			}
		} else {
			// Iterate on end
			while (1) {
				size = heap_size(h_end);
				if (!size) break;
				maxThreads = min(size, NTHREADS - (NTHREADS >> 1));
				#pragma omp parallel num_threads(maxThreads)
				{
					searchIteration(graph, h_end, graph->visited_from_end, graph->visited_from_start, omp_get_thread_num() + (NTHREADS >> 1));
				}
				if (pathArray) break;
			}
		}
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
