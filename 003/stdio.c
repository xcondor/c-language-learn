#include <stdio.h>

int main() {
    int a = 10, b = 20, c = 30, d = 40, e = 50;

    // 赋值运算符：将值赋给变量
    a = 100;
    b = 200;
    c = 300;
    d = 400;
    e = 500;

    // 算术运算符：进行数学运算
    int sum = a + b + c + d + e;
    printf("算术运算符：a + b + c + d + e = %d\n", sum);

    // 关系运算符：比较大小
    if (a > b) {
        printf("关系运算符：a > b\n");
    } else if (a < b) {
        printf("关系运算符：a < b\n");
    } else {
        printf("关系运算符：a == b\n");
    }

    // 逻辑运算符：组合条件
    if ((a > b) && (c > d)) {
        printf("逻辑运算符：(a > b) && (c > d)\n");
    } else if ((a > b) || (c > d)) {
        printf("逻辑运算符：(a > b) || (c > d)\n");
    } else {
        printf("逻辑运算符：!(a > b) &&!(c > d)\n");
    }

    // 位运算符：进行位级别的操作
    a = a & b;
    printf("位运算符：a & b = %d\n", a);

    a = a | b;
    printf("位运算符：a | b = %d\n", a);

    a = a ^ b;
    printf("位运算符：a ^ b = %d\n", a);

    a = ~a;
    printf("位运算符：~a = %d\n", a);

    a <<= 2;
    printf("位运算符：a <<= 2 = %d\n", a);

    a >>= 2;
    printf("位运算符：a >>= 2 = %d\n", a);

    return 0;
}