#include <stdio.h>
#include "rpn.h"
#include <stdlib.h>
#include <memory.h>
#include <string.h>



int main(int argc, char* argv[]) {

	if ( argc > 1 )
	{
		char* out;
		int res = rpn_eval_token(&argv[1], &out);
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
			rpn_eval_expr(line, &out);
			puts(out);

	}

}
