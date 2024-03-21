#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> // 引入SDL_image库
#include <stdbool.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define PLANE_SPEED 5
#define BULLET_SPEED 10
#define BULLET_COOLDOWN 10 // 子弹间隔

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool isRunning = false;

int planeX = SCREEN_WIDTH / 2;
int planeY = SCREEN_HEIGHT - 100;

bool upKey = false;
bool downKey = false;
bool leftKey = false;
bool rightKey = false;
bool spaceKey = false;

typedef struct {
    int x;
    int y;
    bool active;
} Bullet;

typedef struct {
    int x;
    int y;
    bool active;
} Enemy;

Bullet bullets[50];
Enemy enemies[10]; // 最多10个敌机
int bulletCooldown = 0; // 子弹间隔计数器

SDL_Texture* planeTexture = NULL; // 飞机图片纹理
SDL_Texture* enemyTexture = NULL; // 敌机图片纹理

void initSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("飞机大战", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // 初始化SDL_image
    IMG_Init(IMG_INIT_PNG);

    isRunning = true;
}

void loadMedia() {
    // 加载飞机图片
    SDL_Surface* loadedSurface = IMG_Load("plane.png");
    if (loadedSurface == NULL) {
        printf("无法加载飞机图片! SDL_image Error: %s\n", IMG_GetError());
    } else {
        // 创建纹理
        planeTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (planeTexture == NULL) {
            printf("无法创建飞机纹理! SDL Error: %s\n", SDL_GetError());
        }

        // 设置纹理的混合模式为透明度混合
        SDL_SetTextureBlendMode(planeTexture, SDL_BLENDMODE_BLEND);

        SDL_FreeSurface(loadedSurface);
    }

    // 加载敌机图片
    loadedSurface = IMG_Load("enemy.png");
    if (loadedSurface == NULL) {
        printf("无法加载敌机图片! SDL_image Error: %s\n", IMG_GetError());
    } else {
        // 创建纹理
        enemyTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (enemyTexture == NULL) {
            printf("无法创建敌机纹理! SDL Error: %s\n", SDL_GetError());
        }

        // 设置纹理的混合模式为透明度混合
        SDL_SetTextureBlendMode(enemyTexture, SDL_BLENDMODE_BLEND);

        SDL_FreeSurface(loadedSurface);
    }
}


void closeSDL() {
    // 释放纹理和关闭SDL_image
    SDL_DestroyTexture(planeTexture);
    SDL_DestroyTexture(enemyTexture);
    IMG_Quit();

    // 关闭SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void handleEvents() {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        upKey = true;
                        break;
                    case SDLK_DOWN:
                        downKey = true;
                        break;
                    case SDLK_LEFT:
                        leftKey = true;
                        break;
                    case SDLK_RIGHT:
                        rightKey = true;
                        break;
                    case SDLK_SPACE:
                        spaceKey = true;
                        break;
                }
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym) {
                    case SDLK_UP:
                        upKey = false;
                        break;
                    case SDLK_DOWN:
                        downKey = false;
                        break;
                    case SDLK_LEFT:
                        leftKey = false;
                        break;
                    case SDLK_RIGHT:
                        rightKey = false;
                        break;
                    case SDLK_SPACE:
                        spaceKey = false;
                        break;
                }
                break;
        }
    }
}

void movePlane() {
    if(upKey && planeY > 0)
        planeY -= PLANE_SPEED;
    if(downKey && planeY < SCREEN_HEIGHT - 100)
        planeY += PLANE_SPEED;
    if(leftKey && planeX > 0)
        planeX -= PLANE_SPEED;
    if(rightKey && planeX < SCREEN_WIDTH - 100)
        planeX += PLANE_SPEED;
}

void moveBullets() {
    for(int i = 0; i < 50; ++i) {
        if(bullets[i].active) {
            bullets[i].y -= BULLET_SPEED;
            if(bullets[i].y < 0)
                bullets[i].active = false;
        }
    }
}

void moveEnemies() {
    for(int i = 0; i < 10; ++i) {
        if(enemies[i].active) {
            enemies[i].y += 1; // 敌机向下移动
            if(enemies[i].y > SCREEN_HEIGHT) // 敌机移出屏幕，重置为未激活状态
                enemies[i].active = false;
        }
        else {
            // 如果当前位置没有敌机，尝试生成一个敌机
            if(rand() % 1000 == 0) {
                enemies[i].active = true;
                enemies[i].x = rand() % (SCREEN_WIDTH - 100); // 随机生成x坐标
                enemies[i].y = -50; // 敌机出现在屏幕顶部
            }
        }
    }
}

void checkCollision() {
    for(int i = 0; i < 50; ++i) {
        if(bullets[i].active) {
            for(int j = 0; j < 10; ++j) {
                if(enemies[j].active) {
                    // 检查子弹与敌机的碰撞
                    if(bullets[i].x < enemies[j].x + 100 && bullets[i].x + 5 > enemies[j].x &&
                       bullets[i].y < enemies[j].y + 50 && bullets[i].y + 10 > enemies[j].y) {
                        bullets[i].active = false; // 子弹消失
                        enemies[j].active = false; // 敌机消失
                    }
                }
            }
        }
    }
}

void shootBullet() {
    if (bulletCooldown > 0) {
        bulletCooldown--;
        return;
    }

    for(int i = 0; i < 50; ++i) {
        if(!bullets[i].active) {
            bullets[i].active = true;
            bullets[i].x = planeX + 45; // 调整子弹位置
            bullets[i].y = planeY;
            bulletCooldown = BULLET_COOLDOWN;
            break;
        }
    }
}

void render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // 绘制飞机
    SDL_Rect planeRect = {planeX, planeY, 100, 100}; // 设置飞机矩形大小为100x100
    SDL_RenderCopy(renderer, planeTexture, NULL, &planeRect);

    // 绘制敌机
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // 设置敌机颜色为红色
    for(int i = 0; i < 10; ++i) {
        if(enemies[i].active) {
            SDL_Rect enemyRect = {enemies[i].x, enemies[i].y, 100, 100}; // 设置敌机矩形大小为100x100
            SDL_RenderCopyEx(renderer, enemyTexture, NULL, &enemyRect, 0, NULL, SDL_FLIP_VERTICAL); // 翻转敌机图片
        }
    }

    // 绘制子弹
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    for(int i = 0; i < 50; ++i) {
        if(bullets[i].active) {
            SDL_Rect bulletRect = {bullets[i].x, bullets[i].y, 5, 10}; // 设置子弹矩形大小为5x10
            SDL_RenderFillRect(renderer, &bulletRect);
        }
    }

    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    initSDL();
    loadMedia(); // 加载图片

    while(isRunning) {
        handleEvents();
        movePlane();
        moveBullets();
        moveEnemies();
        checkCollision(); // 检查子弹与敌机的碰撞
        if(spaceKey)
            shootBullet();
        render();
        SDL_Delay(10);
    }

    closeSDL(); // 释放资源
    return 0;
}

