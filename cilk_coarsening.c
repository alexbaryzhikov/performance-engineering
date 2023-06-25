#include <cilk/cilk.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

static struct timeval begin_time, end_time;

void timer_start() { gettimeofday(&begin_time, NULL); }

void timer_stop() {
    gettimeofday(&end_time, NULL);
    long begin_ms = begin_time.tv_sec * 1000000L + begin_time.tv_usec;
    long end_ms = end_time.tv_sec * 1000000L + end_time.tv_usec;
    printf("%ld µs\n", (end_ms - begin_ms) / 1000);
}

void vector_calc(int a[], int b[], size_t n) {
#pragma cilk grainsize 100
    cilk_for(size_t i = 0; i < n; ++i) {
        int acc = 0;
        for (size_t j = 0; j < n; ++j) {
            acc = (acc + b[j]) % a[i];
        }
        a[i] = acc;
    }
}

void fill(int v[], size_t n) {
    for (size_t i = 0; i < n; ++i) {
        v[i] = rand() * (1000.0 / RAND_MAX) + 1;
    }
}

void println(int v[], size_t n, size_t m) {
    printf("[");
    for (size_t i = 0; i < m; ++i) {
        if (i) printf(", ");
        printf("%d", v[i]);
    }
    printf(" ... ");
    for (size_t i = n - m; i < n; ++i) {
        if (i > n - m) printf(", ");
        printf("%d", v[i]);
    }
    printf("]\n");
}

#define N 100000

int main(int argc, char const *argv[]) {
    int a[N];
    fill(a, N);
    int b[N];
    fill(b, N);

    timer_start();
    vector_calc(a, b, N);
    timer_stop();

    println(a, N, 10);

    return 0;
}
