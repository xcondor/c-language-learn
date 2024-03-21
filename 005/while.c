#include <stdio.h>

int main() {
    int number, sum = 0;

    printf("请输入一个正整数：");
    scanf("%d", &number);

    do {
        sum += number;
        printf("%d + %d = %d\n", sum, number, sum + number);
        printf("请输入下一个正整数：");
        scanf("%d", &number);
    } while (number > 0);

    printf("总和为：%d\n", sum);

    return 0;
}