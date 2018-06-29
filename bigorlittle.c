#include <stdio.h>


int main() {
    int a = 1;

    if (((char *) &a)[3] == 1) {
        printf("big end");
    } else {
        printf("little end");
    }
}