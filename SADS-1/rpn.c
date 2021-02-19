//
// Created by osobiehl on 19.02.21.
//
#include "rpn.h"
#include "string.h"
#include <stdlib.h>
#include <stdio.h>
#include "rpn_stack.h"
#include <ctype.h>
#include <math.h>
static const int DEBUG = 0;
/**
 * @brief evaluates an expression,
 * @param expr
 * @param result
 * @return
 */
int rpn_eval_expr(const char *expr, char **result){
	if (!expr) {
		perror("expression given is null!\n");
		exit(-1);
	}
	char exp[strlen(expr) +1];
	strcpy(exp, expr);
	const char delim[2] = " ";
	//quick and dirty upper bound
	char* tokens[strlen(expr) +1];

	char* token;
	int size = -1;
	token = strtok(exp, delim);
	while ( token != NULL){
		size++;
		tokens[size] = token;
		token = strtok(NULL, delim);
	}
	tokens[size +1] = NULL;
	if (DEBUG){
		for (int i = 0; i < size; i++){
			puts(tokens[i]);
		}
	}
	int eval = rpn_eval_token(tokens, result);
	if (eval != RPN_OK) {
		*result = rpn_strerror(eval);

	}
	return eval;
}

static inline int rpn_isdigit(char* in){
	for (unsigned long i = 0; in[i] != ' ' && in[i] != '\0' && i < strlen(in); i++){
		if (!isdigit(in[i])){
			return 0;
		}
	}
	return 1;
}
static inline int rpn_isOperator(const char* in){
	const char* operators = "+-*/%\0";
	int isoperator = 0;
	for (const char* i = operators; *i != '\0'; i++){
		if (*in == *i){
			isoperator =1;
			break;
		}
	}
	if ( (*(in+1) != ' ' && *(in+1) != '\0') || !isoperator) {

		if (DEBUG){
			puts("not operator because of whitespace or null ending char");
		}
		return 0;
	}
	else return 1;



}

int rpn_eval_token(char* token[], char** result){
	if (!token){
		perror("invalid token pointer!");
		exit(-1);
	}
	rpn_stack_t* stack = rpn_stack_new();
	int total_tokens = 0;
	for (int i = 0; token[i] != NULL; i++)
		total_tokens++;
	// since I'm not malloc'ing anything, I have to make sure to not share addresses
	// inefficient but memory is cheap
	int potential_operand_results[total_tokens+1];
	int in[total_tokens+1];
	for(int i = 0; token[i] != NULL; i++){
		int isDigit = rpn_isdigit(token[i]);
		//case: we have an integer inp
		if (isDigit){

			in[i] = atoi(token[i]);

			rpn_stack_push(stack, (void*)&in[i]);
		}
		// case: we have an operator
		else if (rpn_isOperator(token[i])){
			char op = *token[i];
			if (rpn_stack_empty(stack))
				return RPN_MISSING_OPERAND;
			int operand1 = *(int*)rpn_stack_pop(stack);
			if (rpn_stack_empty(stack))
				return RPN_MISSING_OPERAND;
			int operand2 = *(int*)rpn_stack_pop(stack);
			int res;
			switch(op){
				case('+'):
					res = operand1 + operand2;
					break;
				case('-'):
					res = operand2 - operand1;
					break;
				case('*'):
					res = operand2 * operand1;
					break;
				case('/'):
					if (operand1 == 0) {

						if (DEBUG)
							perror("division by zero!");
						return RPN_ARITHMETIC_ERROR;
					}
					res = operand2 / operand1;
					break;
				case('%'):
					if (operand1 == 0) {

						if (DEBUG)
							perror("modulo by zero!");
						return RPN_ARITHMETIC_ERROR;
					}
					res = operand2 % operand1;
					break;
				default:
					return RPN_INVALID_TOKEN;
					break;
			}
			potential_operand_results[i] = res;
			rpn_stack_push(stack, (void*)&potential_operand_results[i]);
		}
		else {
			//need to print and exit here because I'm lazy and adhering to the api
			printf("rpnc: invalid token \'%s\'\n", token[i]);
			return RPN_INVALID_TOKEN;
		}


	}
	//this case should never happen but whatever
	if (rpn_stack_empty(stack)) {
		return RPN_MISSING_OPERAND;
	}
	int final_result = *(int*)rpn_stack_pop(stack);
	//case: there's more stuff in the stack
	if (!rpn_stack_empty(stack)){
		if (DEBUG){
			printf("printing remaining contents\n");
			while(!rpn_stack_empty(stack)){
				int a = *(int*)rpn_stack_pop(stack);
				printf("%d ", a);
			}
			printf("\n");
		}
		return RPN_MISSING_OPERATOR;
	}

	//convert int to str:
	if (DEBUG)
	{
		printf("input: %d", final_result);
		printf("bytes used: %lu \n", (unsigned long) ((ceil(log10(final_result) + 1)) * sizeof(char)));
	}
	char* ret_str;
	if (final_result != 0)
		ret_str = malloc((unsigned long) (ceil(log10(final_result) + 1)) * sizeof(char));
	else
		ret_str = malloc( sizeof(char) * 2);
	if (!ret_str){
		perror("out of memory!" );
		exit(EXIT_FAILURE);
	}
	if (sprintf(ret_str, "%d", final_result)  < 0){
		perror("sprintf");
		exit(EXIT_FAILURE);
	}
	// ThIs ToOk mE OnE hOUr
	*result = ret_str;
	return RPN_OK;
}
	char* rpn_strerror(int errnum)
	{
		char* output;
		switch(errnum){

			case(RPN_MISSING_OPERAND):
				output = "rpnc: missing operand\n";
				break;
			case(RPN_MISSING_OPERATOR):
				output = "rpnc: missing operator\n";
				break;
			case(RPN_ARITHMETIC_ERROR):
				output = "rpnc: arithmetic error\n";
				break;
			case(RPN_INVALID_TOKEN):
				output="";
				break;
			default:
				output="rpnc: unknown error\n";
				break;
			}
			return strdup(output);

	}


