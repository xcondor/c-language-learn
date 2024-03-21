#include <stdio.h>

// 定义计算器函数
int calculator(int num1, int num2, char operator) {
    int result = 0;

    switch (operator) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2!= 0) {
                result = num1 / num2;
            } else {
                printf("错误：除数不能为 0。\n");
                return -1;
            }
            break;
        default:
            printf("错误：无效的运算符。\n");
            return -1;
    }

    return result;
}

// 主函数
int main() {
    int num1, num2;
    char operator;

    printf("请输入第一个数字：");
    scanf("%d", &num1);

    printf("请输入运算符（+、-、*、/）：");
    scanf(" %c", &operator);

    printf("请输入第二个数字：");
    scanf("%d", &num2);

    int result = calculator(num1, num2, operator);
    if (result!= -1) {
        printf("计算结果：%d\n", result);
    }

    return 0;
}