/*
 * philosophers/phil-templ.c --
 *
 *	A template for solutions of the dining philosophers problem.
 */

#define _POSIX_C_SOURCE 200809L

#include <pthread.h>
#include <stdio.h>
#include <time.h>

#define PHIL_STATE_THINKING	0x01
#define PHIL_STATE_HUNGRY	0x02
#define PHIL_STATE_EATING	0x03

#define LIFE_TIME (365 * 3 * 1)

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
typedef struct philosopher {
	char *name;
	int state;
	unsigned meals;
	struct philosopher *left;
	struct philosopher *right;
	pthread_t tid;
	pthread_mutex_t  lock;
} philosopher_t;

const struct timespec eat_time   = { .tv_sec = 0, .tv_nsec = 4321 };
const struct timespec think_time = { .tv_sec = 0, .tv_nsec = 1234 };

static void
think(philosopher_t *phil)
{
	printf("%s is thinking\n", phil->name);
	nanosleep(&think_time, NULL);
}

static void
eat(philosopher_t *phil)
{
	phil->meals++;
	printf("%s is eating meal #%d\n", phil->name, phil->meals);
	nanosleep(&eat_time, NULL);
}
static void test(philosopher_t *phil)
{

}

static void
acquire_forks(philosopher_t *phil)
{
	pthread_mutex_lock(&mutex);
	phil->state = PHIL_STATE_HUNGRY;
	printf("%s is hungry\n", phil->name);
	test(phil);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_lock(&phil->lock);
}



static void
release_forks(philosopher_t *phil)
{
	pthread_mutex_lock(&mutex);
	phil->state = PHIL_STATE_THINKING;
	test(phil->right);
	test(phil->left);
	pthread_mutex_unlock(&mutex);
}

static void*
enjoy_life(void *arg)
{
	philosopher_t *phil = (philosopher_t *) arg;

	printf("%s: %s -- %s -- %s\n",
		   phil->name, phil->left->name, phil-> name, phil->right->name);
	for (int i = 0; i < LIFE_TIME; i++) {
		think(phil);
		acquire_forks(phil);
		eat(phil);
		release_forks(phil);
	}
	return NULL;
}

int
main(int argc, char *argv[])
{
	philosopher_t phils[argc];

	for (int i = 1; i < argc; i++) {
		phils[i].name = argv[i];
		phils[i].state = PHIL_STATE_THINKING;
		phils[i].meals = 0;
		phils[i].left  = (i == 1)      ? &phils[argc-1] : &phils[i-1];
		phils[i].right = (i == argc-1) ? &phils[1]      : &phils[i+1];
		pthread_mutex_init(&phils[i].lock, NULL);
		pthread_mutex_lock(&phils[i].lock);
		(void) pthread_create(&phils[i].tid, NULL, enjoy_life, &phils[i]);
	}

	(void) pthread_exit(NULL);
	return 0;
}
