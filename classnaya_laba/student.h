#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

/**
@class student
Класс студента, доступ к приватным полям осуществляется через геттеры, сеттеры.
Из особенностей, 2 трехмерных массива с оценками и данными о посещаемости. В оценках 1 элемент - идентификатор предмета,
Второй элемент - месяц, третий - день месяца, причем в каждом месяце есть дополнительная ячейка, в которой
хранится итоговая оценка за курс, который кончился в соответствующем месяце. Таким образом Хранятся оценки студента за все предметы.
В данных о посещаемости то же самое, токо 1 - был, -1 не был.
*/
class student{
private:
    char login[50];
    char password[50];

    int subjects[100];
    ///Номер группы студента.
    int group;
    ///Хранилище оценок.
    double grades[100][13][33]{};
    ///Хранилище информации о посещаемости
    int attendance [100][13][32]{};

public:
    void set_login(char* val);

    void set_password(char* val);

    void set_subject(int* subj);

    void set_group(int val);

    void set_grade(int subj, int month, int day, int val);

    void set_attendance(int subj, int month, int day, int val);

    void get_subjects(int* to_copy);

    int get_group();

    void get_login(char* to_copy);

    void get_password(char* to_copy);

    int get_grade(int subj, int month, int day);

    int get_attendance(int subj, int month, int day);
};
