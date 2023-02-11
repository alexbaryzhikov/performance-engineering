#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define M 10
#define N 5
#define FILL_THRESHOLD 0.1

typedef struct Compressed_sparse_row {
    int n;        // number of rows
    int nnz;      // number of non-zeros
    int *row;     // n + 1 elements
    int *col;     // nnz elements
    double *val;  // nnz elements
} Csr_t;

void to_csr(Csr_t *csr, double matrix[M][N]) {
    int *row = malloc(sizeof(int) * (M + 1));
    int *col = malloc(sizeof(int) * M * N);
    double *val = malloc(sizeof(double) * M * N);

    row[0] = 0;
    int nnz = 0;
    for (int i = 0; i < M; ++i) {
        row[i + 1] = row[i];
        for (int j = 0; j < N; ++j) {
            if (matrix[i][j]) {
                ++row[i + 1];
                col[nnz] = j;
                val[nnz] = matrix[i][j];
                ++nnz;
            }
        }
    }

    col = realloc(col, sizeof(int) * nnz);
    val = realloc(val, sizeof(double) * nnz);

    csr->n = M;
    csr->nnz = nnz;
    csr->row = row;
    csr->col = col;
    csr->val = val;
}

void print_csr(Csr_t *csr) {
    printf("Compressed_sparse_row {\n");
    printf("    row=[");
    for (int i = 0; i <= csr->n; ++i) {
        if (i) printf(" ");
        printf("%d", csr->row[i]);
    }
    printf("]\n");
    printf("    col=[");
    for (int i = 0; i < csr->nnz; ++i) {
        if (i) printf(" ");
        printf("%6d", csr->col[i]);
    }
    printf("]\n");
    printf("    val=[");
    for (int i = 0; i < csr->nnz; ++i) {
        if (i) printf(" ");
        printf("%.4f", csr->val[i]);
    }
    printf("]\n");
    printf("}\n");
}

double randf() { return rand() / (double)RAND_MAX; }

void fill_sparce_matrix(double matrix[M][N]) {
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (randf() < FILL_THRESHOLD) {
                matrix[i][j] = randf();
            } else {
                matrix[i][j] = 0;
            }
        }
    }
}

void print_matrix(double matrix[M][N]) {
    for (int i = 0; i < M; ++i) {
        printf("[");
        for (int j = 0; j < N; ++j) {
            if (j) printf(" ");
            if (matrix[i][j]) {
                printf("%.4f", matrix[i][j]);
            } else {
                printf("%6.0f", matrix[i][j]);
            }
        }
        printf("]\n");
    }
}

void multiply_matrix(Csr_t *csr, double vector[N], double result[M]) {
    for (int i = 0; i < csr->n; ++i) {
        result[i] = 0;
        for (int j = csr->row[i]; j < csr->row[i + 1]; ++j) {
            result[i] += csr->val[j] * vector[csr->col[j]];
        }
    }
}

void fill_vector(int n, double vector[n]) {
    for (int i = 0; i < n; ++i) {
        vector[i] = randf();
    }
}

void print_vector(int n, double vector[n]) {
    printf("[");
    for (int i = 0; i < n; ++i) {
        if (i) printf(" ");
        printf("%.4f", vector[i]);
    }
    printf("]\n");
}

int main() {
    double matrix[M][N];
    fill_sparce_matrix(matrix);

    print_matrix(matrix);
    printf("\n");

    Csr_t csr;
    to_csr(&csr, matrix);

    print_csr(&csr);
    printf("\n");

    double vector[N];
    fill_vector(N, vector);

    printf("vector=");
    print_vector(N, vector);
    printf("\n");

    double mult_result[M];
    multiply_matrix(&csr, vector, mult_result);

    printf("mult_result=");
    print_vector(M, mult_result);
    printf("\n");
}
