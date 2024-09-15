#include <common.h>
#include <sizes.h>
#include <testsuite.h>

#include <stack.h>

TEST_SUITE(stack);

TEST_CASE(stack, create_and_destroy)
{
	struct stack *s = NULL;
	int rc;

	rc = stack_create(s);
	TEST_ASSERT_EQ(rc, 0);
	TEST_ASSERT_NE(s, NULL);
	TEST_ASSERT_EQ(stack_size(s), 0);
	TEST_ASSERT_EQ(stack_capacity(s), (SZ_64 / sizeof(int)));

	rc = stack_destroy(s);
	TEST_ASSERT_EQ(rc, 0);

	return TEST_PASS;
}

TEST_CASE(stack, push_and_pop)
{
	struct stack *s = NULL;
	int rc;
	int items[8] = {1, 2, 3, 4, 5, 6, 7, 8};

	stack_create(s);

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

int main(int argc, char **argv)
{
	TEST_SUITE_RUN(stack);
}
