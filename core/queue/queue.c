#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include <sizes.h>

#include "queue.h"

/*
 * Description: Creates a queue with the specified capacity.
 * Parameters:
 *   - capacity: The maximum size of the queue.
 * Return Value:
 *   - Pointer to the newly created queue on success.
 *   - NULL if memory allocation fails or capacity is invalid.
 */
struct queue *queue_create(int capacity)
{
	struct queue *q;

	if (capacity <= 0) {
		return NULL;
	}

	q = (struct queue *)malloc(sizeof(struct queue));
	if (q == NULL) {
		return NULL;
	}

	q->base = (int *)malloc((capacity + 1) * sizeof(int));
	if (q->base == NULL) {
		return NULL;
	}

	q->front    = 0;
	q->back     = 0;
	q->capacity = capacity + 1;

	return q;
}

/*
 * Description: Frees the memory associated with the queue.
 * Parameters:
 *   - q: Pointer to the queue.
 * Return Value:
 *   - 0 on success.
 *   - -EINVAL if the queue or its base is NULL.
 */
int queue_destroy(struct queue *q)
{
	if (q == NULL) {
		return -EINVAL;
	}

	if (q->base == NULL) {
		return -EINVAL;
	}

	free(q->base);
	free(q);

	return 0;
}

/*
 * Description: Checks if the queue is full.
 * Parameters:
 *   - q: Pointer to the queue.
 * Return Value:
 *   - true if the queue is full, false otherwise.
 */
bool queue_is_full(struct queue *q)
{
	if (q == NULL) {
		return false;
	}

	if (q->base == NULL) {
		return false;
	}

	return (q->front + 1) % q->capacity == q->back;
}

/*
 * Description: Checks if the queue is empty.
 * Parameters:
 *   - q: Pointer to the queue.
 * Return Value:
 *   - true if the queue is empty, false otherwise.
 */
bool queue_is_empty(struct queue *q)
{
	if (q == NULL) {
		return false;
	}

	if (q->base == NULL) {
		return false;
	}

	return q->front == q->back;
}

/*
 * Description: Adds a value to the queue.
 * Parameters:
 *   - q: Pointer to the queue.
 *   - value: The value to be added to the queue.
 * Return Value:
 *   - 0 on success.
 *   - -EINVAL if the queue is NULL or uninitialized.
 *   - -ENOMEM if the queue is full.
 */
int queue_push(struct queue *q, int value)
{
	if (q == NULL) {
		return -EINVAL;
	}

	if (q->base == NULL) {
		return -EINVAL;
	}

	if (queue_is_full(q)) {
		return -ENOMEM;
	}

	q->front = (q->front + 1) % q->capacity;
	q->base[q->front] = value;

	return 0;
}

/*
 * Description: Removes an element from the front of the queue.
 * Parameters:
 *   - q: Pointer to the queue.
 * Return Value:
 *   - 0 on success.
 *   - -EINVAL if the queue is NULL, uninitialized, or empty.
 */
int queue_pop(struct queue *q)
{
	if (q == NULL) {
		return -EINVAL;
	}

	if (q->base == NULL) {
		return -EINVAL;
	}

	if (queue_is_empty(q)) {
		return -EINVAL;
	}

	q->back = (q->back + 1) % q->capacity;

	return 0;
}

/*
 * Description: Retrieves the front element of the queue without removing it.
 * Parameters:
 *   - q: Pointer to the queue.
 * Return Value:
 *   - The value at the front of the queue.
 *   - -EINVAL if the queue is NULL, uninitialized, or empty.
 */
int queue_front(struct queue *q)
{
	if (q == NULL) {
		return -EINVAL;
	}

	if (q->base == NULL) {
		return -EINVAL;
	}

	if (queue_is_empty(q)) {
		return -EINVAL;
	}

	return q->base[q->front];
}

/*
 * Description: Retrieves the back element of the queue without removing it.
 * Parameters:
 *   - q: Pointer to the queue.
 * Return Value:
 *   - The value at the back of the queue.
 *   - -EINVAL if the queue is NULL, uninitialized, or empty.
 */
int queue_back(struct queue *q)
{
	if (q == NULL) {
		return -EINVAL;
	}

	if (q->base == NULL) {
		return -EINVAL;
	}

	if (queue_is_empty(q)) {
		return -EINVAL;
	}

	return q->base[(q->back + 1) % q->capacity];
}

/*
 * Description: Returns the number of elements in the queue.
 * Parameters:
 *   - q: Pointer to the queue.
 * Return Value:
 *   - The number of elements in the queue.
 *   - -EINVAL if the queue is NULL or uninitialized.
 */
int queue_size(struct queue *q)
{
	int size;

	if (q == NULL) {
		return -EINVAL;
	}

	if (q->base == NULL) {
		return -EINVAL;
	}

	size = q->front - q->back;
	if (size < 0) {
		size += q->capacity;
	}

	return size;
}

/*
 * Description: Returns the capacity of the queue.
 * Parameters:
 *   - q: Pointer to the queue.
 * Return Value:
 *   - The capacity of the queue.
 *   - -EINVAL if the queue is NULL or uninitialized.
 */
int queue_capacity(struct queue *q)
{
	if (q == NULL) {
		return -EINVAL;
	}

	if (q->base == NULL) {
		return -EINVAL;
	}

	return q->capacity - 1;
}
