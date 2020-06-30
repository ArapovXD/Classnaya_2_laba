#include <iostream>
#include <vector>
#include <cstring>
using namespace std;


/**
@class teacher
Класс учителя, доступ к приватным полям осуществляется через геттеры, сеттеры
*/
class teacher{
private:
    int subjects[100];
    int len_subjects = 0;
    int* groups;
    int len_groups;
    char login[50];
    char password[50];
public:

    void set_subject(int* subj);

    void set_groups(int* grp, int size_groups);

    void set_login(char* val);

    void set_password(char* val);

    void get_subjects(int* to_copy);

    void get_groups(int* to_copy);

    int get_len_groups();

    void get_login(char* to_copy);

    void get_password(char* to_copy);
};
