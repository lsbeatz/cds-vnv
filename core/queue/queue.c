#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#include <sizes.h>

#include "queue.h"

struct queue *queue_create(int capacity)
{
	return NULL;
}

int queue_destroy(struct queue *q)
{
	return 0;
}

bool queue_is_full(struct queue *q)
{
	return false;
}

bool queue_is_empty(struct queue *q)
{
	return false;
}

int queue_enqueue(struct queue *q, int value)
{
	return 0;
}

int queue_dequeue(struct queue *q)
{
	return 0;
}

int queue_peek(struct queue *q)
{
	return 0;
}

int queue_size(struct queue *q)
{
	return 0;
}

int queue_capacity(struct queue *q)
{
	return 0;
}


