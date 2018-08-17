#include <omp.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>

typedef std::vector<double> Vector;

int main(int argc, char **argv) {
    const int N = (argc > 1 ? atoi(argv[1]) : 1000);
    const double eps = (argc > 2 ? atof(argv[2]) : 1e-8);
    const int max_iter = (argc > 3 ? atoi(argv[3]) : 1000);

    Vector A(N*N, 0.0);
    Vector b(N, 0.0), x(N, 0.0), x_next(N, 0.0);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i*N + j] = i + j + 1;
        }
        A[i*N + i] = N*N*(i + 1);
    }

    for (int i = 0; i < N; i++) {
        double sum = 0.0;
        for (int j = 0; j < N; j++) {
            sum += A[i*N + j]*(i + 1);
        }
        b[i] = sum;
    }

    double norm = 0.0;
    int iter = 0;

    do {
        norm = 0.0;

        #pragma omp parallel for
        for (int i = 0; i < N; i++) {
            double sum = 0.0;
            for (int j = 0; j < N; j++) {
                sum += A[i*N + j]*x[j];
            }
            x_next[i] = (b[i] - sum + A[i*N + i]*x[i])/A[i*N + i];
        }

        #pragma omp parallel for reduction(max:norm)
        for (int i = 0; i < N; i++) {
            norm = fmax(norm, fabs(x_next[i] - x[i]));
        }

        x = x_next;
        iter++;
    } while ((norm > eps) && (iter < max_iter));

    std::cout << "Norm = " << norm << ", iter = " << iter << std::endl;

//    for (int i = 0; i < N; i++) std::cout << x[i] << std::endl;

    return 0;
}
