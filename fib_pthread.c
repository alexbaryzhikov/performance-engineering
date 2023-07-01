#include <inttypes.h>
#include <pthread.h>
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

typedef struct {
    int64_t input;
    int64_t output;
} thread_args_t;

void* thread_func(void* arg) {
    thread_args_t* ta = (thread_args_t*)arg;
    ta->output = fib(ta->input);
    return NULL;
}

int main(int argc, char const* argv[]) {
    pthread_t thread;
    thread_args_t ta;
    int status;
    int64_t result;

    if (argc < 2) return 1;
    int64_t n = strtoul(argv[1], NULL, 0);

    timer_start();
    ta.input = n - 1;
    status = pthread_create(&thread, NULL, thread_func, &ta);
    if (status != 0) return 1;
    result = fib(n - 2);
    status = pthread_join(thread, NULL);
    if (status != 0) return 1;
    result += ta.output;
    timer_stop();

    printf("Fibonacci of %" PRId64 " is %" PRId64 ".\n", n, result);
    return 0;
}
