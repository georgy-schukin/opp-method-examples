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

    Vector A(N*N);
    Vector b(N), x(N), x_next(N);
    
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

    for (int i = 0; i < N; i++) {
        x[i] = 0.0;
    }

    double norm = 0.0;
    int iter = 0;

    do {
        norm = 0.0;

        for (int i = 0; i < N; i++) {
            double sum = 0.0;
            for (int j = 0; j < i; j++) {
                sum += A[i*N + j]*x[j];
            }
            for (int j = i + 1; j < N; j++) {
                sum += A[i*N + j]*x[j];
            }
            x_next[i] = (b[i] - sum)/A[i*N + i];
            norm = fmax(norm, fabs(x_next[i] - x[i]));           
        }              
        
        x = x_next;
        iter++;
    } while ((norm > eps) && (iter < max_iter));

    std::cout << "Norm = " << norm << ", iter = " << iter << std::endl;

    return 0;
}
