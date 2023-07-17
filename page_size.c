#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    int page_size = getpagesize();
    printf("Page size is %d bytes.\n", page_size);
    return 0;
}
