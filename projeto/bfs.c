#include <stdio.h>
#include "graph.h"
#include "queue.h"

void bfs(Graph *graph, int startNode)
{
	int i;
	Queue *q = createQueue(0);
	enqueue(q, startNode);

	while (!isEmpty(q))
	{
		printQueue(q);
		int currentNode = dequeue(q);

		graph->visited[currentNode] = 1;
		printf("Visited %d\n", currentNode);
		for (i = 0; i < graph->V; i++)
		{
			if (i != currentNode)
			{
				if (graph->adj_matrix[currentNode][i] > 0 && graph->visited[i] == 0)
				{
					enqueue(q, i);
				}
			}
		}
	}
}

int main()
{
	Graph *graph = createGraph(6);
	addEdge(graph, 0, 1, 1);
	addEdge(graph, 0, 2, 1);
	addEdge(graph, 0, 3, 1);
	addEdge(graph, 3, 4, 1);
	printGraph(graph);

	bfs(graph, 0);
}
