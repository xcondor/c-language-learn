#include <stdio.h>

int main() {
    int x = 10;
    int *ptr = &x;

    printf("x 的值为：%d\n", x);
    printf("*ptr 的值为：%d\n", *ptr);

    *ptr = 20;
    printf("x 的值现在为：%d\n", x);

    return 0;
}