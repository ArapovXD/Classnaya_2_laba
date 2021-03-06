#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include "teacher.h"
using namespace std;

void teacher::set_subject(int* subj){
    int i = 0;
    for (i; i < 100; i++) subjects[i] = -1;
    i = 0;
    while (subj[i] != -1){
        subjects[i] = subj[i];
        i++;
    }
}


void teacher::set_groups(int* grp, int size_groups){

    len_groups = size_groups;
    groups = new int[len_groups];

    int i = 0;

    for (i; i < len_groups; i++){
        groups[i] = grp[i];
    }
}

void teacher::set_login(char* val){
    strcpy(login, val);
}

void teacher::set_password(char* val){
    strcpy(password, val);
}

void teacher::get_subjects(int* to_copy){
    int i = 0;

    while (subjects[i] != -1){
        to_copy[i] = subjects[i];
        i++;
    }
}

void teacher::get_groups(int* to_copy){
    int i = 0;

    for (i; i < len_groups; i++){
        to_copy[i] = groups[i];
    }
}

int teacher::get_len_groups(){
    return len_groups;
}

void teacher::get_login(char* to_copy){
    strcpy(to_copy, login);
}

void teacher::get_password(char* to_copy){
    strcpy(to_copy, password);
}


