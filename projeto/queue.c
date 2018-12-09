#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

//Código adaptado de https://www.programiz.com/dsa/graph-bfs
#define MIN_LENGTH 100

Queue *createQueue(int length)
{
	Queue *q = malloc(sizeof(Queue));
	if (length <= 100)
		length = 100;
	q->length = length;
	q->items = malloc(length*sizeof(int));
	q->front = -1;
	q->rear = -1;
	return q;
}

int isEmpty(Queue *q)
{
	if (q->rear == -1)
		return 1;
	else
		return 0;
}

void enqueue(Queue *q, int value)
{
	if (q->rear == q->length - 1)
		printf("\nQueue is Full!!");
	else
	{
		if (q->front == -1)
			q->front = 0;
		q->rear++;
		q->items[q->rear] = value;
	}
}

int dequeue(Queue *q)
{
	int item;
	if (isEmpty(q))
	{
		item = -1;
	}
	else
	{
		item = q->items[q->front];
		q->front++;
		if (q->front > q->rear)
		{
			q->front = q->rear = -1;
		}
	}
	return item;
}

void printQueue(Queue *q)
{
	int i = q->front;

	if (isEmpty(q))
	{
		printf("Queue is empty");
	}
	else
	{
		printf("\nQueue contains \n");
		for (i = q->front; i < q->rear + 1; i++)
		{
			printf("%d ", q->items[i]);
		}
	}
}
