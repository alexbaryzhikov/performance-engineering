#include <stdio.h>
#include <stdlib.h>

void full_add(int a, int b, int c, int *sum, int *carry) {
    int test = (a << 2) | (b << 1) | c;
    switch (test) {
        case 0:
            *sum = 0;
            *carry = 0;
            break;
        case 1:
            *sum = 1;
            *carry = 0;
            break;
        case 2:
            *sum = 1;
            *carry = 0;
            break;
        case 3:
            *sum = 0;
            *carry = 1;
            break;
        case 4:
            *sum = 1;
            *carry = 0;
            break;
        case 5:
            *sum = 0;
            *carry = 1;
            break;
        case 6:
            *sum = 0;
            *carry = 1;
            break;
        case 7:
            *sum = 1;
            *carry = 1;
            break;
    }
}

int main(int argc, char const *argv[]) {
    int a = 0, b = 0, c = 0, sum, carry;
    if (argc == 4) {
        a = atoi(argv[1]);
        b = atoi(argv[2]);
        c = atoi(argv[3]);
    }

    full_add(a, b, c, &sum, &carry);

    printf("sum=%d carry=%d\n", sum, carry);
}
