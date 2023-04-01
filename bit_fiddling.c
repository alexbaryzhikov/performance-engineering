#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

int min(int a, int b) { return b ^ ((a ^ b) & -(a < b)); }

void merge(long* C, long* A, size_t na, long* B, size_t nb) {
    long* a_end = A + na;
    long* b_end = B + nb;
    while (A < a_end && B < b_end) {
        bool cmp = *A <= *B;
        *C++ = min(*A, *B);
        A += cmp;
        B += !cmp;
    }
    while (A < a_end) {
        *C++ = *A++;
    }
    while (B < b_end) {
        *C++ = *B++;
    }
}

/* Modular Addition. Returns (a + b) % n. */
int mod_add(int a, int b, int n) {
    int z = a + b;
    return z - (n & -(n <= z));
}

/* Round up to a power of 2. */
int round_pow2(uint64_t n) {
    --n;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n |= n >> 32;
    return ++n;
}

int least_significant_one(int x) { return x & (-x); }

int log2_debruijn64(uint64_t x) {
    static const int table[64] = {0,  1,  2,  53, 3,  7,  54, 27, 4,  38, 41, 8,  34, 55, 48, 28,
                                  62, 5,  39, 46, 44, 42, 22, 9,  24, 35, 59, 56, 49, 18, 29, 11,
                                  63, 52, 6,  26, 37, 40, 33, 47, 61, 45, 43, 21, 23, 58, 17, 10,
                                  51, 25, 36, 32, 60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13, 12};

    return table[(x * 0x022fdd63cc95386dULL) >> 58];
}

int count_ones(int x) {
    int count = 0;
    while (x) {
        x = x & (x - 1);
        count++;
    }
    return count;
}

int count_ones2(int x) {
    static const unsigned char bit_count_table[256] = {
        0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2,
        3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3,
        3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5,
        6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4,
        3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4,
        5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6,
        6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8};

    int count = 0;
    unsigned char* byte = (unsigned char*)&x;
    for (int i = 0; i < sizeof(int); i++) {
        count += bit_count_table[byte[i]];
    }
    return count;
}

int count_ones3(int x) {
    x = (x & 0x55555555) + ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x & 0x0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F);
    x = (x & 0x00FF00FF) + ((x >> 8) & 0x00FF00FF);
    x = (x & 0x0000FFFF) + ((x >> 16) & 0x0000FFFF);
    return x;
}

int count_ones4(unsigned int x) {
    return __builtin_popcount(x);
}

void test(const char* name, bool b) { printf("%s %s\n", b ? "✅" : "❌", name); }

bool equals(long* A, long* B, size_t n) {
    for (; n; --n) {
        if (*A++ != *B++) return false;
    }
    return true;
}

void run_tests() {
    int a = 213, b = 22;
    swap(&a, &b);
    test("swap(213, 22)", a == 22 && b == 213);
    a = b = 999;
    swap(&a, &b);
    test("swap(999, 999)", a == 999 && b == 999);

    test("min(54, 2)", min(54, 2) == 2);
    test("min(-54, 2)", min(-54, 2) == -54);
    test("min(999, 999)", min(999, 999) == 999);

    long A[] = {5, 23, 54, 101};
    long B[] = {1, 33, 45, 290};
    long C[8];
    long D[] = {1, 5, 23, 33, 45, 54, 101, 290};
    merge(C, A, 4, B, 4);
    test("merge({5, 23, 54, 101}, {1, 33, 45, 290})", equals(C, D, 8));

    test("mod_add(4, 2, 7)", mod_add(4, 2, 7) == 6);
    test("mod_add(4, 3, 7)", mod_add(4, 3, 7) == 0);
    test("mod_add(4, 4, 7)", mod_add(4, 4, 7) == 1);

    test("round_pow2(0)", round_pow2(0) == 0);
    test("round_pow2(1)", round_pow2(1) == 1);
    test("round_pow2(2)", round_pow2(2) == 2);
    test("round_pow2(3)", round_pow2(3) == 4);
    test("round_pow2(55)", round_pow2(55) == 64);

    test("least_significant_one(0)", least_significant_one(0b0) == 0b0);
    test("least_significant_one(1)", least_significant_one(0b1) == 0b1);
    test("least_significant_one(2)", least_significant_one(0b10) == 0b10);
    test("least_significant_one(3)", least_significant_one(0b11) == 0b1);
    test("least_significant_one(10)", least_significant_one(0b1010) == 0b10);

    test("log2_debruijn64(1)", log2_debruijn64((uint64_t)1) == 0);
    test("log2_debruijn64(1 << 1)", log2_debruijn64((uint64_t)1 << 1) == 1);
    test("log2_debruijn64(1 << 3)", log2_debruijn64((uint64_t)1 << 3) == 3);
    test("log2_debruijn64(1 << 5)", log2_debruijn64((uint64_t)1 << 5) == 5);
    test("log2_debruijn64(1 << 10)", log2_debruijn64((uint64_t)1 << 10) == 10);
    test("log2_debruijn64(1 << 20)", log2_debruijn64((uint64_t)1 << 20) == 20);
    test("log2_debruijn64(1 << 32)", log2_debruijn64((uint64_t)1 << 32) == 32);
    test("log2_debruijn64(1 << 63)", log2_debruijn64((uint64_t)1 << 63) == 63);

    test("count_ones(0b0)", count_ones(0b0) == 0);
    test("count_ones(0b1)", count_ones(0b1) == 1);
    test("count_ones(0b10)", count_ones(0b10) == 1);
    test("count_ones(0b11)", count_ones(0b11) == 2);
    test("count_ones(0b101)", count_ones(0b101) == 2);
    test("count_ones(0b1010010111)", count_ones(0b1010010111) == 6);
    test("count_ones(0b11111111)", count_ones(0b11111111) == 8);

    test("count_ones2(0b0)", count_ones2(0b0) == 0);
    test("count_ones2(0b1)", count_ones2(0b1) == 1);
    test("count_ones2(0b10)", count_ones2(0b10) == 1);
    test("count_ones2(0b11)", count_ones2(0b11) == 2);
    test("count_ones2(0b101)", count_ones2(0b101) == 2);
    test("count_ones2(0b1010010111)", count_ones2(0b1010010111) == 6);
    test("count_ones2(0b11111111)", count_ones2(0b11111111) == 8);

    test("count_ones3(0b0)", count_ones3(0b0) == 0);
    test("count_ones3(0b1)", count_ones3(0b1) == 1);
    test("count_ones3(0b10)", count_ones3(0b10) == 1);
    test("count_ones3(0b11)", count_ones3(0b11) == 2);
    test("count_ones3(0b101)", count_ones3(0b101) == 2);
    test("count_ones3(0b1010010111)", count_ones3(0b1010010111) == 6);
    test("count_ones3(0b11111111)", count_ones3(0b11111111) == 8);

    test("count_ones4(0b0)", count_ones4(0b0) == 0);
    test("count_ones4(0b1)", count_ones4(0b1) == 1);
    test("count_ones4(0b10)", count_ones4(0b10) == 1);
    test("count_ones4(0b11)", count_ones4(0b11) == 2);
    test("count_ones4(0b101)", count_ones4(0b101) == 2);
    test("count_ones4(0b1010010111)", count_ones4(0b1010010111) == 6);
    test("count_ones4(0b11111111)", count_ones4(0b11111111) == 8);
}

int main(int argc, char const* argv[]) { run_tests(); }
