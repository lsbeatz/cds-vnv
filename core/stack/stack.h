#ifndef STACK_H
#define STACK_H

/*
 * struct stack: Represents a dynamic stack data structure.
 * Members:
 *   - base: Pointer to the array that holds the stack elements.
 *   - top: Index of the top element in the stack (-1 when the stack is empty).
 *   - capacity: The current maximum capacity of the stack (in terms of elements).
 */
struct stack {
	int *base;
	int	 top;
	int	 capacity;
};

struct stack *stack_create(void);
int stack_destroy(struct stack *s);

int stack_push(struct stack *s, int value);
int stack_pop(struct stack *s);
int stack_peek(struct stack *s);

int stack_size(struct stack *s);
int stack_capacity(struct stack *s);

#endif /* STACK_H */
