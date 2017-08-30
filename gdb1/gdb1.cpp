#include <pthread.h>
#include <stdio.h>
#include <queue>

using namespace std;

typedef queue<int*> Queue;

bool is_empty(Queue *q) {
    return q->empty();
}

pthread_barrier_t barrier;

void* thread_func(void* arg) {
    pthread_barrier_wait(&barrier);

    Queue *q = static_cast<Queue*>(arg);
    while (!q->empty()) {
        int *task = q->front();
        q->pop();
    //    printf("%d\n", *task);
        delete task;
    }
    return 0;
}

int main() {
    Queue q;
    
    for (int i = 0; i < 100; i++) {
        q.push(new int(i));
    }

	pthread_t t[10];

    int num_of_threads = 8;

    pthread_barrier_init(&barrier, NULL, num_of_threads);

    for (int i = 0; i < num_of_threads; i++) {
	    pthread_create(&t[i], NULL, thread_func, &q);
    }

    for (int i = 0; i < num_of_threads; i++) {
	    pthread_join(t[i], NULL);
    }

    pthread_barrier_destroy(&barrier);

    return 0;
}
