#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    const int N = (argc > 1 ? atoi(argv[1]) : 13);

    int a[N], b[N];

    for (int i = 0; i < N; i++) {
        a[i] = 0;
        b[i] = 0;
    }

    #pragma omp parallel shared(a, b)
    {
        #pragma omp for schedule(static) nowait
        for (int i = 0; i < N; i++) {
            a[i] = i;
        }
        #pragma omp for schedule(static) nowait
        for (int i = 0; i < N; i++) {
            b[i] = a[i]*a[i];
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");

    return 0;
}
