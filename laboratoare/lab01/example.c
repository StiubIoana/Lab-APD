#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *f(void *arg) {
  	long id = (long)arg;
	
	for (int i = 0 ; i <= 100; ++i) {
  	printf("Hello World din thread-ul %ld, iteratia %d\n", id, i);
	
	}
  	pthread_exit(NULL);
}

void *f2(void *arg) {
  	long id = (long)arg;
	
	for (int i = 0 ; i <= 100; ++i) {
  	printf("Bye World din thread-ul %ld, iteratia %d\n", id, i);
	
	}
  	pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
	long cores = sysconf(_SC_NPROCESSORS_CONF);
	long num_threads = 2;

	int onlyTwoThreads = 1;

	pthread_t threads[num_threads];
  	int r;
  	long id;
  	void *status;

	if (onlyTwoThreads) {
		num_threads = 2;
		if (pthread_create(&threads[0], NULL, f, (void *)0)) {
				printf("Eroare la crearea thread-ului %d\n", 0);
				exit(-1);
			}
		if (pthread_create(&threads[1], NULL, f2, (void *)1)) {
				printf("Eroare la crearea thread-ului %d\n", 1);
				exit(-1);
			}
	} else {
		for (id = 0; id < num_threads; id++) {
			r = pthread_create(&threads[id], NULL, f, (void *)id);

			if (r) {
				printf("Eroare la crearea thread-ului %ld\n", id);
				exit(-1);
			}
		}
	}

  	for (id = 0; id < num_threads; id++) {
		r = pthread_join(threads[id], &status);

		if (r) {
	  		printf("Eroare la asteptarea thread-ului %ld\n", id);
	  		exit(-1);
		}
  	}

  	pthread_exit(NULL);
}
