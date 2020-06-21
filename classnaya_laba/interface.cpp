#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include "interface.h"
using namespace std;

interface::interface(int val, char* sf_name, char* tf_name, char* sbjf_name){
    call = val;
    strcpy(student_filename, sf_name);
    strcpy(teacher_filename, tf_name);
    strcpy(subject_filename, sbjf_name);
}

void interface::show_interface(){
    switch (call){
        case 1 : authorization(call); break;
        case 2 : authorization(call); break;
        case 3 : show_registration_interface(); break;
    }
}

void interface::show_student_interface(char* my_login){
    while (1){
///Чтобы после каждой выполненной команды обновлялся класс ученика
        vector <student> students;
        student a;
        int len = get_people(students), i = 0;
        for (i; i < len; i++){
            char s_login[50];
            students[i].get_login(s_login);
            if (!strcmp(my_login, s_login)){
                a = students[i];
                break;
            }
        }

        int call;
        cout << "\nPosmotret ocenki - 1\n";
        cout << "Uznat itogovuu ocenku za kurs - 2\n";
        cout << "Posmotret poseshaemost - 3\n";
        cout << "Vihod - 0\n";
        cout << "Viberite komandu: ";
        cin >> call;

        switch (call){
            case 1 : show_grades_or_attendance(a, 0); break;
            case 2 : show_final_rate(a); break;
            case 3 : show_grades_or_attendance(a, 1); break;
            case 0 : exit(0);
        }
    }
}

void interface::show_teacher_interface(char* my_login){

    while (1){
///Чтобы после каждой выполненной команды обновлялся класс учителя
        vector <teacher> teachers;
        teacher a;
        int len = get_people(teachers), i = 0;
        for (i; i < len; i++){
            char t_login[50];
            teachers[i].get_login(t_login);
            if (!strcmp(my_login, t_login)){
                a = teachers[i];
                break;
            }
        }

        int call;
        cout << "\nDobavit studenta v gruppu - 1\n";
        cout << "Uznat tekuwie gruppi - 2\n";
        cout << "Dobavit gruppu - 3\n";
        cout << "Udalit gruppu - 4\n";
        cout << "Perevesti studenta v druguu gruppu - 5\n";
        cout << "Postavit ocenku - 6\n";
        cout << "Vistovit studentu ocenku za kurs - 7\n";
        cout << "Zapolnit poseshaemost gruppi - 8\n";
        cout << "Dobavit predmet - 9\n";
        cout << "Udalit predmet - 10\n";
        cout << "Vigod - 0\n";
        cout << "Vvedite komandu: ";
        cin >> call;

        switch (call){
            case 1 : add_to_group(a); break;
            case 2 : show_curr_groups(a); break;
            case 3 : add_group(teachers, i, len); break;
            case 4 : delete_group(teachers, i, len); break;
            case 5 : to_moove_student(a); break;
            case 6 : give_grades_or_attendance(a, 0); break;
            case 7 : to_final_rate(a); break;
            case 8 : give_grades_or_attendance(a, 1); break;
            case 9 : add_subject(teachers, i, len); break;
            case 10 : delete_subject(teachers, i, len); break;
            case 0 : exit(0);
        }
    }
}


void interface::delete_subject(vector <teacher> teachers, int index, int len){
    char my_login[50];
    teachers[index].get_login(my_login);

    subject_index ex;
    ifstream f;
    f.open(subject_filename);
    f.read((char*)&ex, sizeof(subject_index));
    f.close();

    int t_subjects[100], i = 0;
    for (i; i < 100; i++) t_subjects[i] = -1;
    teachers[index].get_subjects(t_subjects);

    int subj = ask_to_subj(t_subjects, ex);
    subj = t_subjects[subj];

    i = 0;
    while (t_subjects[i] != -1){

        if (t_subjects[i] == subj){
            int p = t_subjects[i + 1];
            if (p != -1){
                t_subjects[i + 1] = t_subjects[i];
                t_subjects[i] = p;
            }
            else t_subjects[i] = -1;
        }
        i++;
    }

    teachers[index].set_subject(t_subjects);
    dump_data(len, teachers);
}


void interface::add_subject(vector <teacher> teachers, int index, int len){

    subject_index ex;
    ifstream f;
    f.open(subject_filename);
    f.read((char*)&ex, sizeof(subject_index));
    f.close();

    char new_subject[50];
    cout << "Vvedite nazvanie predmeta: ";
    cin >> new_subject;

    int res = ex.is_subject_exist(new_subject);

    if (res == -1){
        ex.set_new_subject_name(new_subject);
        ex.set_new_index();
        res = ex.get_len() - 1;
    }

    ofstream ff;
    ff.open(subject_filename);
    ff.write((char*)&ex, sizeof(subject_index));
    ff.close();

    char my_login[50];
    teachers[index].get_login(my_login);


    int t_subjects[100], j = 0;
    for (j; j < 100; j++) t_subjects[j] = -1;

    teachers[index].get_subjects(t_subjects);
    for (j = 0; j < 100; j++){
        if (t_subjects[j] == -1){
            t_subjects[j] = res;
            break;
        }
    }

    teachers[index].set_subject(t_subjects);

    dump_data(len, teachers);

    cout << "Predmet uspeshno dobavlen!\n";

}

void interface::show_final_rate(student a){
    cout << endl;

    subject_index ex;
    ifstream f;
    f.open(subject_filename);
    f.read((char*)&ex, sizeof(subject_index));
    f.close();

    int s_subjects[100], i = 0, j = 0;
    for (i; i < 100; i++) s_subjects[i] = -1;
    a.get_subjects(s_subjects);
    i = 0;

    int subj_index = ask_to_subj(s_subjects, ex);

    cout << "Vvedite posledniy mesyac kursa: ";
    int mk;
    cin >> mk;

    int grade = a.get_grade(s_subjects[subj_index], mk, 32);
    if (grade) cout << "Vawa ocenka za kurs - " << grade << endl;
    else cout << "Ocenka ewe ne vistovlena!\n";
}



void interface::to_final_rate(teacher a){
    cout << endl;

    subject_index ex;
    ifstream f;
    f.open(subject_filename);
    f.read((char*)&ex, sizeof(subject_index));
    f.close();

    int t_subjects[100], i = 0, j = 0;
    for (i; i < 100; i++) t_subjects[i] = -1;
    a.get_subjects(t_subjects);
    i = 0;

    int subj_index = ask_to_subj(t_subjects, ex);

    vector <student> students;
    int len = get_people(students), flag = 0, res;
    char login[50];

    while (1){
        cin_login(login);
        res = is_login_exist(login);
        if (!res) cout << "Logina ne suwestvuet!\n";
        else break;
    }
    res --;

    int s_subjects[100];
    for (j = 0; j < 100; j++) s_subjects[j] = -1;
    students[res].get_subjects(s_subjects);
    j = 0;

    while (s_subjects[j] != -1){
        if (s_subjects[j] == t_subjects[subj_index]){
            flag = 1;
            break;
        }
        j++;
    }

    if (!flag){
        cout << "Student ne imeet takogo predmeta!\n";
    }
    else{
        int dn, mn, dk, mk, i = 0;
        double sum = 0.0, counT = 0.0;
        cout << "Vvedite period ocenivaya: \n";
        cout << "S kakogo nomera mesyaca: ";
        cin >> mn;
        cout << "S kakogo dnya: ";
        cin >> dn;
        cout << "Do kakogo nomera mesyaca: ";
        cin >> mk;
        cout << "Do kakogo dnya: ";
        cin >> dk;

        ///Подсчет данных для вычисления ср.ариф.

        for (mn; mn < (mk + 1); mn++){

            if (mn == mk){
                for (dn; dn < (dk + 1); dn++){
                    int grade = students[res].get_grade(t_subjects[subj_index], mn, dn);
                    if (grade){
                        sum += grade;
                        counT ++;
                    }
                }
            }

            else {
                for (dn; dn < 32; dn++){
                    int grade = students[res].get_grade(t_subjects[subj_index], mn, dn);
                    if (grade){
                        sum += grade;
                        counT ++;
                    }
                    dn = 1;
                }
            }
        }

        students[res].set_grade(t_subjects[subj_index], mk, 32, sum/counT);
        int g = students[res].get_grade(t_subjects[subj_index], mk, 32);
        cout << "Itogovaya za kurs: " << g << endl;

        dump_data(len, students);
    }
}


int interface::ask_to_subj(int* arr, subject_index ex){
    int i = 0;

    while (arr[i] != -1){
        char subj[50];
        ex.get_subject(subj, arr[i]);
        cout << i + 1 << ". " << subj << endl;
        i++;
    }

    int subj;
    cout << "Vvedite nomer predmeta: ";
    cin >> subj;
    return subj - 1;
}


void interface::show_grades_or_attendance(student a, int attendance){
    cout << endl;

    subject_index ex;
    ifstream f;
    f.open(subject_filename);
    f.read((char*)&ex, sizeof(subject_index));
    f.close();

    int s_subjects[100], i = 0, j = 0;
    for (i; i < 100; i++) s_subjects[i] = -1;
    a.get_subjects(s_subjects);
    i = 0;

    int subj_index = ask_to_subj(s_subjects, ex);

    int month, day = 0;
    cout << "Vvedite nomer mesyaca, 0 = za vse vremya: ";
    cin >> month;
    if (month != 0){
        cout << "Vvdeite den, 0 - za ves mesyac: ";
        cin >> day;
    }

    if (month == 0) {
        for (i = 1; i < 13; i++) {
            for (j = 1; j < 32; j++) {
                int val;
                if (attendance){
                    val = a.get_attendance(s_subjects[subj_index], i, j);
                    if (val == 1) cout << i << "." << j << ".20 - " << "bil" << endl << endl;
                    else if (val == -1) cout << i << "." << j << ".20 - " << "ne bil" << endl << endl;
                }
                else {
                    val = a.get_grade(s_subjects[subj_index], i, j);
                    if (val) cout << i << "." << j << ".20 - " << val << endl << endl;
                }
            }
        }
    }

    else if (day == 0) {
        for (i = 1; i < 32; i++) {
            int val;
            if (attendance){
                val = a.get_attendance(s_subjects[subj_index], month, i);
                if (val == 1) cout << month << "." << i << "bil " << val << endl;
                else if (val == -1) cout << month << "." << i << "ne bil " << val << endl;
            }
            else{
                val = a.get_grade(s_subjects[subj_index], month, i);
                if (val) cout << month << "." << i << ".20 - " << val << endl;
            }
        }
    }
    else {
        int val;
        if (attendance){
            val = a.get_attendance(s_subjects[subj_index], month, day);
            if (val == 1) cout << month << "." << day << "bil " << val << endl;
            else if (val == -1) cout << month << "." << day << "ne bil " << val << endl;
        }
        else{
            val = a.get_grade(s_subjects[subj_index], month, day);
            if (val) cout << month << "." << day << ".20 - " << val << endl;
        }

    }
}

void interface::give_grades_or_attendance(teacher a, int attendance){
    cout << endl;

    vector <student> students;
    int len = get_people(students);

    subject_index ex;
    ifstream f;
    f.open(subject_filename);
    f.read((char*)&ex, sizeof(subject_index));
    f.close();

    int t_subjects[100], i = 0;
    for (i; i < 100; i++) t_subjects[i] = -1;
    a.get_subjects(t_subjects);

    int subj = ask_to_subj(t_subjects, ex);

    int s_subjects[100], j = 0;
    for (j; j < 100; j++) s_subjects[j] = -1;
    int group, res = 0, flag = 0;

    while(!res){
        cout << "Vvedite gruppu: ";
        cin >> group;
        res = is_group_exist(group, s_subjects);
        if (!res) cout << "Eta gruppa pusta!\n";
    }

    j = 0;
    while (s_subjects[j] != -1){
        if (s_subjects[j] == t_subjects[subj]){
            flag = 1;
            break;
        }
        j++;
    }

    j = 0;
    int t_groups[100]{}, flag2 = 0;
    a.get_groups(t_groups);
    while(t_groups[j]){
        if (t_groups[j] == group){
            flag2 = 1;
        }
        j++;
    }

    if (!flag2) cout << "Net dostupa k etoy gruppe!\n";
    else if (!flag){
        cout << "U gruppi net takogo predmeta!\n";
    }
    else{
        int month, day;
        cout << "Vvedite nomer mesyaca: ";
        cin >> month;
        cout << "Vvedite nomer dnya: ";
        cin >> day;

        i = 0;
        for (i; i < len; i ++){
            int s_group = students[i].get_group();
            if (s_group == group){
                char s_login[50];
                students[i].get_login(s_login);
                if (attendance) cout << "Vvedite 1 esli bil, -1 ina4e " << s_login << " ";
                else cout << "Vvedite ocenku " << s_login << " - ";
                int grade;
                cin >> grade;

                if (attendance) students[i].set_attendance(subj, month, day, grade);
                else students[i].set_grade(subj, month, day, grade);
            }
        }

        dump_data(len, students);
        cout << "Ocenki uspeshno vistavleni!\n";
    }

}

void interface::to_moove_student(teacher a){
    vector <student> students;
    int len = get_people(students), i = 0, new_group, flag = 0, flag2 = 0;
    int new_subjects[100], s_index;
    for (i; i < 100; i++) new_subjects[i] = -1;
    i = 0;
    char login[50];
    cout << endl;
    cin_login(login);
    cout << "Vvedite novuu gruppu: ";
    cin >> new_group;

    for (i; i < len; i++){
        char s_login[50];
        students[i].get_login(s_login);

        if (!strcmp(login, s_login)){
            s_index = i;
            int s_group = students[i].get_group();

            int my_groups[100]{}, j = 0;
            a.get_groups(my_groups);

            while (my_groups[j]){
                if (my_groups[j] == s_group){
                    flag = 1;
                    break;
                }
                j++;
            }
        }

        else if (students[i].get_group() == new_group){

            students[i].get_subjects(new_subjects);
            flag2 = 1;
        }
    }

    if (!flag){
        cout << "Net dostupa k studentu, t.k. on ne prinadlezit vashim gruppam!\n";
    }
    else{
        students[s_index].set_group(new_group);
        if (flag2) students[s_index].set_subject(new_subjects);
        dump_data(len, students);
        cout << "Gruppa u studenta " << login << " uspeshno izmenena!\n";
    }

}



void interface::delete_group(vector <teacher> teachers, int index, int len){

    int group;
    cout << "\nVvedite gruppu: ";
    cin >> group;
    int t_groups[100]{}, i = 0;
    teachers[index].get_groups(t_groups);

    while (t_groups[i]){

        if (t_groups[i] == group){
            int p = t_groups[i + 1];
            if (p != 0){
                t_groups[i + 1] = t_groups[i];
                t_groups[i] = p;
            }
            else t_groups[i] = 0;
        }
        i++;
    }

    teachers[index].set_groups(t_groups);

    dump_data(len, teachers);

    cout << "Uspeshno udaleno!\n";
}



void interface::dump_data(int len, vector <teacher> &arr){
    int i;
    ofstream f;
    f.open(teacher_filename);
    for (i = 0; i < len; i++) f.write((char*)&arr[i], sizeof(teacher));
    f.close();
}

void interface::dump_data(int len, vector <student> &arr){
    int i;
    ofstream f;
    f.open(student_filename);
    for (i = 0; i < len; i++) f.write((char*)&arr[i], sizeof(student));
    f.close();
}

void interface::add_group(vector <teacher> teachers, int index, int len){

    int group, t_groups[100]{};
    teachers[index].get_groups(t_groups);

///Проверка на наличие введенной группы
    while (1){
        cout << "\nVvedite gruppu: ";
        cin >> group;
        int j = 0, flag = 1;
        while (t_groups[j]){
            if (t_groups[j] == group){
                cout << "U vas uze est eta gruppa!\n";
                flag = 0;
                break;
            }
            j++;
        }
        if (flag) break;
    }

    int i = 0;
    while (1){
        if (t_groups[i] == 0){
            t_groups[i] = group;
            break;
        }
        i++;
    }
    teachers[index].set_groups(t_groups);

    dump_data(len, teachers);

    cout << "Gruppa uspeshno dobavlena!\n";
}




int interface::is_group_exist(int group, int* subjects){
    vector <student> students;
    int len = get_people(students), i;

    for (i = 0; i < len; i++){
        if (students[i].get_group() == group){
            students[i].get_subjects(subjects);
            return 1;
        }
    }

    return 0;
}

void interface::authorization(int call){

    while(1){
        char login[50];
        char password[50];
        cin_login(login);
        cin_password(password);

        int res = is_login_exist(login);

        if (!res){
            cout << "Ne pravilno vveden login ili parol!\n";
            continue;
        }

        if (call == 1){
            vector <student> students;
            int len = get_people(students);
            char student_password[50];
            students[res - 1].get_password(student_password);

            if (strcmp(password, student_password)){
                cout << "Ne pravilno vveden login ili parol!\n";
                continue;
            }
            else{
                cout << "Dobro pojalovat!";
                char s_login[50];
                students[res - 1].get_login(s_login);
                show_student_interface(s_login);
                break;
            }
        }

        if (call == 2){

            vector <teacher> teachers;
            int len = get_people(teachers);
            char teacher_password[50];
            teachers[res - 1].get_password(teacher_password);

            if (strcmp(password, teacher_password)){
                cout << "Ne pravilno vveden login ili parol!\n";
                continue;
            }
            else{
                cout << "\nDobro pojalovat!";
                char t_login[50];
                teachers[res - 1].get_login(t_login);
                show_teacher_interface(t_login);
                break;
            }
        }
    }

}


void interface::show_curr_groups(teacher a){
    int groups[100]{}, i = 0;
    a.get_groups(groups);
    cout << "\nVashi gruppi: ";
    while (groups[i] != 0){
        cout << groups[i] << " ";
        i++;
    }
    cout << endl;
}


void interface::add_to_group(teacher a){

    subject_index ex;
    ifstream f;
    f.open(subject_filename);
    f.read((char*)&ex, sizeof(subject_index));
    f.close();

    int group;
    int subjects[100], i;
    for (i = 0; i < 100; i++) subjects[i] = -1;

///Если студент с введенной группой существует, то в subjects запишутся номера его предметов, иначе надо ввести самому
    while (1){
///Можем добавлять студентов только в группы учителя
        while (1){
            cout << "\nVvedite gruppu: ";
            cin >> group;
            int teacher_groups[100], i = 0, flag = 0;
            a.get_groups(teacher_groups);
            while (teacher_groups[i] != 0) {
                if (teacher_groups[i] == group){
                    flag = 1;
                    break;
                }
                i++;
            }
            if (!flag) cout << "Net dostupa k etoy gruppe!\n";
            else break;
        }

        int res = is_group_exist(group, subjects);

        if (!res){

            int i = 0, n;
            int len_ss = 0;

            int amount_of_subjects = ex.get_len();
            char subj[50];

            cout << "Vvedite kol-vo predmetov: ";
            cin >> n;

            for (i; i < n; i++){
                cout << "Vvedite nazvanie predmeta " << i + 1 << ": ";
                cin >> subj;
                int res = ex.is_subject_exist(subj);

                if (res != -1){
                    subjects[len_ss] = res;
                    len_ss ++;
                }

                else{
                    subjects[len_ss] = ex.get_len();
                    ex.set_new_index();
                    ex.set_new_subject_name(subj);
                    len_ss++;
                }
            }
            break;
        }
        else break;
    }

    i = 0;

    char login[50];
    while (1){
        int res;
        cin_login(login);
        res = is_login_exist(login);
        if (!res) break;
        else cout << "Takoy login uze suwestvuet!\n";
    }

    char password[50];
    create_password(password);

    student b;
    b.set_group(group);
    b.set_login(login);
    b.set_password(password);
    b.set_subject(subjects);

    append_data(b);
    ofstream ff;
    ff.open(subject_filename);
    ff.write((char*)&ex, sizeof(subject_index));
    ff.close();
    cout << "Student uspeshno dobavlen!\n";
}


void interface::cin_login(char* login){
    cout << "Vvedite login: ";
    cin >> login;
}

void interface::cin_password(char* password){
    cout << "Vvedite parol: ";
    cin >> password;
}

void interface::create_password(char* password){
    char password1[50], password2[50];
    while (1){
        password1;
        cin_password(password1);
        cout << "Povtorite parol: ";
        cin >> password2;
        if (!strcmp(password1, password2)){
            strcpy(password, password1);
            break;
        }
        else cout << "Ne verno!\n";
    }
}


int interface::get_people(vector <teacher> &arr){
    ifstream f;
    int i = 0;
    f.open(teacher_filename);

    teacher a;

    while (f.read((char*)&a, sizeof(teacher))){
        arr.push_back(a);
        i++;
    }

    f.close();

    return i;
}


int interface::get_people(vector <student> &arr){
    ifstream f;
    int i = 0;
    f.open(student_filename);

    student a;
    while (f.read((char*)&a, sizeof(student))){
        arr.push_back(a);
        i++;
    }
    f.close();

    return i;
}



int interface::is_login_exist(char* login){
    ifstream f1;
    ifstream f2;
    f1.open(student_filename);
    f2.open(teacher_filename);

    vector <teacher> teachers;
    int len_t = get_people(teachers);

    vector <student> students;
    int len_s = get_people(students);

    int i;
    for (i = 0; i < len_t; i++){
        char t_login[50];
        teachers[i].get_login(t_login);
        if (!strcmp(t_login, login)){
            f1.close();
            f2.close();
            return i + 1;
        }
    }

    for (i = 0; i < len_s; i++){
        char s_login[50];
        students[i].get_login(s_login);
        if (!strcmp(s_login, login)){
            f1.close();
            f2.close();
            return i + 1;
        }
    }

    f1.close();
    f2.close();
    return 0;
}


void interface::append_data(teacher &a){
    fstream f;
    f.open(teacher_filename, fstream::app);
    f.write((char*)&a, sizeof(teacher));
    f.close();
}

void interface::append_data(student &a){
    fstream f;
    f.open(student_filename, fstream::app);
    f.write((char*)&a, sizeof(student));
    f.close();
}


void interface::show_registration_interface(){

    subject_index ex;
    ifstream f;
    f.open(subject_filename);
    f.read((char*)&ex, sizeof(subject_index));
    f.close();

    int i = 0, n;
    int teacher_subjects[100], len_ts = 0;
    for (i; i < 100; i++) teacher_subjects[i] = -1;
    i = 0;
    int amount_of_subjects = ex.get_len();
    char subj[50];

    cout << "\nVvedite kol-vo predmetov: ";
    cin >> n;


    for (i; i < n; i++){
        cout << "Vvedite nazvanie predmeta " << i + 1 << ": ";
        cin >> subj;

        int res = ex.is_subject_exist(subj);

        if (res != -1){
            teacher_subjects[len_ts] = res;
            len_ts ++;
        }

        else{
            teacher_subjects[len_ts] = ex.get_len();
            ex.set_new_index();
            ex.set_new_subject_name(subj);
            len_ts++;
        }
    }


    i = 0;

// Заканчиваем ввод предметов.......................................................


// Вводим группы....................................................................

    int teacher_groups[100]{}, group, len_tg = 0;

    cout << "\nVvedite kol-vo grupp: ";
    cin >> n;
    cout << "Vvedite gruppu " << 1 << ": ";
    cin >> teacher_groups[0];


    for (i = 1; i < n; i++){

        while (1){

            bool flag = 0;
            cout << "Vvedite gruppu " << i + 1 << ": ";
            cin >> group;

            int j;
            for (j = 0; j < i; j++){
                if (teacher_groups[j] == group){
                    cout << "Takaya gruppa uze est!\n";
                    break;
                }
                else if (j == (i - 1)){
                    teacher_groups[i] = group;
                    flag = 1;
                }
            }
            if (flag) break;
        }
    }

// Заканчиваем ввод групп...........................................................


// Начинаем загрузку учителя........................................................

    teacher a;
    char login[50];
    while (1){
        cin_login(login);
        int res = is_login_exist(login);
        if (!res) break;
        else cout << "Takoy login uze sushestvuet!\n";
    }

    char password[50];
    create_password(password);


    a.set_subject(teacher_subjects);
    a.set_groups(teacher_groups);
    a.set_login(login);
    a.set_password(password);

    append_data(a);
    ofstream ff;
    ff.open(subject_filename);
    ff.write((char*)&ex, sizeof(subject_index));
    ff.close();
    cout << "Uspeshnaya registraciya!\n";

// Заканчиваем загрузку учителя........................................................
}


