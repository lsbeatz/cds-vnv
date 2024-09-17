#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <stdio.h>
#include <termcolor.h>

enum test_rc {
	TEST_PASS,
	TEST_FAIL,
	TEST_SKIP,

	NR_TEST_RC,
};

struct test_case {
	char *name;
	int (*func)(void);
	struct test_case *next;
};

struct test_suite {
	char *name;
	int	  nr_tests;
	struct test_case *tc_head;
};

#define TEST_SUITE(ts)						\
	struct test_suite test_suite_##ts = {	\
		.name	  = #ts,					\
		.nr_tests = 0,						\
		.tc_head  = NULL, 					\
	}

#define TEST_CASE(ts, tc)										\
	int	test_func_##tc(void);									\
	struct test_case test_case_##tc = {							\
		.name = #tc,											\
		.func = test_func_##tc,									\
		.next = NULL,											\
	};															\
	__attribute__((constructor)) void test_case_register_##tc()	\
	{															\
		test_case_add(&test_suite_##ts, &test_case_##tc);		\
	}															\
	int test_func_##tc(void)

#define TEST_SUITE_RUN(ts)						\
	do {										\
		test_suite_execute(&test_suite_##ts);	\
	} while (0)

#define TEST_LOG(hdr, color, fmt, ...)											\
	do {																		\
		printf(color "[%-8s] " TERMCOLOR_RESET fmt "\n", #hdr, ##__VA_ARGS__);	\
	} while (0)

#define TEST_LOG_SUITE(fmt, ...)												\
	do {																		\
		printf("\n");															\
		printf("=======================================================\n");	\
		printf(fmt "\n", ##__VA_ARGS__);										\
		printf("=======================================================\n");	\
	} while (0)

#define TEST_LOG_CASE(fmt, ...)													\
	do {																		\
		printf("\n[" fmt "]\n", ##__VA_ARGS__);									\
		printf("-------------------------------------------------------\n");	\
	} while (0)

#define TEST_LOG_LOAD(fmt, ...)	  TEST_LOG(LOAD, TERMCOLOR_RESET, fmt, ##__VA_ARGS__)
#define TEST_LOG_PASS(fmt, ...)	  TEST_LOG(PASS, TERMCOLOR_GREEN, fmt, ##__VA_ARGS__)
#define TEST_LOG_FAIL(fmt, ...)	  TEST_LOG(FAIL, TERMCOLOR_RED, fmt, ##__VA_ARGS__)
#define TEST_LOG_SKIP(fmt, ...)	  TEST_LOG(SKIP, TERMCOLOR_BLUE, fmt, ##__VA_ARGS__)
#define TEST_LOG_WARN(fmt, ...)	  TEST_LOG(WARN, TERMCOLOR_YELLOW, fmt, ##__VA_ARGS__)
#define TEST_LOG_ASSERT(fmt, ...) TEST_LOG(ASSERT, TERMCOLOR_MAGENTA, fmt, ##__VA_ARGS__)

#define TEST_ASSERT(a, op, b)													\
	do {																		\
		if (a op b) { /* do nothing */ }										\
		else {																	\
			TEST_LOG_ASSERT("%s:%d: %s %s %s", __FILE__, __LINE__, #a, #op, #b);\
			return TEST_FAIL;													\
		}																		\
	} while (0)

#define TEST_ASSERT_EQ(a, b) TEST_ASSERT(a, ==, b)
#define TEST_ASSERT_NE(a, b) TEST_ASSERT(a, !=, b)
#define TEST_ASSERT_GT(a, b) TEST_ASSERT(a, >, b)
#define TEST_ASSERT_GE(a, b) TEST_ASSERT(a, >=, b)
#define TEST_ASSERT_LT(a, b) TEST_ASSERT(a, <, b)
#define TEST_ASSERT_LE(a, b) TEST_ASSERT(a, <=, b)

void test_case_add(struct test_suite *ts, struct test_case *tc);
void test_suite_execute(struct test_suite *ts);

#endif /* TESTSUITE_H */
