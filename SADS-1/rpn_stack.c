#include "rpn_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
//
// Created by osobiehl on 18.02.21.
//


static inline void verify_stack(rpn_stack_t* s){
	if (!s){
		perror("null stack!");
		exit(EXIT_FAILURE);
	}
	else if (s->current < -1){
		perror("invalid stack index!");
		exit(EXIT_FAILURE);
	}
	else if (s->datapointers == NULL){
		perror("data pointers are null!");
		exit(EXIT_FAILURE);
	}
}
static inline void extend(rpn_stack_t* s){
	s-> size *= 2;
	s->datapointers = (void**)realloc(s->datapointers, s->size * sizeof(void*));
	if (!s->datapointers ){
		perror("out of memory!");
		exit(EXIT_FAILURE);
	}
}
//no shrink method, xd
rpn_stack_t*
rpn_stack_new(){
	rpn_stack_t* res = (rpn_stack_t*) malloc(sizeof(rpn_stack_t));
	if (!res){
		perror("out of memory!");
		exit(EXIT_FAILURE);
	}
	res->size = 10;
	res->current = -1;
	res->datapointers = (void**)malloc(sizeof(void*)*10);

	if (!res->datapointers){
		perror("not enough memory!\n");
		exit(EXIT_FAILURE);
	}
	return res;
}
void
rpn_stack_push(rpn_stack_t *s, void *data){
	verify_stack(s);
	if (s->current+1 == s->size)
		extend(s);
	s->current++;
	s->datapointers[s->current] = data;

}
/**
* \brief Pop data from the top of the stack.
*
* \param s The stack to pop data from.
* \return The data or NULL if the stack is empty.
*/
void*
rpn_stack_pop(rpn_stack_t *s){
	verify_stack(s);
	if (s->current == -1){
		perror("stack underflow!");
		return NULL;
	}
	return s->datapointers[s->current--];
}
/**
* \brief Peek on the data at the top of the stack.
*
* \param s The stack to peek on.
* \return The data or NULL if the stack is empty.
*/
void*
rpn_stack_peek(rpn_stack_t *s){
	verify_stack(s);
	
	if (s->current == -1){
		return NULL;
	}

	else return s->datapointers[s->current];
}
/**
* \brief Test whether a stack is empty.
*
* \param s The stack to test.
* \return A non-zero value if the stack is empty, 0 otherwise.
*/
int
rpn_stack_empty(rpn_stack_t *s){
	verify_stack(s);
	return s->current == -1;

}
/**
* \brief Delete a stack.
*
* \param s The stack to delete.
*/
void
rpn_stack_del(rpn_stack_t *s){
	verify_stack(s);
	// NOT FREEING EACH ELEMENT TO STOP INVALID FREE
	free(s->datapointers);
	free(s);
}
