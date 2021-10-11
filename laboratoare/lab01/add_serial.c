#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

/*
    schelet pentru exercitiul 5
*/

int* arr;
int array_size, num_threads;

typedef struct {
    int start, end;
    int id;
} Thread_arg;

void *f(void *arg) {
  	Thread_arg *args = (Thread_arg*)arg;
	int start = args->start;
    int end = args->end;
    int id = args->id;

  	printf("Thread-ul %d [%d, %d]\n", id, start, end);
	for (int i = start; i < end; ++i) {
        arr[i] += 100;
    }

  	pthread_exit(NULL);
}

int min (int a, int b) {
    return a < b ? a : b;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("Specificati dimensiunea array-ului\n");
        exit(-1);
    }

    array_size = atoi(argv[1]);
    num_threads = atoi(argv[2]);

    arr = malloc(array_size * sizeof(int));
    for (int i = 0; i < array_size; i++) {
        arr[i] = i;
    }

    for (int i = 0; i < array_size; i++) {
        printf("%d", arr[i]);
        if (i != array_size - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }

    // TODO: aceasta operatie va fi paralelizata

	pthread_t threads[num_threads];
    Thread_arg thread_args[num_threads];
    for (int i = 0 ; i < num_threads; ++i) {
        int start = (i) * (double)array_size / num_threads;
        int end = min((i + 1) * (double)array_size / num_threads, array_size);
        
        thread_args[i].start = start;
        thread_args[i].end = end;
        thread_args[i].id = i;

        int r = pthread_create(&threads[i], NULL, f, (void *)&thread_args[i]);

		if (r) {
			printf("Eroare la crearea thread-ului %d\n", i);
			exit(-1);
		}
    }

    void *status;
    int id;
    for (id = 0; id < num_threads; id++) {
		int r = pthread_join(threads[id], &status);

		if (r) {
	  		printf("Eroare la asteptarea thread-ului %d\n", id);
	  		exit(-1);
		}
  	}


    for (int i = 0; i < array_size; i++) {
        printf("%d", arr[i]);
        if (i != array_size - 1) {
            printf(" ");
        } else {
            printf("\n");
        }
    }

  	return 0;
}
