#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// 全局变量，用于共享数据
intptr_t counter = 0;

// 线程函数，用于增加计数器的值
void* threadFunction(void* threadId) {
    // 将 void* 转换为 intptr_t
    intptr_t id = (intptr_t)threadId;
    // 增加计数器的值
    counter++;
    printf("线程 %ld 结束，计数器的值为：%ld\n", id, counter);
    pthread_exit(NULL);
}

int main() {
    // 创建两个线程
    pthread_t threads[2];

    // 创建线程
    for (int i = 0; i < 2; i++) {
        // 将 int 转换为 intptr_t
        intptr_t threadId = (intptr_t)i;
        pthread_create(&threads[i], NULL, threadFunction, (void*)threadId);
    }

    // 等待线程结束
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("主线程结束，计数器的值为：%ld\n", counter);

    return 0;
}