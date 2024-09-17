#include <stdlib.h>
#include <errno.h>
#include <common.h>
#include <sizes.h>
#include <testsuite.h>

#include <stack.h>

TEST_SUITE(stack);

TEST_CASE(stack, create_and_destroy)
{
	struct stack *s;
	int rc;

	s = stack_create();
	TEST_ASSERT_NE(s, NULL);
	TEST_ASSERT_EQ(stack_size(s), 0);
	TEST_ASSERT_EQ(stack_capacity(s), (SZ_64 / sizeof(int)));

	rc = stack_destroy(s);
	TEST_ASSERT_EQ(rc, 0);

	return TEST_PASS;
}

TEST_CASE(stack, push_and_pop)
{
	struct stack *s;
	int rc;
	int items[8] = {1, 2, 3, 4, 5, 6, 7, 8};

	s = stack_create();

	for (int i = 0; i < ARRAY_SIZE(items); i++) {
		rc = stack_push(s, items[i]);
		TEST_ASSERT_EQ(rc, 0);
		TEST_ASSERT_EQ(stack_peek(s), items[i]);
	}

	for (int i = 7; i >= 0; i--) {
		TEST_ASSERT_EQ(stack_peek(s), items[i]);
		rc = stack_pop(s);
		TEST_ASSERT_EQ(rc, 0);
	}

	stack_destroy(s);

	return TEST_PASS;
}

TEST_CASE(stack, grow)
{
	struct stack *s;
	int rc;
	size_t size = (SZ_64 / sizeof(int));
	size_t max_size = (SZ_4K / sizeof(int));

	s = stack_create();

	for (int i = 0; i < max_size + 1; i++) {
		rc = stack_push(s, i);
		if (i >= max_size) {
			TEST_ASSERT_EQ(rc, -ENOMEM);
			TEST_ASSERT_EQ(stack_capacity(s), max_size);
			TEST_ASSERT_EQ(stack_peek(s), max_size - 1);
		} else if (i >= size) {
			size = (size << 1);
			TEST_ASSERT_EQ(rc, 0);
			TEST_ASSERT_EQ(stack_capacity(s), size);
			TEST_ASSERT_EQ(stack_peek(s), i);
		} else {
			TEST_ASSERT_EQ(rc, 0);
			TEST_ASSERT_EQ(stack_capacity(s), size);
			TEST_ASSERT_EQ(stack_peek(s), i);
		}
	}

	for (int i = max_size - 1; i >= 0; i--) {
		TEST_ASSERT_EQ(stack_peek(s), i);
		rc = stack_pop(s);
		TEST_ASSERT_EQ(rc, 0);
		TEST_ASSERT_EQ(stack_capacity(s), max_size);
	}
	TEST_ASSERT_EQ(stack_peek(s), -EINVAL);

	stack_destroy(s);

	return TEST_PASS;
}

TEST_CASE(stack, over_pop)
{
	struct stack *s;
	int rc;

	s = stack_create();

	for (int i = 0; i < 10; i++) {
		rc = stack_pop(s);
		TEST_ASSERT_EQ(rc, -EINVAL);
		TEST_ASSERT_EQ(stack_size(s), 0);
	}

	stack_destroy(s);

	return TEST_PASS;
}

int main(int argc, char **argv)
{
	TEST_SUITE_RUN(stack);
}
