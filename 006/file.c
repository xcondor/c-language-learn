#include <stdio.h>

int main() {
    FILE *file = fopen("example.txt", "r");

    if (file == NULL) {
        printf("文件打开失败\n");
        return 1;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);

    return 0;
}