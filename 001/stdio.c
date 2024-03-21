#include <stdio.h>

int main() {
    int a, b, sum;
    printf("请输入两个整数：");
    scanf("%d%d", &a, &b);
    sum = a + b;
    printf("两个整数的和为：%d\n", sum);
    return 0;
}