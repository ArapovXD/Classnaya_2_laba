#include <vector>
#include <iostream>
#include <cstring>
#include "subject_class.h"

using namespace std;


int subject_index::get_len(){return index_next;}

void subject_index::get_subject(char* to_copy, int index){

    strcpy(to_copy, subject_name[index]);
}

int subject_index::is_subject_exist(char* subj){

    int i = 0, len = index_next;

    for (i; i < len; i++){
        if (!strcmp(subject_name[i], subj)) return i;
    }

    return -1;

}

void subject_index::set_new_index(){

    subject_ind[index_next] = 1;
}

void subject_index::set_new_subject_name(char* new_name){

    strcpy(subject_name[index_next], new_name);
    index_next++;
}













