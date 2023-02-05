#include <cilk/cilk.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

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
    Time to run: 255,929 µs
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
    Optimizations: reordered loops
    Time to run: 14,431 µs
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
    Optimizations: reordered loops, parallel loops
    Time to run: 2,512 µs
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

/*
    Optimizations: reordered loops, parallel loops, tiling
    Time to run: 36 µs
*/

#define BLOCK_SIZE 64

void multiply_matrices_3() {
    cilk_for(int ih = 0; ih < N; ih += BLOCK_SIZE) {
        cilk_for(int jh = 0; jh < N; jh += BLOCK_SIZE) {
            for (int kh = 0; kh < N; kh += BLOCK_SIZE) {
                for (int il = 0; il < BLOCK_SIZE; ++il) {
                    for (int kl = 0; kl < BLOCK_SIZE; ++kl) {
                        for (int jl = 0; jl < BLOCK_SIZE; ++jl) {
                            C[ih + il][jh + jl] = A[ih + il][kh + kl] * B[kh + kl][jh + jl];
                        }
                    }
                }
            }
        }
    }
}


/*
    Optimizations: reordered loops, parallel loops, recursive tiling
    Time to run: 2,240 µs
*/

#define THRESHOLD 128
#define X(M, r, c) (M + (r * (n_##M) + c) * (n / 2))

void mm_base(
    double * restrict C, int n_C,
    double * restrict A, int n_A,
    double * restrict B, int n_B,
    int n
) {
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            for (int j = 0; j < n; ++j) {
                C[i * n_C + j] += A[i * n_A + k] * B[k * n_B + j];
            }
        }
    }
}

void mm_dac(
    double * restrict C, int n_C,
    double * restrict A, int n_A,
    double * restrict B, int n_B,
    int n
) {
    if (n <= THRESHOLD) {
        mm_base(C, n_C, A, n_A, B, n_B, n);
    } else {
        cilk_spawn mm_dac(X(C, 0, 0), n_C, X(A, 0, 0), n_A, X(B, 0, 0), n_B, n / 2);
        cilk_spawn mm_dac(X(C, 0, 1), n_C, X(A, 0, 0), n_A, X(B, 0, 1), n_B, n / 2);
        cilk_spawn mm_dac(X(C, 1, 0), n_C, X(A, 1, 0), n_A, X(B, 0, 0), n_B, n / 2);
        mm_dac(X(C, 1, 1), n_C, X(A, 1, 0), n_A, X(B, 0, 1), n_B, n / 2);
        cilk_sync;
        cilk_spawn mm_dac(X(C, 0, 0), n_C, X(A, 0, 1), n_A, X(B, 1, 0), n_B, n / 2);
        cilk_spawn mm_dac(X(C, 0, 1), n_C, X(A, 0, 1), n_A, X(B, 1, 1), n_B, n / 2);
        cilk_spawn mm_dac(X(C, 1, 0), n_C, X(A, 1, 1), n_A, X(B, 1, 0), n_B, n / 2);
        mm_dac(X(C, 1, 1), n_C, X(A, 1, 1), n_A, X(B, 1, 1), n_B, n / 2);
        cilk_sync;
    }
}

void multiply_matrices_4() {
    mm_dac(C[0], N, A[0], N, B[0], N, N);
}

int main(int argc, char *argv[]) {
    int variant = 0;
    if (argc > 1) {
        variant = atoi(argv[1]);
    }

    initialize_matrices();

    struct timeval begin, end;
    gettimeofday(&begin, NULL);
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
        case 3:
            multiply_matrices_3();
            break;
        case 4:
            multiply_matrices_4();
            break;
    }
    gettimeofday(&end, NULL);
    
    long begin_ms = begin.tv_sec * 1000000L + begin.tv_usec;
    long end_ms = end.tv_sec * 1000000L + end.tv_usec;
    
    printf("%ld µs\n",  (end_ms - begin_ms) / 1000);
}