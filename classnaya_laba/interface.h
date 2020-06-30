#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include "subject_class.h"
#include "teacher.h"
#include "student.h"

using namespace std;


/**
@class interface
Класс интерфейс
*/
class interface{
private:
    int call;
    char student_filename[50];
    char teacher_filename[50];
    char subject_filename[50];
    char groups_filename[50];
public:

    interface(int val, char* sf_name , char* tf_name, char*  sbjf_name, char* grpf_name);
/**
    @function lockdown
    Выход из программы
*/
    void lockdown();




/**
    @function show_interface
    В зависимости от команды передает управление соответствующей функции, если 1 или 2, то авторизация, 3 - регистрация учителя
*/
    void show_interface();




/**
    @function show_registration_interface
    Реализует регистрацию учителя.

*/
void show_registration_interface();


/**
    @function authorization
    Функция авторизации учителя или студента, после успешной авторизации управление
    передается show_student_interface или show_teacher_interface с аргументом логина пользователя
    @param call - команда
*/
    void authorization(int call);




/**
    @function show_student_interface

    Запрашивает и выполняет функции студента
    @param a - экземпляр класса student, авторизовавшегося пользователя
*/
    void show_student_interface(student a);




/**
    @function show_teacher_interface
    Запрашивает и выполняет функции учителя, перед этим обновив экземпляр класса учителя, путем загрузки всех экземпляров в массив и поиска в нем нужного по логину.
    @param my_login - логин авторизовавшегося учителя
*/
    void show_teacher_interface(char* my_login);




/**
    @function show_grades_or_attendance
    Функция студента, которая реализует возможность просмотра оценок или посещаемости по какому то предмету ученика,
    предварительно обозначив диапазон, за который выводить оценки или посещаемость, за весь год, за какой то месяц, за конкретный день.
    @param a - экземпляр класса student, авторизовавшегося пользователя
    @param attendance 1 - просмотр посещаемости, 0 - оценок.
*/
    void show_grades_or_attendance(student a, int attendance);




/**
    @function show_final_rate
    Функция студента, которая реализует возможность просмотра итоговой оценки по какому то предмету ученика за курс,
    который кончился в определенном месяце.
    @param a - экземпляр класса student, авторизовавшегося пользователя
*/
    void show_final_rate(student a);




/**
    @function add_to_group
    Функция учителя, которая реализует возможность добавления студента в какую то группу учителя.
    Если студент с введенной группой существует, то ему запишутся предметы данной группы, т.к. в группе у всех одинаковые предметы
    иначе - это первый студент в группе и предметы надо ввести самому
    @param a - экземпляр класса teacher, авторизовавшегося пользователя
*/
    void add_to_group(teacher a);




/**
    @function show_curr_groups
    Функция учителя, которая реализует возможность просмотра номеров текущих групп данного учителя.
    @param a - экземпляр класса teacher, авторизовавшегося пользователя
*/
    void show_curr_groups(teacher a);




/**
    @function add_group
    Функция учителя, которая реализует возможность добавление группы данному учителю.
    @param teachers - массив со всеми экземплярами класса teacher
    @param index - индекс нашего учителя в массиве teachers
    @param len - длина массива teachers
*/
    void add_group(vector <teacher> teachers, int index, int len);




/**
    @function delete_group
    Функция учителя, которая реализует возможность удаление группы данного учителя путем
    @param teachers - массив со всеми экземплярами класса teacher
    @param index - индекс нашего учителя в массиве teachers
    @param len - длина массива teachers
*/
    void delete_group(vector <teacher> teachers, int index, int len);




/**
    @function to_moove_student
    Функция учителя, которая реализует возможность перемещения студента принадлежащего одной из его групп в другую группу,
    при изменении группы меняются предметы студента на те, которые в новой группе, если в новой группе никого нет, то предметы
    остаются те же.
    @param a - экземпляр класса teacher, авторизовавшегося пользователя
*/
    void to_moove_student(teacher a);




/**
    @function give_grades_or_attendance
    Функция учителя, которая реализует возможность выставления оценки или посещаемости одной из групп учителя за определенную дату
    @param a - экземпляр класса teacher, авторизовавшегося пользователя
    @param attendance 1 - выставление посещаемости, 0 - оценок.
*/
    void give_grades_or_attendance(teacher a, int attendance);




/**
    @function to_final_rate
    Функция учителя, которая реализует возможность выставления итоговой оценки за курс какому то студенту, как средней арифметической,
    предварительно введя дату начала и конца курса.
    @param a - экземпляр класса teacher, авторизовавшегося пользователя
*/
    void to_final_rate(teacher a);




/**
    @function add_subject
    Функция учителя, которая реализует возможность добавления предмета данного учителя.
    @param teachers - массив со всеми экземплярами класса teacher
    @param index - индекс нашего учителя в массиве teachers
    @param len - длина массива teachers
*/
    void add_subject(vector <teacher> teachers, int index, int len);




/**
    @function delete_subject
    Функция учителя, которая реализует возможность удаления предмета данного учителя.
    @param teachers - массив со всеми экземплярами класса teacher
    @param index - индекс нашего учителя в массиве teachers
    @param len - длина массива teachers
*/
    void delete_subject(vector <teacher> teachers, int index, int len);




/**
    @function get_people
    Реализует загрузку всех экземпляров класса teacher, массив групп для каждого экземпляра загружается из файла с группами,
    у экземпляра teacher хранится длина массива групп и из файла берутся соответствующее кол-во групп и засовывается в экземпляр.
    @param arr куда будет загружаться массив со всеми экземплярами класса teacher.
*/
    int get_people(vector <teacher> &arr);




/**
    @function get_people
    Реализует загрузку всех экземпляров класса student.
    @param arr куда будет загружаться массив со всеми экземплярами класса student.
*/
    int get_people(vector <student> &arr);




/**
    @function append_data
    Добавляет экземпляр класса teacher в конец файла с учителями, группы загружает в конец отдельного файла с группами
    @param a - экземпляр класса teacher, авторизовавшегося пользователя
*/
    void append_data(teacher &a);





/**
    @function append_data
    Добавляет экземпляр класса student в конец файла с студентами
    @param a - экземпляр класса student, авторизовавшегося пользователя
*/
    void append_data(student &a);




/**
    @function dump_data
    Сохраняет массив с экземплярами класса teacher в файл с учителями,
    группы сохраняет в файл с группами.
    @param arr - массив с учителями, который надо сохранить
    @param len - длина массива arr
*/
    void dump_data(int len, vector <teacher> &arr);




/**
    @function dump_data
    Сохраняет массив с экземплярами класса student в файл с студентами
    @param arr - массив с студентами, который надо сохранить
    @param len - длина массива arr
*/
    void dump_data(int len, vector <student> &arr);





/**
    @function is_login_exist
    Возвращает 0,если логина не существует, индекс пользователя с этим логином в массиве + 1, если существует.
    @param login - логин, наличие которого надо проверить
*/
    int is_login_exist(char* login);




/**
    @function is_group_exist
    Функция, которая проверяет, есть ли студент с данной группой, если есть то возвращает 1, загружает в массив предметы этой группы,
    иначе возвращает 0.
    @param group
    @param subjects куда будут загружаться предметы, если студент с данной группой нашелся
    @return 1 - студент с такой группой есть
    @return 0 - нету
*/
    int is_group_exist(int group, int* subjects);




/**
    @function ask_to_subj
    Функция, которая просит выбрать предмет из arr, возвращает индекс номера выбранного предмета.
    @param arr - массив с номерами предметов
    @param ex - экземпляр класса subject_index, через который по номеру предмета можно получать название предмета
    @return return subj - 1  индекс номера выбранного предмета
*/
    int ask_to_subj(int* arr, subject_index ex);




/**
    @function cin_login
    Функция для получения логина в login
    @param login - куда считать логин
*/
    void cin_login(char* login);




/**
    @function cin_password
    Функция для получения пароля в password
    @param password - куда считать пароль
*/
    void cin_password(char* password);




/**
    @function create_password
    Функция для создания пароля, перед копированием в password надо чтобы пользователь ввел 2 раза подряд пароль верно.
    @param password - куда копируется пароль
*/
    void create_password(char* password);
};














