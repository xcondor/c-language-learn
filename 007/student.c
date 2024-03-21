#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int age;
    float grade;
};

int main() {
    struct Student s1;

    strcpy(s1.name, "Alice");
    s1.age = 20;
    s1.grade = 90.5;

    printf("姓名：%s\n", s1.name);
    printf("年龄：%d\n", s1.age);
    printf("成绩：%f\n", s1.grade);

    return 0;
}