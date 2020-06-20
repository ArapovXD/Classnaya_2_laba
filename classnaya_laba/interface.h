#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include "subject_class.h"
#include "teacher.h"
#include "student.h"

using namespace std;



class interface{
private:
    int call;
    char student_filename[50];
    char teacher_filename[50];
    char subject_filename[50];
public:
    interface(int val, char* sf_name , char* tf_name, char*  sbjf_name);

    void show_interface();

    void authorization(int call);

    int ask_to_subj(int* arr, subject_index ex);

    void show_grades_or_attendance(student a, int attendance);

    void show_final_rate(student a);

    void show_student_interface(char* my_login);

///Проверяет на наличие существования группы, если сущ то заполняет массив предметами группы, возвращает 1, иначе - 0
    int is_group_exist(int group, int* subjects);

    void add_to_group(teacher a);

    void show_curr_groups(teacher a);

    void dump_data(int len, vector <teacher> &arr);

    void dump_data(int len, vector <student> &arr);

    void add_group(teacher a, int index);

    void delete_group(teacher a, int index);

    void to_moove_student(teacher a);

    void give_grades_or_attendance(teacher a, int attendance);

    void to_final_rate(teacher a);

    void add_subject(teacher a);

    void delete_subject(teacher a);

    void show_teacher_interface(char* my_login);

    void show_registration_interface();

    void cin_login(char* login);

    void cin_password(char* password);

    void create_password(char* password);

    int get_people(vector <teacher> &arr);

    int get_people(vector <student> &arr);

    int is_login_exist(char* login);

    void append_data(teacher &a);

    void append_data(student &a);
};














