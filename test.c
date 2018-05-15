#include <stdio.h>


int main() {
    int a = 0xffffffff;
    char b[4] = "abc";

    printf("a = %d, b = %s\n", a, b);
    printf("b[0] = %d\n", b[0]);
    return 0;
}