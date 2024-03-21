#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// 全局变量，用于存储共享内存中的数据
int sharedData = 0;

// 线程函数，用于修改共享内存中的数据
void* threadFunction(void* threadId) {
    int threadIdValue = (intptr_t)threadId;

    // 修改共享内存中的数据
    sharedData += threadIdValue;

    printf("线程 %d 完成，共享数据的值为：%d\n", threadIdValue, sharedData);

    return NULL;
}

int main() {
    // 创建两个线程
    pthread_t threads[2];

    // 创建线程
    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, threadFunction, (void*)((size_t)i));
    }

    // 等待线程完成
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("主线程完成，共享数据的值为：%d\n", sharedData);

    return 0;
}