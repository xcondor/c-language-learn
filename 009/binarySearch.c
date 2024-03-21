#include <stdio.h>

// 二分查找函数
int binarySearch(int arr[], int low, int high, int x) {
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == x)
            return mid;
        else if (arr[mid] < x)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
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
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15};
    int arr_size = sizeof(arr) / sizeof(arr[0]);
    int x = 5;

    int result = binarySearch(arr, 0, arr_size - 1, x);

    if (result!= -1)
        printf("元素 %d 在数组中的索引为 %d。\n", x, result);
    else
        printf("元素 %d 不在数组中。\n", x);

    printArray(arr, arr_size);

    return 0;
}