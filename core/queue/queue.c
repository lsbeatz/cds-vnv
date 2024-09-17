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

int queue_push(struct queue *q, int value)
{
	return 0;
}

int queue_pop(struct queue *q)
{
	return 0;
}

int queue_front(struct queue *q)
{
	return 0;
}

int queue_back(struct queue *q)
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


