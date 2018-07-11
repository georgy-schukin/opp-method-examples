#include <omp.h>
#include <stdio.h>

int main() {
    int a = 0;
    int num;

    #pragma omp parallel shared(a) 
    {
        num = omp_get_thread_num();
        #pragma omp atomic
        a += num;
    }

    printf("a = %d\n", a);

    return 0;
}
