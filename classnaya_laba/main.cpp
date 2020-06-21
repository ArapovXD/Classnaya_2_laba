#include <iostream>
#include <vector>
#include <cstring>
#include "interface.h"


using namespace std;

int main(int argc, char *argv[]){

/*
    if (argc != 4){             ///Завершить программу, если поступило не 3 аргумента в мейн
        cout << "Nujno 3 argumenta! 1 - file s studentami, 2 - file s uchitelami, 3 - file s predmetami\n";
        exit(0);
    }
*/
    char a[50] = "students.bin";
    char b[50] = "teachers.bin";
    char c[50] = "subject_class.bin";

    while (1){
        cout << "\nstudent - 1, U4itel - 2, registraciya (tolko dla uchiteley) - 3 vihod - 0 ";
        int who;
        cin >> who;
        interface ex(who, a, b, c);
        ex.show_interface();
    }

    return 0;
}
