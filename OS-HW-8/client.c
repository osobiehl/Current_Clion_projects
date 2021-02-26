//
// Created by osobiehl on 05.11.20.
//
#include <event2/event.h>
struct clnt_t{
	struct clnt_t* next;
	int fd;
	struct event* event;
	int games_played;
	int answered_correctly;

}typedef clnt_t;


