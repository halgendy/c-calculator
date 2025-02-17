#ifndef STACK_H
#define STACK_H

typedef struct {
    void **elements;
    int top;
    int capacity;
} Stack;

Stack *new_stack();
void push(Stack *s, void *element);
void *pop(Stack *s);
void *peek(Stack *s);
void free_stack(Stack *s);
int stack_length(Stack *s);

#endif

