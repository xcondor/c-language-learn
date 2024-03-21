#include <stdio.h>

// 学生结构体定义
typedef struct {
    char name[50];
    int age;
    float grade;
} Student;

// 记录学生成绩函数
void recordStudentGrades(Student *students, int *nStudents) {
    int i, subject;

    printf("请输入学生人数：");
    scanf("%d", nStudents);

    for (i = 0; i < *nStudents; i++) {
        printf("请输入学生 %d 的姓名：", i + 1);
        scanf("%s", students[i].name);

        printf("请输入学生 %d 的年龄：", i + 1);
        scanf("%d", &students[i].age);

        printf("请输入学生 %d 的成绩：", i + 1);
        scanf("%f", &students[i].grade);

        printf("请输入学生 %d 的科目数：", i + 1);
        scanf("%d", &subject);

        for (int j = 0; j < subject; j++) {
            printf("请输入学生 %d 的科目 %d 的成绩：", i + 1, j + 1);
            scanf("%f", &students[i].grade);
        }
    }
}

// 查询学生成绩函数
void queryStudentGrades(Student *students, int nStudents) {
    int i, subject;

    printf("请输入要查询的学生编号：");
    scanf("%d", &i);

    if (i < 1 || i > nStudents) {
        printf("不存在该学生！\n");
        return;
    }

    printf("学生 %d 的信息如下：\n", i);
    printf("姓名：%s\n", students[i].name);
    printf("年龄：%d\n", students[i].age);
    printf("成绩：%f\n", students[i].grade);

    printf("请输入要查询的科目编号：");
    scanf("%d", &subject);

    if (subject < 1 || subject > 5) {
        printf("不存在该科目！\n");
        return;
    }

    printf("学生 %d 的科目 %d 的成绩是：%f\n", i, subject, students[i].grade);
}

int main() {
    Student students[50];
    int nStudents;

    recordStudentGrades(students, &nStudents);
    queryStudentGrades(students, nStudents);

    return 0;
}