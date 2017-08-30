#include <pthread.h>
#include <stdio.h>

int queue[100];
const int queue_size = 100;
int counter = 0;

void* thread_func(void*) {
    int sum = 0;
    while (counter < queue_size) {
        int value = queue[counter];
 //       printf("%d\n", value);
        sum += value;
        counter++;
    }
    return 0;
}

int main() {
    for (int i = 0; i < queue_size; i++) {
        queue[i] = i;
    }

    counter = 0;

	pthread_t t[10];

    int num_of_threads = 4;

    for (int i = 0; i < num_of_threads; i++) {
	    pthread_create(&t[i], NULL, thread_func, NULL);
    }

    for (int i = 0; i < num_of_threads; i++) {
	    pthread_join(t[i], NULL);
    }

    return 0;
}
