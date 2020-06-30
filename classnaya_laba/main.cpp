#include <iostream>
#include <vector>
#include <cstring>
#include "interface.h"
using namespace std;

/**
    @function main
    В мейн нужно дать 4 файла, 1-ый, где будут храниться студенты, 2 - учителя, 3 - предметы, 4 - группы учителя.
    После проверки на аргументы создается экземпляр ex класса interface с передачей в конструктор имен файлов и команды,
    управление переходит методу show_interface.
*/

int main(int argc, char *argv[]){


    if (argc != 5){             ///Завершить программу, если поступило не 4 аргумента в мейн
        cout << "Nujno 4 argumenta! 1 - file s studentami, 2 - file s uchitelami, 3 - file s predmetami, 4 - file s gruppami u4itela\n";
        exit(0);
    }

    while (1){
        cout << "\nstudent - 1, U4itel - 2, registraciya (tolko dla uchiteley) - 3 vihod - 0 ";
        int who;
        cin >> who;
        interface ex(who, argv[1], argv[2], argv[3], argv[4]);
        ex.show_interface();
    }

    return 0;
}
