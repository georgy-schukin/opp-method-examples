#include <omp.h>
#include <stdio.h>

int main() {
    const int N = 10000;
    const int M = 10000;

    double *a = new double[N*M];
    double *b = new double[N];

    #pragma omp parallel for
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < M; i++) {
            a[j*N + i] = 1.0;
        }
    }

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        b[i] = 0.0;
    }

    #pragma omp parallel for schedule(static, 1)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            b[i] += a[j*N + i];
        }
    }

    delete[] a;
    delete[] b;

    return 0;
}
