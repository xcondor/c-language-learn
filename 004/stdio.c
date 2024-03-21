#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 生成随机数的函数
int generateRandomNumber() {
    srand(time(NULL));
    return rand() % 100 + 1;
}

// 检查猜测是否正确的函数
int checkGuess(int guess, int randomNumber) {
    if (guess == randomNumber) {
        return 1;
    } else if (guess > randomNumber) {
        return -1;
    } else {
        return 2;
    }
}

// 游戏循环
void playGame() {
    int randomNumber = generateRandomNumber();
    int guess;
    int attempts = 0;
    int result;

    do {
        printf("请输入你的猜测（1 到 100 之间的整数）：");
        scanf("%d", &guess);

        attempts++;

        result = checkGuess(guess, randomNumber);
        if (result == 1) {
            printf("恭喜你，猜对了！你一共尝试了%d 次。\n", attempts);
        } else if (result == -1) {
            printf("抱歉，你的猜测太大了，请再试一次。\n");
        } else {
            printf("抱歉，你的猜测太小了，请再试一次。\n");
        }
    } while (result!= 1);
}

int main() {
    playGame();

    return 0;
}