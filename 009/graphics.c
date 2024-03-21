#include <graphics.h>

int main() {
    // 初始化图形模式
    initgraph(640, 480);

    // 绘制一个红色的矩形
    rectangle(100, 100, 200, 200);

    // 绘制一个蓝色的圆形
    circle(300, 300, 50);

    // 绘制一个绿色的线条
    line(100, 300, 500, 300);

    // 显示图形
    getch();

    // 关闭图形模式
    closegraph();

    return 0;
}