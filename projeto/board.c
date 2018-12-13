#include "graph.h"
#include <stdbool.h>
#include <math.h>
#include <stdio.h>

bool isValueInArray(int value, int array[], int length)
{
    int i;
    for(i = 0; i < length; i++)
    {
        if(array[i] == value) {
            return true;
        }           
    }
    return false;
}

Graph *createBoard(int D)
{
    int col, row;
    Graph *graph = createGraph(D * D);
    for (row = 0; row < D; row++)
        for (col = 0; col < D - 1; col++)
            addEdge(graph, row * D + col, row * D + col + 1, 1);

    for (row = 0; row < D - 1 ; row++)
        for (col = 0; col < D; col++)
            addEdge(graph, row * D + col, (row + 1) * D + col, 1);
    

    return graph;
}

Graph *createObstacleInRow(Graph *graph, int D, int row, int gaps[], int length)
{
    int i;

    for (i = 0; i < D; i++)
    {
        if(!isValueInArray(i, gaps, length))
        {
            if(row > 0)
                removeEdge(graph, row * D + i, (row - 1) * D + i);
            if(row < D - 1)
                removeEdge(graph, row * D + i, (row + 1) * D + i);
            if(i > 0)
                removeEdge(graph, row * D + i, row * D + i - 1);
            if(i < D - 1)
                removeEdge(graph, row * D + i, row * D + i + 1);
            }
    }

    return graph;
}
