#include <pthread.h>
#include <stdio.h>

int a = 0;

pthread_mutex_t m1, m2;

void* thread_func(void*) {
    pthread_mutex_lock(&m1);
    pthread_mutex_lock(&m2);

	a++;

    pthread_mutex_unlock(&m2);
    pthread_mutex_unlock(&m1);
    return 0;
}

int main() {
    pthread_mutex_init(&m1, NULL);
    pthread_mutex_init(&m2, NULL);

	pthread_t t;
	pthread_create(&t, NULL, thread_func, NULL);

    pthread_mutex_lock(&m2);
    pthread_mutex_lock(&m1);

	a++;

    pthread_mutex_unlock(&m1);
    pthread_mutex_unlock(&m2);

	pthread_join(t, NULL);

    pthread_mutex_destroy(&m1);
    pthread_mutex_destroy(&m2);

	printf("a = %d\n", a);

    return 0;
}
