#include <iostream>
#include <vector>
#pragma once

using namespace std;



class subject_index{
private:
    int subject_ind[100];
    char subject_name[50][50];
    int index_next = 0;

public:

    int get_len(){return index_next;}

    void get_subject(char* to_copy, int index);

    int is_subject_exist(char* subj);

    void set_new_index();

    void set_new_subject_name(char* new_name);
};
