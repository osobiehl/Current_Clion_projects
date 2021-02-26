//
// Created by osobiehl on 26.02.21.
//

#include <stdio.h>
#include "infix.h"
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include "rpn.h"



int main(int argc, char* argv[]) {

	if ( argc > 1 )
	{
		char* out;
		int res = expr_infix_eval_token(&argv[1], &out);
		if (res != RPN_OK){
			out = rpn_strerror(res);
		}
		puts(out);
		return (res == RPN_OK ?EXIT_SUCCESS : EXIT_FAILURE);

	}

	char* line = NULL;
	char* out = NULL;
	size_t len = 0;
	int nread;
	while ( -1 != (nread = getline(&line, &len, stdin)) ){
		if (!line) {
			perror("getline");
			exit(EXIT_FAILURE);
		}
		line[strlen(line) - 1] = '\0';
		int res = expr_infix_eval(line, &out);
		if (res != RPN_OK){
			out = infix_strerror(res);
		}
		if (out)
			puts(out);
	}

}
