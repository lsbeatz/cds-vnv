#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include <sizes.h>

#include "stack.h"

#define MIN_STACK_CAPACITY (SZ_64 / sizeof(int))
#define MAX_STACK_CAPACITY (SZ_4K / sizeof(int))

/*
 * Description: Checks if the stack is full.
 * Parameters:
 *   - s: Pointer to the stack structure.
 * Return Value:
 *   - true if the stack is full, otherwise false.
 */
static inline bool stack_is_full(struct stack *s)
{
	return s->top + 1 == s->capacity;
}

/*
 * Description: Checks if the stack is empty.
 * Parameters:
 *   - s: Pointer to the stack structure.
 * Return Value:
 *   - true if the stack is empty, otherwise false.
 */
static inline bool stack_is_empty(struct stack *s)
{
	return s->top == -1;
}

/*
 * Description: Grows the stack size by doubling its current capacity.
 * Parameters:
 *   - s: Pointer to the stack structure.
 * Return Value:
 *   - 0 on success.
 *   - -EINVAL if the stack is NULL.
 *   - -ENOMEM if memory allocation fails or the capacity exceeds the limit.
 */
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

/*
 * Description: Creates and initializes a new stack.
 * Return Value:
 *   - Pointer to the newly created stack on success.
 *   - NULL if memory allocation fails.
 */
struct stack *stack_create(void)
{
	struct stack *s;

	s = (struct stack *)malloc(sizeof(struct stack));
	if (s == NULL) {
		return NULL;
	}

	s->base = (int *)malloc(MIN_STACK_CAPACITY * sizeof(int));
	if (s->base == NULL) {
		return NULL;
	}

	s->top		= -1;
	s->capacity = MIN_STACK_CAPACITY;

	return s;
}

/*
 * Description: Destroys the stack and frees associated memory.
 * Parameters:
 *   - s: Pointer to the stack structure.
 * Return Value:
 *   - 0 on success.
 *   - -EINVAL if the stack or base pointer is NULL.
 */
int stack_destroy(struct stack *s)
{
	return 0;
}

/*
 * Description: Pushes a value onto the stack. If the stack is full, it grows the stack.
 * Parameters:
 *   - s: Pointer to the stack structure.
 *   - value: The value to push onto the stack.
 * Return Value:
 *   - 0 on success.
 *   - Error code if stack growth fails (-ENOMEM or -EINVAL).
 */
int stack_push(struct stack *s, int value)
{
	return 0;
}

/*
 * Description: Pops the top value off the stack.
 * Parameters:
 *   - s: Pointer to the stack structure.
 * Return Value:
 *   - 0 on success.
 *   - -EINVAL if the stack is empty.
 */
int stack_pop(struct stack *s)
{
	return 0;
}

/*
 * Description: Returns the top value of the stack without removing it.
 * Parameters:
 *   - s: Pointer to the stack structure.
 * Return Value:
 *   - The top value of the stack on success.
 *   - -EINVAL if the stack is NULL, uninitialized, or empty.
 */
int stack_peek(struct stack *s)
{
	return 0;
}

/*
 * Description: Returns the current size of the stack (number of elements).
 * Parameters:
 *   - s: Pointer to the stack structure.
 * Return Value:
 *   - The number of elements in the stack.
 *   - -EINVAL if the stack is NULL.
 */
int stack_size(struct stack *s)
{
	return 0;
}

/*
 * Description: Returns the current capacity of the stack.
 * Parameters:
 *   - s: Pointer to the stack structure.
 * Return Value:
 *   - The capacity of the stack.
 *   - -EINVAL if the stack is NULL.
 */
int stack_capacity(struct stack *s)
{
	return 0;
}
