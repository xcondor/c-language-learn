#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arr = (int *)malloc(10 * sizeof(int));

    if (arr == NULL) {
        printf("内存分配失败\n");
        return 1;
    }

    for (int i = 0; i < 10; i++) {
        arr[i] = i + 1;
    }

    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }

    free(arr);

    return 0;
}