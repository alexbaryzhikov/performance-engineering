#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

struct timeval begin, end;

void time_begin() { gettimeofday(&begin, NULL); }

void time_end(const char *msg) {
    gettimeofday(&end, NULL);

    long begin_ms = begin.tv_sec * 1000000L + begin.tv_usec;
    long end_ms = end.tv_sec * 1000000L + end.tv_usec;

    if (msg) {
        printf("%s: %ld µs\n", msg, (end_ms - begin_ms) / 1000);
    } else {
        printf("%ld µs\n", (end_ms - begin_ms) / 1000);
    }
}

void scale(double *x, double *y, int n) {
    for (int i = 0; i < n; ++i) {
        y[i] = x[i] * exp(sqrt(M_PI / 2));
    }
}

void scale_opt(double *x, double *y, int n) {
    double factor = exp(sqrt(M_PI / 2));
    for (int i = 0; i < n; ++i) {
        y[i] = x[i] * factor;
    }
}

int main(int argc, char const *argv[]) {
    int n = 1000000;
    double *x = (double *)malloc(sizeof(double) * n);
    double *y = (double *)malloc(sizeof(double) * n);
    for (int i = 0; i < n; ++i) {
        x[i] = (double)rand() / (double)RAND_MAX;
    }

    time_begin();
    scale(x, y, n);
    time_end("No optimizations");

    time_begin();
    scale_opt(x, y, n);
    time_end("Hoisting");

    return 0;
}
