#include <stdio.h>

int main() {
    int number, result;

    printf("请输入一个数字：");
    scanf("%d", &number);

    // 使用 if-else 语句来判断数字是否为偶数
    if (number % 2 == 0) {
        printf("%d 是偶数\n", number);
    } else {
        printf("%d 是奇数\n", number);
    }

    // 使用 for 循环来计算 1 到 10 的和
    result = 0;
    for (int i = 1; i <= 10; i++) {
        result += i;
    }
    printf("1 到 10 的和为：%d\n", result);

    // 使用 while 循环来打印数字 1 到 5
    int i = 1;
    while (i <= 5) {
        printf("%d ", i);
        i++;
    }
    printf("\n");

    return 0;
}