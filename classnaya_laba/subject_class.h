#include <iostream>
#include <vector>
#pragma once

using namespace std;


/**
@class subject_index
Класс в котором хранятся индексы и названия всех предметов которые были у учителей или учеников, а так же кол-во предметов,
который так же является индексом для следующего нового предмета
*/
class subject_index{
private:
    int subject_ind[100];
    char subject_name[100][50];
    int index_next = 0;

public:
/**
    @function get_len
    возвращает кол-во предметов в массиве
    @return index_next - длина массива
*/
    int get_len();




/**
    @function get_subject
    По индексу предмета копирует в to_copy название предмета
    @param to_copy - куда копировать название
    @param index - индекс педмета
*/
    void get_subject(char* to_copy, int index);




/**
    @function is_subject_exist
    По названию предмета проверяет, существует ли предмет в массиве, если да - возвращает индекс предмета, иначе -1
    @param subj - название предмета, наличие которого надо проверить
*/
    int is_subject_exist(char* subj);




/**
    @function set_new_index
    Вообще массив subject_ind нигде не нужен, но так получилось что он есть.
    Ставит единицу в индексе нового предмета в массиве subject_ind
*/
    void set_new_index();




/**
    @function set_new_subject_name
    Добавляет в массив с названиями предметов новое назание предмета, ставит index_next + 1, который так же является длиной массива
*/
    void set_new_subject_name(char* new_name);
};
