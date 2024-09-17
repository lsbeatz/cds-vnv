#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/time.h>

#include "testsuite.h"

void test_case_add(struct test_suite *ts, struct test_case *tc)
{
	struct test_case *cur;

	if (ts == NULL || tc == NULL) {
		return;
	}

	if (ts->tc_head == NULL) {
		ts->tc_head = tc;
	} else {
		cur = ts->tc_head;
		while (cur->next != NULL) {
			cur = cur->next;
		}
		cur->next = tc;
	}
	ts->nr_tests++;

	TEST_LOG_LOAD("Test Suite(%s) <= add TC%02d(%s)", ts->name, ts->nr_tests, tc->name);
}

void test_suite_execute(struct test_suite *ts)
{
	int rc;
	int tc_num;
	int results[NR_TEST_RC];
	int elapsed;

	struct timeval	  start;
	struct timeval	  end;
	struct test_case *tc;

	if (ts == NULL) {
		assert(0);
		return;
	}

	TEST_LOG_SUITE("Running Test Suite: %s", ts->name);

	memset(results, 0, sizeof(results));

	tc = ts->tc_head;
	tc_num = 1;
	while (tc) {
		TEST_LOG_CASE("Test Case %02d: %s", tc_num, tc->name);

		gettimeofday(&start, NULL);
		rc = tc->func();
		gettimeofday(&end, NULL);

		elapsed = (end.tv_sec - start.tv_sec) * 1E6 + (end.tv_usec - start.tv_usec);

		switch (rc) {
		case TEST_PASS:
			TEST_LOG_PASS("execution time: %dms", elapsed);
			break;
		case TEST_FAIL:
			TEST_LOG_FAIL("execution time: %dms", elapsed);
			break;
		case TEST_SKIP:
			TEST_LOG_SKIP("execution time: %dms", elapsed);
			break;
		default:
			break;
		}

		results[rc]++;
		tc = tc->next;
		tc_num++;
	}

	TEST_LOG_SUITE(
		"Test Suite Summary: %s\n"
		"total %d, "
		TERMCOLOR_GREEN  "%d passed, "
		TERMCOLOR_RED    "%d failed, "
		TERMCOLOR_YELLOW "%d skipped "
		TERMCOLOR_RESET,
		ts->name, ts->nr_tests, results[TEST_PASS], results[TEST_FAIL], results[TEST_SKIP]
	);
}
