#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include "stack.h"
#include "queue.h"

const char OPERATORS[6] = {'(', '^', '*', '/', '+', '-'}; 

char **tokenize(const char *input, int *token_count) {
	int max_tokens = 100;
	char **tokens = malloc(max_tokens * sizeof(char *));
	*token_count = 0;
	
	int i = 0;
	int len = strlen(input);

	while (i < len) {
		// skip spaces
		while (i < len && isspace(input[i])) {
			i++;
		}
		if (i >= len) {
			break;
		}

		if (isdigit(input[i])) {
			int start = i;
			while (i < len && isdigit(input[i])) {
				i++;
			}
			int token_len = i - start;
			char *num = malloc(token_len + 1);
			strncpy(num, input + start, token_len);
			num[token_len] = '\0';
			tokens[(*token_count)++] = num;
		} else {
			char *op = malloc(2);
			op[0] = input[i];
			op[1] = '\0';
			tokens[(*token_count)++] = op;
			i++;
		}
	}

	return tokens;
}

int op_precedence(char op) {
        switch (op) {
                case '^': return 3;
                case '*': case '/': return 2;
                case '+': case '-': return 1;
                default: return 0;
        }
}

Queue *eval_yard(int token_count, char *tokens[]) {
        Queue *output = new_queue();
        Stack *op_stack = new_stack();

        for (int i = 0; i < token_count; i++) {
        	char *next = tokens[i];
        	
		// save digit for later
		if (isdigit(next[0])) {
			enqueue(output, strdup(next));
		// save ( till we find its match
		} else if (*next == '(') {
			push(op_stack, strdup(next));
		// order operations between ()
		} else if (*next == ')') {
			for (;;) {
				char *op = (char *)pop(op_stack);

				if (*op == '(') {
					free(op);
					break;
				}
				// take out operator (know its not ())
				enqueue(output, op);
			}
		// otherwise operator to do
		} else {
			for (;;) {
				if (stack_length(op_stack) == 0) break;

				char *head = (char *)peek(op_stack);
				if (op_precedence(*head) > op_precedence(*next)) {
					char *popped = (char *)pop(op_stack);
					enqueue(output, popped);
				} else {
					break;
				}
			}
			
			// now push current op to op stack
			push(op_stack, strdup(next));
		}
	}

	// add on any remaining operators
	while (stack_length(op_stack) > 0) {
		char *popped = (char *)pop(op_stack);
		enqueue(output, popped);
	}

	printf("reverse polish output\n");
	//char *token;
        //	while ((token = dequeue(output)) != NULL) {
        //	printf("%s ", token);
	// free(token);
        //	}
	//printf("\n");

	printf("HELLO\n");
        free_stack(op_stack);
	//free_queue(output);
        
	printf("HERE\n");
	return output;
}

int do_op(int a, char op, int b) {

    switch (op) {
        case '^':
            return a * b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '+':
            return a + b;
        case '-':
            return a - b;
	default: 
            printf("error: not an operator");
	    return 1;
    }
}

int eval_polish(Queue *polish_queue) {
	Stack *operand_stack = new_stack();
        char *token;

	while ((token = dequeue(polish_queue)) != NULL) {

		if (isdigit(token[0])) {
			push(operand_stack, strdup(token));
		} else {
			char *right_char = (char *)pop(operand_stack);
			char *left_char = (char *)pop(operand_stack);
			int right = atoi(right_char);
			int left = atoi(left_char);
			int result = do_op(left, token[0], right);
		
			free(right_char);
			free(left_char);
			free(token);

			char result_str[12];
			sprintf(result_str, "%d", result);
			push(operand_stack, strdup(result_str));
		}
	}
	
	printf("OK BUDDY\n");	

	char *final_str = (char *)pop(operand_stack);
	assert(final_str != NULL);
	int final_result = atoi(final_str);
	free(final_str);
	free_stack(operand_stack);
	
	printf("NO WAY\n");

	return final_result;
}

int main(int argc, char *argv[]) {

	// merge args into one string
	char buffer[256] = "";
	for (int i = 1; i < argc; i++) {
		strcat(buffer,argv[i]);
	}

	int token_count;
	char **tokens = tokenize(buffer, &token_count);

        Queue *polish = eval_yard(token_count, tokens);
        printf("makes it back here\n");
	int calc_result = eval_polish(polish);
        printf("ANSWER: %d\n", calc_result);
	return 0;
        // return calculated_result;
}
