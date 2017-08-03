#include <omp.h>
#include <stdio.h>

int main() {
    int a[10];
    int i, num;

    #pragma omp parallel for private(i)
    for (i = 0; i < 10; i++) {
        num = omp_get_thread_num();
        a[i] = num;
    }

    for (i = 0; i < 10; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return 0;
}
