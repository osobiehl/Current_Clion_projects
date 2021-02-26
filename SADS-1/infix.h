/*
* expr/src/infix.h --
*/
/** @file */
#ifndef _INFIX_H
#define _INFIX_H
#define INFIX_OK 0
/** INFIX evaluation failed due to an invalid token. */
#define INFIX_INVALID_TOKEN -10
/** INFIX evaluation failed due to a missing operand. */
#define INFIX_MISSING_OPERAND -11
/** INFIX evaluation failed due to a missing operator. */
#define INFIX_MISSING_OPERATOR -12
/** INFIX evaluation failed due to an arithmetic error. */
#define INFIX_ARITHMETIC_ERROR -13
/* INFIX evaluation failed due to a syntax error */
#define INFIX_SYNTAX_ERROR -14
/**
* \brief Evaluate an expression in infix notation.
*
* This functions takes an array of strings that are interpreted as
* tokens of an expression in infix notation. The function returns the
* results as a string via the second argument. The result is
* allocated using malloc() and must be freed by the caller of this
* function. Note that the function may return a NULL pointer if no
* result was calculated. The return value of the function indicates
* whether the evaluation of the expression in reverse polish notation
* was successful or there were any errors.
*
* \param token Tokens of an expression (NULL-terminated array).
* \param result Pointer to the string holding the result (malloced).
* \result One of the error codes defined above.
*/
char* infix_strerror(int errnum);
int expr_infix_eval_token(char *token[], char **result);
/**
* \brief Evaluate an expression in infix notation.
*
* This function splits the expression contained in the string expr
* into an array of strings and then interpretes the array as tokens
* of an expression in infix notation. The function returns
* the results as a string via the second argument. The result is
* allocated using malloc() and must be freed by the caller of this
* function. Note that the function may return a NULL pointer if no
* result was calculated. The return value of the function indicates
* whether the evaluation of the expression in reverse polish notation
* was successful or there were any errors.
*
* \param expr The expression (whitespace separated numbers and operators)
* \param result Pointer to the string holding the result (malloced).
* \result One of the error codes defined above.
*/
int expr_infix_eval(const char *expr, char **result);
#endif