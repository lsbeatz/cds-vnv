#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

struct queue {
	int *base;
	int  front;
	int  back;
	int  capacity;
};

struct queue *queue_create(int capacity);
int queue_destroy(struct queue *q);

bool queue_is_full(struct queue *q);
bool queue_is_empty(struct queue *q);

int queue_push(struct queue *q, int value);
int queue_pop(struct queue *q);

int queue_front(struct queue *q);
int queue_back(struct queue *q);

int queue_size(struct queue *q);
int queue_capacity(struct queue *q);

#endif /* QUEUE_H */
