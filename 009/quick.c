#include <stdio.h>
#include <stdlib.h>

// 交换函数
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 分治函数
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

// 以数组中的随机元素作为枢轴
int randomizedPartition(int arr[], int low, int high) {
    int randomIdx = low + rand() % (high - low + 1);
    swap(&arr[randomIdx], &arr[high]);
    return partition(arr, low, high);
}

// 快速排序函数
void quickSort(int arr[], int low, int high) {
    while (low < high) {
        int pi = randomizedPartition(arr, low, high);
        if (pi - low < high - pi)
            quickSort(arr, low, pi - 1);
        else
            quickSort(arr, pi + 1, high);
    }
}

// 打印数组函数
void printArray(int arr[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// 测试示例
int main() {
    int arr[] = {10, 80, 30, 90, 40, 50, 70};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("排序前的数组为：\n");
    printArray(arr, arr_size);
    quickSort(arr, 0, arr_size - 1);
    printf("排序后的数组为：\n");
    printArray(arr, arr_size);

    return 0;
}