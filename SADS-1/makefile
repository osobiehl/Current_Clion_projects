default: all
all: rpn.c rpn_stack.c run_infix.c infix.c
	afl-gcc -o testerino run_infix.c rpn.c infix.c rpn_stack.c -lm
	AFL_SKIP_CPUFREQ=1 afl-fuzz  -i afl_testcase -o afl_findings ./testerino