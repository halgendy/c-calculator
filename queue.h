#ifndef QUEUE_H
#define QUEUE_H

typedef struct Node {
    char *data;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *back;
} Queue;

Queue *new_queue();
void enqueue(Queue *q, const char *value);
char *dequeue(Queue *q);
void free_queue(Queue *q);

#endif

