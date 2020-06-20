#include <iostream>
#include <vector>
#include <cstring>
using namespace std;



class teacher{
private:
    int subjects[100];
    int len_subjects = 0;
    int groups[100]{};
    char login[50];
    char password[50];
public:

    void set_subject(int* subj);

    void set_groups(int* grp);

    void set_login(char* val);

    void set_password(char* val);

    void get_subjects(int* to_copy);

    void get_groups(int* to_copy);

    void get_login(char* to_copy);

    void get_password(char* to_copy);
};
