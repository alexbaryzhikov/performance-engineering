#include <inttypes.h>
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

int64_t fib(int64_t n) {
    if (n < 2) return n;
    return fib(n - 1) + fib(n - 2);
}

int main(int argc, char const *argv[]) {
    if (argc < 2) return 1;
    int64_t n = atoi(argv[1]);

    timer_start();
    int64_t result = fib(n);
    timer_stop();
    
    printf("Fibonacci of %" PRId64 " is %" PRId64 ".\n", n, result);
    return 0;
}
