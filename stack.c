
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack *new_stack() {
	Stack *s = (Stack *)malloc(sizeof(Stack));
	s->capacity = 2;
	// no elements yet
	s->top = -1;
	s->elements = (char *)malloc(s->capacity * sizeof(char));	
}

void push(Stack *s, char element) {
	if (s->top >= s->capacity) {
		s->capacity *= 2;
		s->elements = (char *)realloc(s->elements, s->capacity * sizeof(char));
	}
	s->elements[++s->top] = element;
}

char pop(Stack *s) {
	if (s->top < 0) return '\0';
	return s->elements[s->top--];
}

char peek(Stack *s) {
	if (s->top < 0) return '\0';
	return s->elements[s->top];
}

void free_stack(Stack *s) {
	free(s->elements);
}

int stack_length(Stack *s) {
	return s->top + 1;
}
