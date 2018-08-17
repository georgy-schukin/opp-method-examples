#include <omp.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>

typedef std::vector<double> Vector;

Vector multMatrixVector(const Vector &m, const Vector &v) {
    const int size = v.size();
    Vector result(size, 0.0);
    #pragma omp parallel for shared(m, v, result)
    for (int i = 0; i < size; i++) {
        double s = 0.0;
        for (int j = 0; j < size; j++) {
            s += m[i*size + j]*v[j];
        }
        result[i] = s;
    }
    return result;
}

Vector combineVectors(const Vector &v1, double coeff, const Vector &v2) {
    const int size = v1.size();
    Vector result(size, 0.0);
    #pragma omp parallel for shared(v1, v2, coeff, result)
    for (int i = 0; i < size; i++) {
        result[i] = v1[i] + coeff*v2[i];
    }
    return result;
}

double dotProduct(const Vector &v1, const Vector &v2) {
    const int size = v1.size();
    double result = 0.0;
    #pragma omp parallel for shared(v1, v2) reduction(+:result)
    for (int i = 0; i < size; i++) {
        result += v1[i]*v2[i];
    }
    return result;
}

double vectorNorm(const Vector &v) {
    return sqrt(dotProduct(v, v));
}

int main(int argc, char **argv) {
    const int N = (argc > 1 ? atoi(argv[1]) : 1000);

    Vector A(N*N, 0.0);
    Vector b(N, 1.0), x(N, 0.0);

    #pragma omp parallel for
    for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) {
        A[i*N + j] = i + j + 1;
    }

    Vector r = combineVectors(b, -1.0, multMatrixVector(A, x));
    Vector p = r;

    const double eps = 1e-8;
    double norm = 1.0;
    int iter = 0;

    do {
        Vector rOld = r;
        Vector Ap = multMatrixVector(A, p);
        const double alpha = dotProduct(r, r)/dotProduct(p, Ap);
        x = combineVectors(x, alpha, p);
        r = combineVectors(rOld, -alpha, Ap);
        norm = vectorNorm(r);
        const double beta = dotProduct(r, r)/dotProduct(rOld, rOld);
        p = combineVectors(r, beta, p);        
        iter++;
    } while (norm > eps);

    std::cout << "Norm = " << norm << ", iter = " << iter << std::endl;

    for (int i = 0; i < N; i++) {
        std::cout << x[i] << std::endl;
    }

    return 0;
}
