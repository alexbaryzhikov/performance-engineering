#include <cilk/cilk.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
    int x = 0;
    cilk_for(int i = 0; i < 10; ++i) { x++; }
    printf("x=%d\n", x);
    return 0;
}
