#include <limits.h>
#include <stdio.h>

#define N 50
#define K 50

long long C[N + 1][K + 1];

void precompute_c() {
    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= K; ++j) {
            if (j > i) {
                C[i][j] = 0;
            } else if (j == 0 || j == i) {
                C[i][j] = 1;
            } else {
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            }
        }
    }
}
 
int main() {
    precompute_c();

    int n = -1, k = -1;

    for (int i = 0; i <= N; ++i) {
        for (int j = 0; j <= K; ++j) {
            if (n == -1 && C[i][j] > INT_MAX) {
                n = i, k = j;
            }
            printf(" %16lld", C[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    printf("Integer overflow at n=%d k=%d\n", n, k);
}
