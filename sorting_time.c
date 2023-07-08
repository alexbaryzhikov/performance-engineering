#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <time.h>

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

void fill(double* a, size_t n, unsigned seed) {
    srand(seed);
    while (n) {
        *a++ = (double)rand();
        --n;
    }
}

void msort(double*, size_t);

void partition(double* a, size_t n) {
    if (n < 3) return;
    size_t m = n / 2;
    msort(a, m);
    msort(a + m, n - m);
}

void merge(double* a, size_t n) {
    if (n < 2) return;
    double tmp[n];
    size_t m = n / 2, l = 0, r = m, i = 0;
    while (l < m && r < n && i < n) {
        tmp[i++] = a[l] < a[r] ? a[l++] : a[r++];
    }
    while (l < m) tmp[i++] = a[l++];
    while (r < n) tmp[i++] = a[r++];
    memcpy(a, tmp, n * sizeof(double));
}

void msort(double* a, size_t n) {
    partition(a, n);
    merge(a, n);
}

int cmp_double(const void* a, const void* b) {
    double _a = *(const double*)a;
    double _b = *(const double*)b;
    return (_a > _b) - (_a < _b);
}

void assert_equal(double* a, double* b, size_t n) {
    while (n) {
        if (*a++ != *b++) {
            fprintf(stderr, "Assertion failed: arrays are not equal.\n");
            exit(1);
        }
        --n;
    }
}

void test_msort() {
    size_t min_n = 1, max_n = 20000;
    double a[max_n], b[max_n];

    for (size_t n = min_n; n < max_n; n *= 2) {
        fill(a, n, time(NULL));
        memcpy(b, a, n * sizeof(double));
        qsort(a, n, sizeof(double), cmp_double);
        msort(b, n);
        assert_equal(a, b, n);
    }

    printf("Tests passed.\n");
}

#define MIN_N 1
#define MAX_N 4000001
#define STEP 20000
#define SEED 14400

void measure_qsort_time() {
    double a[MAX_N];
    long ms;

    for (size_t n = MIN_N; n < MAX_N; n += STEP) {
        fill(a, n, SEED);
        stopwatch_start();
        qsort(a, n, sizeof(double), cmp_double);
        ms = stopwatch_stop();
        printf("[%lu, %ld],\n", n, ms);
    }
}

void measure_msort_time() {
    double a[MAX_N];
    long ms;

    for (size_t n = MIN_N; n < MAX_N; n += STEP) {
        fill(a, n, SEED);
        stopwatch_start();
        msort(a, n);
        ms = stopwatch_stop();
        printf("[%lu, %ld],\n", n, ms);
    }
}

int main(int argc, char const* argv[]) {
    set_max_stack_limit();
    if (argc < 2) {
        test_msort();
    } else if (!strcmp(argv[1], "qsort")) {
        measure_qsort_time();
    } else if (!strcmp(argv[1], "msort")) {
        measure_msort_time();
    }
    return 0;
}
