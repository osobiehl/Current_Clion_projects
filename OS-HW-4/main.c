#include <stdio.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int debug = 1;
char coins[20+1];
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int P=100, N=10000;

void run_threads(int n, void* (*proc)(void *)){
	pthread_t pids[P];
	for (int i = 0; i < P; i++){
		int rc = pthread_create(&pids[i], NULL, proc, NULL);
		if (rc){
			perror("pthread_create() failed");
			exit(-1);
		}
	}
	for (int i =0; i < P; i++){
		if (pids[i]){
			int rc = pthread_join(pids[i], NULL);
			if (rc){
				perror("pthread_join() failed");
				exit(-1);
			}
		}
	}
}

static double
timeit(int n, void* (*proc)(void *))
{
	clock_t t1, t2;
	t1 = clock();
	run_threads(n, proc);
	t2 = clock();
	return ((double) t2 - (double) t1) / CLOCKS_PER_SEC * 1000;
}

void* flip_person(void* ignore){
	pthread_mutex_lock(&mutex);
	srand(time(NULL));
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < N; j++){
			coins[i] = ( rand() % 2 == 0 ? 'O' : 'X');
			if (debug) printf("coin number %d, value: %c\n", i, coins[i]);
		}
	}
	if (debug) printf("coins: %s\n", coins);
	pthread_mutex_unlock(&mutex);
	return NULL;
}



int main(int argc, char* argv[]) {
	printf("Hello, World!\n");
	int c;

	while ((c = getopt (argc, argv, "p:n:")) != -1)
		switch (c)
		{
			case 'p':
				P = atoi(argv[optind-1]);
				break;
			case 'n':
				N = atoi(argv[optind-1]);
				break;
			case '?':
				if (optopt == 'c')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr,
							 "Unknown option character `\\x%x'.\n",
							 optopt);
				return 1;
			default:
				abort ();
		}
	if (debug)
		printf("N: %d, P: %d\n", N, P);
	double res1 = timeit(N, flip_person);
	printf("time is: %lf", res1);

//strategy one




	return 0;
}
