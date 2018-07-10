#include <pthread.h>

int a = 0;

void* thread_func(void*) {
    a++;
    return 0;
}

int main() {
    pthread_t t;
    pthread_create(&t, NULL, thread_func, NULL);
    a++;
    pthread_join(t, NULL);
    return 0;
}
