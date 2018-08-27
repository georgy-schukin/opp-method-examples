#include <omp.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>

typedef std::vector<double> Vector;

int main(int argc, char **argv) {
    const int N = (argc > 1 ? atoi(argv[1]) : 1000);

    Vector A(N*N);
    Vector b(N), x(N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i*N + j] = i + j + 1;
        }
        A[i*N + i] = N*N*(i + 1);
    }        

    for (int i = 0; i < N; i++) {
        double sum = 0.0;
        for (int j = 0; j < N; j++) {
            sum += A[i*N + j]*(j + 1);
        }
        b[i] = sum;
    }       

    // Convert matrix A to upper triangular
    for (int row = 0; row < N; row++) {
        for (int r2 = row + 1; r2 < N; r2++) {
            const double coeff = A[r2*N + row]/A[row*N + row];
            for (int col = row; col < N; col++) {
                A[r2*N + col] -= A[row*N + col]*coeff;
            }
        }
    }

    // Solve SLAE
    for (int row = N-1; row >= 0; row--) {
        double sum = 0.0;
        for (int col = row + 1; col < N; col++) {
            sum += A[row*N + col]*x[col];
        }
        x[row] = (b[row] - sum)/A[row*N + row];
    }

    // Check solution
    double norm = 0.0;
    for (int i = 0; i < N; i++) {
        double sum = 0.0;
        for (int j = 0; j < N; j++) {
            sum += A[i*N + j]*x[j];
        }
        norm = fmax(norm, fabs(sum - b[i]));
    }

    std::cout << "Norm = " << norm << std::endl;
    
    return 0;
}
