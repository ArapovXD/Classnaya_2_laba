#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include "student.h"
using namespace std;

void student::set_login(char* val){
    strcpy(login, val);
}

void student::set_password(char* val){
    strcpy(password, val);
}

void student::set_subject(int* subj){
    int i = 0;
    for (i; i < 100; i++) subjects[i] = -1;
    i = 0;
    while (subj[i] != -1){
        subjects[i] = subj[i];
        i++;
    }
}

void student::get_subjects(int* to_copy){
    int i = 0;

    while (subjects[i] != -1){
        to_copy[i] = subjects[i];
        i++;
    }
}

void student::set_group(int val){group = val;}

int student::get_group(){return group;}

void student::get_login(char* to_copy){
    strcpy(to_copy, login);
}

void student::get_password(char* to_copy){
    strcpy(to_copy, password);
}

void student::set_grade(int subj, int month, int day, int val){
    grades[subj][month][day] = val;
}

void student::set_attendance(int subj, int month, int day, int val){
    attendance[subj][month][day] = val;
}

int student::get_grade(int subj, int month, int day){
    return grades[subj][month][day];
}

int student::get_attendance(int subj, int month, int day){
    return attendance[subj][month][day];
}
