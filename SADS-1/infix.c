//
// Created by osobiehl on 24.02.21.
//

#include "infix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "rpn_stack.h"
#include <ctype.h>
#include "rpn.h"
static const int DEBUG = 0;
static inline int infix_isOperator(const char* in){
	const char* operators = "+-*/%()\0";
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
static inline int infix_isdigit(char* in){
	for (unsigned long i = 0; in[i] != ' ' && in[i] != '\0' && i < strlen(in); i++){
		if (!isdigit(in[i])){
			return 0;
		}
	}
	return 1;
}
static inline int infix_operator_precedence(char op){
	switch(op){
		case('+'):
			return 1;
		case('-'):
			return 1;
		case('*'):
			return 2;
		case('/'):
			return 2;
		case('%'):
			return 3;
		default:
			perror("invalid operator in a part that should have seen an operator");
			exit(-1);
	}
}

char* infix_strerror(int errnum) {
	if ( errnum == INFIX_INVALID_TOKEN ){
		return NULL;
	}
	else if (errnum == INFIX_SYNTAX_ERROR){
		return NULL;
	}
	else return rpn_strerror(errnum);
}

int expr_infix_eval(const char* expr, char** result){
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
	tokens[size + 1] = NULL;
	if (DEBUG){
		for (int i = 0; i <= size; i++){
			puts(tokens[i]);
		}

	}
	int Res = expr_infix_eval_token(tokens, result);

	if (Res != RPN_OK) {
		*result = infix_strerror(Res);

	}
	return Res;

}

int expr_infix_eval_token(char *token[], char **result){
	//first let's tokenize and convert to postfix, then call our rpn function
	rpn_stack_t* operator_stack = rpn_stack_new();
	rpn_stack_t* result_stack = rpn_stack_new(); // we will use some casting magic and use this stack ... xd


	if (!token){
		perror("invalid token pointer!");
		exit(-1);
	}
	int total_tokens = 0;
	for (int i = 0; token[i] != NULL; i++)
		total_tokens++;

	for(int i = 0; token[i] != NULL; i++){
		int isDigit = infix_isdigit(token[i]);
		//case: we have an integer inp
		if (isDigit){
			//syntax check: operator should follow any non-ending integer input
			if ( token [i+1] != NULL && ! infix_isOperator(token[i+1]) ) {
				printf("infix: syntax error: %s %s\n", token[i], token[i+1]);
				rpn_stack_del(operator_stack);
				rpn_stack_del(result_stack);
				return INFIX_SYNTAX_ERROR;
			}
			// if it's a digit we simply add it to the stack
			rpn_stack_push(result_stack, (void*) token[i]);
		}
			// case: we have an operator
		else if (infix_isOperator(token[i])){
			char op = *token[i];
			if (token[i+1] == NULL && op != ')'){
				rpn_stack_del(operator_stack);
				rpn_stack_del(result_stack);
				return RPN_MISSING_OPERAND;
			}
			else if (*token[i] == ')' && token[i+1] == NULL){
				//do nothing
			}
			// syntax error
			else if ( !infix_isdigit(token[i+1]) && (*token[i + 1] != ')' && *token[i+1] != '(') ) {
				printf("infix: syntax error: %s %s\n", token[i], token[i+1]);
				rpn_stack_del(operator_stack);
				rpn_stack_del(result_stack);
				return INFIX_SYNTAX_ERROR;
			}
		//	printf("operator: %c\n", op);
			//now we have to check operator precedence
			if (op == '('){
				rpn_stack_push(operator_stack, (void*) token[i]);
			}
			else if (op == ')'){
				char stack_op;
				char* ptr= (char*) rpn_stack_peek(operator_stack);
				if (!ptr){
					printf("infix: invalid number of operators, \'(\' expected \n");
					rpn_stack_del(operator_stack);
					rpn_stack_del(result_stack);
					return INFIX_SYNTAX_ERROR;
				}

				while ( *ptr   != '('){

					//push all previous operators, our normal logic should ensure that the operands are correctly ordered.
					rpn_stack_push(result_stack, rpn_stack_pop(operator_stack));
					ptr = (char*) rpn_stack_peek(operator_stack);
					if (!ptr){
						printf("infix: invalid number of operators, \'(\' expected \n");
						rpn_stack_del(operator_stack);
						rpn_stack_del(result_stack);
						return INFIX_SYNTAX_ERROR;
					}
				}
				//pop the ( in the operator stack )
				rpn_stack_pop(operator_stack);
			}
			else if (rpn_stack_empty(operator_stack) || *(char*) rpn_stack_peek(operator_stack) == '('){
				rpn_stack_push(operator_stack, (void* ) token[i]);
			}
			else {
				//case 1: previous operator has more precedence OR THE SAME PRECEDENCE
				char* ptr = (char*) rpn_stack_peek(operator_stack);
				char stack_op = *ptr;
				while (!rpn_stack_empty(operator_stack)
				&& *(char*) rpn_stack_peek(operator_stack) != '('

				&& infix_operator_precedence(op) <= infix_operator_precedence(* (char*) rpn_stack_peek(operator_stack))){
					rpn_stack_push(result_stack, rpn_stack_pop(operator_stack));
				}
				rpn_stack_push(operator_stack, (void*) token[i]);


				/*if (infix_operator_precedence(op) <= infix_operator_precedence(stack_op)){
					rpn_stack_push(result_stack, rpn_stack_pop(operator_stack));
					rpn_stack_push(operator_stack, (void*) token[i]);
				}
				//case 2:  new op has more precedence
				else{
					rpn_stack_push(result_stack, (void*) token[i]);
				}*/
			}
		}
		else {
			//need to print and exit here because I'm lazy and adhering to the api
			printf("infix: invalid token \'%s\'\n", token[i]);

			rpn_stack_del(operator_stack);
			rpn_stack_del(result_stack);
			return INFIX_INVALID_TOKEN;
		}
	}
	//add all missing operators
	while (!rpn_stack_empty(operator_stack)){
		//printf("pushing operator: %c\n", *(char*)rpn_stack_peek(operator_stack));
		rpn_stack_push(result_stack, rpn_stack_pop(operator_stack));
	}
	// this is a convoluted mess but idc it works
	const char* end_res = NULL;
	rpn_stack_push(result_stack, (void*) end_res);
	if (DEBUG){
		int count = 0;
		for (int i = 0; result_stack->datapointers[i] != NULL; i++ ){
			printf("%s ", (char*)result_stack->datapointers[i]);
			count++;
		}
		printf("count is: %d\n", count);
	}
	char** rpn_tokens = (char**) result_stack->datapointers;
	int res =  rpn_eval_token(rpn_tokens, result);
	rpn_stack_del(result_stack);
	rpn_stack_del(operator_stack);
	return res;
}