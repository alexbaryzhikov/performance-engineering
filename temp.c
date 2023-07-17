#include <stdio.h>

int main(int argc, char const *argv[]) {
    printf("%lu bytes\n", sizeof(double) * 32 * 32);
    return 0;
}
