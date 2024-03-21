#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define CELL_SIZE 20
#define INITIAL_SPEED 200 // 初始速度，值越大速度越慢
#define NUM_OBSTACLES 5  // 障碍物数量

// 颜色结构体
typedef struct {
    Uint8 r, g, b;
} Color;

// 定义蛇的结构体
typedef struct {
    int x, y;
} SnakeSegment;

// 定义游戏状态
typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SnakeSegment snake[100];
    int snakeLength;
    int dirX, dirY;
    int foodX, foodY;
    bool running;
    Color snakeColor;
    Color foodColor;
    Color obstacleColor;
    int obstacles[NUM_OBSTACLES][2];
} GameState;

// 随机生成颜色
Color randomColor() {
    Color color;
    color.r = rand() % 256;
    color.g = rand() % 256;
    color.b = rand() % 256;
    return color;
}

// 初始化游戏状态
void initGame(GameState* gameState) {
    gameState->snake[0].x = WINDOW_WIDTH / 2;
    gameState->snake[0].y = WINDOW_HEIGHT / 2;
    gameState->snakeLength = 1;
    gameState->dirX = 0;
    gameState->dirY = 0;
    gameState->foodX = rand() % (WINDOW_WIDTH / CELL_SIZE) * CELL_SIZE;
    gameState->foodY = rand() % (WINDOW_HEIGHT / CELL_SIZE) * CELL_SIZE;
    gameState->running = true;
    gameState->snakeColor = randomColor();
    gameState->foodColor = randomColor();
    gameState->obstacleColor = randomColor();

    // 生成障碍物
    for (int i = 0; i < NUM_OBSTACLES; i++) {
        gameState->obstacles[i][0] = rand() % (WINDOW_WIDTH / CELL_SIZE) * CELL_SIZE;
        gameState->obstacles[i][1] = rand() % (WINDOW_HEIGHT / CELL_SIZE) * CELL_SIZE;
    }
}

// 处理用户输入
void handleInput(GameState* gameState) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            gameState->running = false;
        }
        else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    gameState->dirX = 0;
                    gameState->dirY = -1;
                    break;
                case SDLK_DOWN:
                    gameState->dirX = 0;
                    gameState->dirY = 1;
                    break;
                case SDLK_LEFT:
                    gameState->dirX = -1;
                    gameState->dirY = 0;
                    break;
                case SDLK_RIGHT:
                    gameState->dirX = 1;
                    gameState->dirY = 0;
                    break;
            }
        }
    }
}

// 更新游戏逻辑
void updateGame(GameState* gameState) {
    // 移动蛇
    for (int i = gameState->snakeLength - 1; i > 0; i--) {
        gameState->snake[i] = gameState->snake[i - 1];
    }
    gameState->snake[0].x += gameState->dirX * CELL_SIZE;
    gameState->snake[0].y += gameState->dirY * CELL_SIZE;

    // 检查是否触碰到边界
    if (gameState->snake[0].x < 0 || gameState->snake[0].x >= WINDOW_WIDTH || 
        gameState->snake[0].y < 0 || gameState->snake[0].y >= WINDOW_HEIGHT) {
        gameState->running = false;
    }

    // 检查是否吃到食物
    if (gameState->snake[0].x == gameState->foodX && gameState->snake[0].y == gameState->foodY) {
        gameState->snakeLength++;
        gameState->foodX = rand() % (WINDOW_WIDTH / CELL_SIZE) * CELL_SIZE;
        gameState->foodY = rand() % (WINDOW_HEIGHT / CELL_SIZE) * CELL_SIZE;
        gameState->foodColor = randomColor();
    }

    // 检查是否碰到障碍物
    for (int i = 0; i < NUM_OBSTACLES; i++) {
        if (gameState->snake[0].x == gameState->obstacles[i][0] && gameState->snake[0].y == gameState->obstacles[i][1]) {
            gameState->running = false;
            break;
        }
    }
}

// 渲染游戏
void renderGame(GameState* gameState) {
    // 清空屏幕
    SDL_SetRenderDrawColor(gameState->renderer, 0, 0, 0, 255);
    SDL_RenderClear(gameState->renderer);

    // 绘制蛇
    SDL_SetRenderDrawColor(gameState->renderer, gameState->snakeColor.r, gameState->snakeColor.g, gameState->snakeColor.b, 255);
    for (int i = 0; i < gameState->snakeLength; i++) {
        SDL_Rect rect = {gameState->snake[i].x, gameState->snake[i].y, CELL_SIZE, CELL_SIZE};
        SDL_RenderFillRect(gameState->renderer, &rect);
    }

    // 绘制食物
    SDL_SetRenderDrawColor(gameState->renderer, gameState->foodColor.r, gameState->foodColor.g, gameState->foodColor.b, 255);
    SDL_Rect foodRect = {gameState->foodX, gameState->foodY, CELL_SIZE, CELL_SIZE};
    SDL_RenderFillRect(gameState->renderer, &foodRect);

    // 绘制障碍物
    SDL_SetRenderDrawColor(gameState->renderer, gameState->obstacleColor.r, gameState->obstacleColor.g, gameState->obstacleColor.b, 255);
    for (int i = 0; i < NUM_OBSTACLES; i++) {
        SDL_Rect obstacleRect = {gameState->obstacles[i][0], gameState->obstacles[i][1], CELL_SIZE, CELL_SIZE};
        SDL_RenderFillRect(gameState->renderer, &obstacleRect);
    }

        // 更新屏幕
    SDL_RenderPresent(gameState->renderer);
}

int main() {
    GameState gameState;

    // 初始化SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL 初始化失败: %s\n", SDL_GetError());
        return -1;
    }

    // 创建窗口
    gameState.window = SDL_CreateWindow("贪食蛇", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (gameState.window == NULL) {
        printf("窗口创建失败: %s\n", SDL_GetError());
        return -1;
    }

    // 创建渲染器
    gameState.renderer = SDL_CreateRenderer(gameState.window, -1, SDL_RENDERER_ACCELERATED);
    if (gameState.renderer == NULL) {
        printf("渲染器创建失败: %s\n", SDL_GetError());
        return -1;
    }

    // 初始化游戏状态
    initGame(&gameState);

    // 游戏循环
    while (gameState.running) {
        handleInput(&gameState);
        updateGame(&gameState);
        renderGame(&gameState);
        SDL_Delay(INITIAL_SPEED); // 控制游戏速度
    }

    // 游戏结束，显示消息
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "游戏结束", "游戏结束！", gameState.window);

    // 清理资源
    SDL_DestroyRenderer(gameState.renderer);
    SDL_DestroyWindow(gameState.window);
    SDL_Quit();

    return 0;
}
