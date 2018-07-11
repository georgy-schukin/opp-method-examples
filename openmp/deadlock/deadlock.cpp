#include <omp.h>
#include <stdio.h>

int main() {
    int a = 0;

    omp_lock_t lock1, lock2;

    omp_init_lock(&lock1);
    omp_init_lock(&lock2);

#pragma omp parallel sections shared(a)
{
    #pragma omp section 
    {
        omp_set_lock(&lock1);
        omp_set_lock(&lock2);

        a++;

        omp_unset_lock(&lock1);
        omp_unset_lock(&lock2);
    }

    #pragma omp section 
    {
        omp_set_lock(&lock2);
        omp_set_lock(&lock1);

        a++;

        omp_unset_lock(&lock1);
        omp_unset_lock(&lock2);
    }
}

    omp_destroy_lock(&lock1);
    omp_destroy_lock(&lock2);

	printf("a = %d\n", a);

    return 0;
}
