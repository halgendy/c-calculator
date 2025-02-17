
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack *new_stack() {
	Stack *s = (Stack *)malloc(sizeof(Stack));
	s->capacity = 2;
	// no elements yet
	s->top = -1;
	s->elements = malloc(s->capacity * sizeof(void *));	
	return s;
}

void push(Stack *s, void *element) {
	if (s->top >= s->capacity) {
		s->capacity *= 2;
		s->elements = realloc(s->elements, s->capacity * sizeof(void *));
	}
	s->elements[++s->top] = element;
}

void *pop(Stack *s) {
	if (s->top < 0) return NULL;
	return s->elements[s->top--];
}

void *peek(Stack *s) {
	if (s->top < 0) return NULL;
	return s->elements[s->top];
}

void free_stack(Stack *s) {
	free(s->elements);
	free(s);
}

int stack_length(Stack *s) {
	return s->top + 1;
}
