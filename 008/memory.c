#include <stdio.h>
#include <stdlib.h>

// 动态分配内存并创建整数数组
int* createArray(int size) {
    int* arr = (int*)malloc(size * sizeof(int));

    if (arr == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }

    printf("内存分配成功，地址：%p\n", arr);

    return arr;
}

// 释放内存
void destroyArray(int* arr) {
    if (arr!= NULL) {
        printf("内存释放，地址：%p\n", arr);
        free(arr);
    }
}

int main() {
    int* arr = createArray(10);

    if (arr == NULL) {
        return 1;
    }

    // 使用数组

    destroyArray(arr);

    return 0;
}