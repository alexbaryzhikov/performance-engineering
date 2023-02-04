#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>

using std::cout;
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::microseconds;

#define N 4096

double A[N][N];
double B[N][N];
double C[N][N];

void initialize_matrices() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = (double)rand() / (double)RAND_MAX;
            B[i][j] = (double)rand() / (double)RAND_MAX;
            C[i][j] = 0;
        }
    }
}

/* Basic version */
void multiply_matrices_0(int n) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

/* Optimizations: loop order  */
void multiply_matrices_1(int n) {
    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < N; ++k) {
            for (int j = 0; j < N; ++j) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

/* Optimizations: loop order, parallel loop  */
void multiply_matrices_2(int n) {
    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < N; ++k) {
            for (int j = 0; j < N; ++j) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main() {
    initialize_matrices();
    auto t_begin = high_resolution_clock::now();
    multiply_matrices_1(4096);
    auto t_end = high_resolution_clock::now();
    cout << duration_cast<microseconds>(t_end - t_begin).count() << " µs\n";
}