#include <pthread.h>

pthread_mutex_t m1, m2;

int main() {
    pthread_mutex_init(&m1, NULL);
    pthread_mutex_init(&m2, NULL);

    pthread_mutex_lock(&m1);
    pthread_mutex_unlock(&m2);

    pthread_mutex_destroy(&m1);
    pthread_mutex_destroy(&m2);
    return 0;
}
