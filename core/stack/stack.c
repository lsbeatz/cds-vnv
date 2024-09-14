#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include <sizes.h>

#include "stack.h"

#define MIN_STACK_CAPACITY (SZ_64 / sizeof(int))
#define MAX_STACK_CAPACITY (SZ_4K / sizeof(int))

static inline bool stack_is_full(struct stack *s)
{
	return s->top == s->capacity;
}

static inline bool stack_is_empty(struct stack *s)
{
	return s->top == -1;
}

static int stack_grow(struct stack *s)
{
	if (s == NULL) {
		return -EINVAL;
	}

	if (s->capacity >= MAX_STACK_CAPACITY) {
		return -ENOMEM;
	}

	s->base = realloc(s->base, (s->capacity << 1) * sizeof(int));
	if (s->base == NULL) {
		return -ENOMEM;
	}

	s->capacity = (s->capacity << 1);

	return 0;
}

int stack_create(struct stack *s)
{
	s = (struct stack *)malloc(sizeof(struct stack));
	if (s == NULL) {
		return -ENOMEM;
	}

	s->base = (int *)malloc(MIN_STACK_CAPACITY * sizeof(int));
	if (s->base == NULL) {
		return -ENOMEM;
	}

	s->top		= -1;
	s->capacity = MIN_STACK_CAPACITY;

	return 0;
}

int stack_destroy(struct stack *s)
{
	return 0;
}

int stack_push(struct stack *s, int value)
{
	return 0;
}

int stack_pop(struct stack *s)
{
	return 0;
}

int stack_peek(struct stack *s)
{
	return 0;
}

int stack_size(struct stack *s)
{
	return 0;
}

int stack_capacity(struct stack *s)
{
	return 0;
}
