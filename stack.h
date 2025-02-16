#ifndef STACK_H
#define STACK_H

typedef struct {
    char *elements;
    int top;
    int capacity;
} Stack;

Stack *new_stack();
void push(Stack *s, char item);
char pop(Stack *s);
char peek(Stack *s);
void free_stack(Stack *s);
int stack_length(Stack *s);

#endif

