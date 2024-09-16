#ifndef STACK_H
#define STACK_H

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
