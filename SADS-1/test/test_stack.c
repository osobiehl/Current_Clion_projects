/*
 * gcd/test/check-gcd.c --
 */

#include <stdlib.h>
#include <check.h>
#include <stdio.h>
#include "rpn_stack.h"
#include "rpn.h"


/*
 * We introduce a simple data structure so that we can make test cases
 * for the gcd and lcm functions data driven.
 */

START_TEST(test_stack)
	{
		rpn_stack_t * stack_test = rpn_stack_new();
		if (!stack_test){
			perror("failed to create");
		}
 		ck_assert_msg(stack_test != NULL, "rpn_stack_new returns null!");
		int i1 = 69;
		rpn_stack_push(stack_test, (void*) & i1);
		ck_assert_int_eq(i1, *(int*)rpn_stack_pop(stack_test) );
		ck_assert_msg(rpn_stack_empty(stack_test) == 1, "stack says it is not empty when it should be");
		const int limit_inp = 20;
		int ints[limit_inp];
		//check the order of our stack + stack extension;
		for (int i = 0; i < limit_inp; i++){
			ints[i] = i;
			rpn_stack_push(stack_test, (void*)&ints[i]);
		}
		for(int i = limit_inp - 1; i >= 0; i--){
			int res = *(int*)rpn_stack_pop(stack_test);
			ck_assert_int_eq(res, i);
		}
		//stack should be empty
		ck_assert_msg(rpn_stack_empty(stack_test) == 1, "stack should be empty!");
		//try to peek to the back of the stack
		void* i = rpn_stack_peek(stack_test);
		ck_assert_msg(i == NULL, "empty stack should peek return null");
		//make sure we have no segmentation faults

		ck_assert_msg(NULL == rpn_stack_pop(stack_test), "empty stack pop should return NULL");

		int s = 5;
		rpn_stack_push(stack_test, (void*)&s);
		ck_assert_int_eq(s, *(int*)rpn_stack_peek(stack_test));
		rpn_stack_del(stack_test);
	}
END_TEST

typedef struct rpn_t_test{
	const char* input;
	const char* output;
} rpn_test_t;
START_TEST(test_rpn)
	{
		rpn_test_t arr[] = {
				{"1 1 +", "2"},
				{"2 2 * 5 +", "9"},
				{ "8 2 /", "4"},
				{ "10 5 %", "0"},
				{ "69 9 -", "60"},
				{"5 5 5 5 + + +", "20"},
				{NULL, NULL}
		};
		char* str;
		for (int i = 0; arr[i].input != NULL; i++){
			int r = rpn_eval_expr(arr[i].input, &str);
			ck_assert_str_eq(arr[i].output, str);
			ck_assert_int_eq(r, RPN_OK);
		}
		//corner cases
		int r = rpn_eval_expr("5 5 5 5 5", &str);
		ck_assert_int_eq(r, RPN_MISSING_OPERATOR);
		r = rpn_eval_expr("5 5 + +", &str);
		ck_assert_int_eq(r, RPN_MISSING_OPERAND);
		r = rpn_eval_expr("foo", &str);
		ck_assert_int_eq(r, RPN_INVALID_TOKEN);
		r = rpn_eval_expr("5 0 /", &str);
		ck_assert_int_eq(r, RPN_ARITHMETIC_ERROR);



	}
END_TEST

static Suite*
gdb_suite(void)
{
	Suite *s;
	TCase *tc_gcd, *tc_lcm;

	s = suite_create("all");
	tc_gcd = tcase_create("gcd");
	tc_lcm = tcase_create("lcm");

	tcase_add_test(tc_gcd, test_stack);
	suite_add_tcase(s, tc_gcd);
	tcase_add_test(tc_lcm, test_rpn);
	suite_add_tcase(s, tc_lcm);
	return s;
}

int main(void)
{
	rpn_stack_t *x = rpn_stack_new();
	if (!x)
	{
		printf("X IS NULL!\n");
	}
	int number_failed;
	Suite *s;
	SRunner *sr;

	s = gdb_suite();
	sr = srunner_create(s);

	srunner_run_all(sr, CK_NORMAL);
	number_failed = srunner_ntests_failed(sr);
	srunner_free(sr);
	return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}