#include <stdio.h>
int main() {
    int number = 10;
    int *pointer = &number;
    printf("变量的值为：%d\n", number);
    printf("指针的值为：%p\n", pointer);
    return 0;
}