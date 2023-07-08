#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

static struct timespec t0, t1;

void stopwatch_start() { clock_gettime(CLOCK_MONOTONIC, &t0); }

long stopwatch_stop() {
    clock_gettime(CLOCK_MONOTONIC, &t1);
    return (t1.tv_sec - t0.tv_sec) * 1000000L + (t1.tv_nsec - t0.tv_nsec) / 1000L;
}

void set_max_stack_limit() {
    struct rlimit l;
    getrlimit(RLIMIT_STACK, &l);
    l.rlim_cur = l.rlim_max;
    setrlimit(RLIMIT_STACK, &l);
}

void fill(double *a, size_t n) {
    srand(1234);
    while (n) {
        *(a++) = (double)rand();
        --n;
    }
}

int cmp_double(const void* a, const void* b) {
    double _a = *(const double*)a;
    double _b = *(const double*)b;
    return (_a > _b) - (_a < _b);
}

int main(int argc, char const *argv[]) {
    set_max_stack_limit();

    size_t min_n = 1, max_n = 4000001, step = 20000;
    double a[max_n];
    long ms;

    for (size_t n = min_n; n < max_n; n += step) {
        fill(a, n);
        stopwatch_start();
        qsort(a, n, sizeof(double), cmp_double);
        ms = stopwatch_stop();
        printf("[%lu, %ld],\n", n, ms);
    }

    return 0;
}
