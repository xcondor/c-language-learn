#include <ncurses.h>

int main() {
    initscr();            // 初始化 ncurses 窗口
    printw("Hello, ncurses!");  // 在窗口中打印文本
    refresh();            // 刷新窗口以显示更改
    getch();              // 等待用户输入
    endwin();             // 关闭 ncurses 窗口

    return 0;
}
