#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

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
