#include <stdio.h>

int main() {
    int numbers[5] = {10, 20, 30, 40, 50};

    // 遍历数组并打印每个元素
    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }

    printf("\n");

    return 0;
}