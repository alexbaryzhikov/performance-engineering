#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sum(int* a, size_t n) {
    int sum = 0;
    size_t i = 0, j;
    if (n > 3) {
        for (; i < n - 3; i += 4) {
            sum += a[i];
            sum += a[i + 1];
            sum += a[i + 2];
            sum += a[i + 3];
        }
    }
    for (j = i; j < n; ++j) {
        sum += a[j];
    }
    return sum;
}

int rand_int(int from, int to) { return from + (to - from + 1) * (rand() / (double)RAND_MAX); }

int main(int argc, char const* argv[]) {
    int n = 99;
    int* a = (int*)malloc(sizeof(int) * n);
    srand(time(0));
    printf("[");
    for (size_t i = 0; i < n; ++i) {
        if (i) printf(" ");
        a[i] = rand_int(0, 2);
        printf("%d", a[i]);
    }
    printf("]\n");
    printf("sum=%d\n", sum(a, n));
}
