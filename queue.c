
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

Queue *new_queue() {
	Queue *q = (Queue *)malloc(sizeof(Queue));
	q->front = q->back = NULL;
	return q;
}

void enqueue(Queue *q, const char *value) {
	Node *new_node = (Node *)malloc(sizeof(Node));
	new_node->data = strdup(value);
	new_node->next = NULL;

	if (q->back == NULL) {
		q->front = q->back = new_node;
	} else {
		q->back->next = new_node;
		q->back = new_node;
	}
}

char *dequeue(Queue *q) {
	if (q->front == NULL) return NULL;

	Node *temp = q->front;
	char *data = temp->data;

	//printf("Dequeuing: %s\n", data);

	q->front = q->front->next;
	if (q->front == NULL) q->back = NULL;

	free(temp);
	return data;
}

void free_queue(Queue *q) {
	while (q->front != NULL) {
		free(dequeue(q));
	}
	free(q);
}
