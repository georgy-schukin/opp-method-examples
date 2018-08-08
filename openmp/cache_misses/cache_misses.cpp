#include <omp.h>
#include <stdio.h>

int main() {
    const int N = 10000;

    double *a = new double[N];
    double *b = new double[N];

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        a[i] = 1.0;
    }

    for (int i = 0; i < N; i++) {
        b[i] = a[i]*2;
    }

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        b[i] = b[i] + a[i];
    }

    delete[] a;
    delete[] b;

    return 0;
}
