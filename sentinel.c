#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

bool overflow(int *a, size_t n) {
    int sum = 0;
    for (size_t i = 0; i < n; ++i) {
        sum += a[i];
        if (sum < a[i]) return true;
    }
    return false;
}

bool overflow_opt(int *a, size_t n) {
    a[n] = INT_MAX;
    int sum = a[0];
    size_t i = 0;
    while (sum >= a[i]) {
        sum += a[++i];
    }
    return i < n;
}

int main(int argc, char const *argv[]) {
    size_t n = 2;
    int *a = (int *)malloc(sizeof(int) * (n + 1));
    srand(time(0));
    printf("[");
    for (size_t i = 0; i < n; ++i) {
        if (i) printf(" ");
        a[i] = rand();
        printf("%d", a[i]);
    }
    printf("]\n");
    printf("overflow=%d\n", overflow(a, n));
    printf("overflow_opt=%d\n", overflow_opt(a, n));
}
