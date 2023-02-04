#include <cilk/cilk.h>

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

/*
    Basic version
    Time to run: 26,3296,414 µs
*/
void multiply_matrices_0() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

/*
    Optimizations: loop order
    Time to run: 14,209,655 µs
*/
void multiply_matrices_1() {
    for (int i = 0; i < N; ++i) {
        for (int k = 0; k < N; ++k) {
            for (int j = 0; j < N; ++j) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

/*
    Optimizations: loop order, parallel loop
    Time to run: 2,563,214 µs
*/
void multiply_matrices_2() {
    cilk_for(int i = 0; i < N; ++i) {
        for (int k = 0; k < N; ++k) {
            for (int j = 0; j < N; ++j) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main(int argc, char* argv[]) {
    int variant = 0;
    if (argc > 1) {
        variant = atoi(argv[1]);
    }

    initialize_matrices();

    auto t_begin = high_resolution_clock::now();
    switch (variant) {
        case 0:
            multiply_matrices_0();
            break;
        case 1:
            multiply_matrices_1();
            break;
        case 2:
            multiply_matrices_2();
            break;
    }
    auto t_end = high_resolution_clock::now();

    cout << duration_cast<microseconds>(t_end - t_begin).count() << " µs\n";
}