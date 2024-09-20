#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <common.h>
#include <sizes.h>
#include <testsuite.h>

#include <queue.h>

TEST_SUITE(queue);

TEST_CASE(queue, create_and_destroy)
{
	struct queue *q;
	int rc;
	int capacity = 16;

	q = queue_create(capacity);
	TEST_ASSERT_NE(q, NULL);
	TEST_ASSERT_EQ(queue_size(q), 0);
	TEST_ASSERT_EQ(queue_capacity(q), capacity);

	rc = queue_destroy(q);
	TEST_ASSERT_EQ(rc, 0);

	return TEST_PASS;

}

TEST_CASE(queue, push_and_pop)
{
	struct queue *q;
	int rc;
	int capacity = 32;

	q = queue_create(capacity);

	for (int i = 0; i < capacity; i++) {
		rc = queue_push(q, i);
		TEST_ASSERT_EQ(rc, 0);
		TEST_ASSERT_EQ(queue_front(q), i);
		TEST_ASSERT_EQ(queue_back(q), 0);
		TEST_ASSERT_EQ(queue_size(q), (i + 1));
	}

	for (int i = 0; i < capacity - 1; i++) {
		rc = queue_pop(q);
		TEST_ASSERT_EQ(rc, 0);
		TEST_ASSERT_EQ(queue_front(q), capacity - 1);
		TEST_ASSERT_EQ(queue_back(q), i + 1);
		TEST_ASSERT_EQ(queue_size(q), capacity - 1 - i);
	}

	rc = queue_pop(q);
	TEST_ASSERT_EQ(rc, 0);
	TEST_ASSERT_EQ(queue_front(q), -EINVAL);
	TEST_ASSERT_EQ(queue_back(q), -EINVAL);
	TEST_ASSERT_EQ(queue_size(q), 0);
	TEST_ASSERT_EQ(queue_capacity(q), capacity);

	queue_destroy(q);

	return TEST_PASS;
}

TEST_CASE(queue, over_push)
{
	struct queue *q;
	int rc;
	int capacity = 55;

	q = queue_create(capacity);

	for (int i = 0; i < capacity; i++) {
		rc = queue_push(q, i + 1);
		TEST_ASSERT_EQ(rc, 0);
	}

	for (int i= 0; i < 16; i++) {
		rc = queue_push(q, 0xAA);
		TEST_ASSERT_EQ(rc, -ENOMEM);
		TEST_ASSERT_EQ(queue_is_full(q), true);
		TEST_ASSERT_EQ(queue_is_empty(q), false);
		TEST_ASSERT_EQ(queue_front(q), capacity);
		TEST_ASSERT_EQ(queue_back(q), 1);
		TEST_ASSERT_EQ(queue_size(q), capacity);
		TEST_ASSERT_EQ(queue_capacity(q), capacity);
	}

	queue_destroy(q);

	return TEST_PASS;
}

TEST_CASE(queue, over_pop)
{
	struct queue *q;
	int rc;
	int capacity = 127;

	q = queue_create(capacity);

	for (int i = 0; i < 127; i++) {
		rc = queue_pop(q);
		TEST_ASSERT_EQ(rc, -EINVAL);
		TEST_ASSERT_EQ(queue_is_empty(q), true);
		TEST_ASSERT_EQ(queue_is_full(q), false);
		TEST_ASSERT_EQ(queue_size(q), 0);
		TEST_ASSERT_EQ(queue_capacity(q), capacity);
	}

	queue_destroy(q);

	return TEST_PASS;
}

TEST_CASE(queue, repeated_push_pop)
{
	struct queue *q;
	int rc;
	int capacity = 233;

	q = queue_create(capacity);

	for (int i = 0; i < capacity * 3; i++) {
		rc = queue_push(q, i);
		TEST_ASSERT_EQ(rc, 0);
		TEST_ASSERT_EQ(queue_is_empty(q), false);
		TEST_ASSERT_EQ(queue_front(q), i);
		TEST_ASSERT_EQ(queue_back(q), i);
		TEST_ASSERT_EQ(queue_size(q), 1);
		TEST_ASSERT_EQ(queue_capacity(q), capacity);

		rc = queue_pop(q);
		TEST_ASSERT_EQ(rc, 0);
		TEST_ASSERT_EQ(queue_is_empty(q), true);
		TEST_ASSERT_EQ(queue_front(q), -EINVAL);
		TEST_ASSERT_EQ(queue_back(q), -EINVAL);
		TEST_ASSERT_EQ(queue_size(q), 0);
		TEST_ASSERT_EQ(queue_capacity(q), capacity);
	}

	queue_destroy(q);

	return TEST_PASS;
}

TEST_CASE(queue, hanlde_null_ptr)
{
	int rc;

	rc = queue_destroy(NULL);
	TEST_ASSERT_EQ(rc, -EINVAL);

	rc = queue_is_full(NULL);
	TEST_ASSERT_EQ(rc, false);

	rc = queue_is_empty(NULL);
	TEST_ASSERT_EQ(rc, false);

	rc = queue_push(NULL, 0);
	TEST_ASSERT_EQ(rc, -EINVAL);

	rc = queue_pop(NULL);
	TEST_ASSERT_EQ(rc, -EINVAL);

	rc = queue_front(NULL);
	TEST_ASSERT_EQ(rc, -EINVAL);

	rc = queue_back(NULL);
	TEST_ASSERT_EQ(rc, -EINVAL);

	rc = queue_size(NULL);
	TEST_ASSERT_EQ(rc, -EINVAL);

	rc = queue_capacity(NULL);
	TEST_ASSERT_EQ(rc, -EINVAL);

	return TEST_PASS;
}

TEST_CASE(queue, non_positive_capacity)
{
	struct queue *q;
	int rc;

	q = queue_create(0);
	TEST_ASSERT_EQ(q, NULL);

	q = queue_create(-1);
	TEST_ASSERT_EQ(q, NULL);

	q = queue_create(-2);
	TEST_ASSERT_EQ(q, NULL);

	q = queue_create(-17);
	TEST_ASSERT_EQ(q, NULL);

	q = queue_create(-439);
	TEST_ASSERT_EQ(q, NULL);

	q = queue_create(-1024);
	TEST_ASSERT_EQ(q, NULL);

	return TEST_PASS;
}

int main(int argc, char **argv)
{
	TEST_SUITE_RUN(queue);
}
