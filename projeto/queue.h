typedef struct queueStruct {
    int *items;
    int length;
    int front;
    int rear;
} Queue;

Queue* createQueue();
void enqueue(Queue* q, int);
int dequeue(Queue* q);
void display(Queue* q);
int isEmpty(Queue* q);
void printQueue(Queue* q);
