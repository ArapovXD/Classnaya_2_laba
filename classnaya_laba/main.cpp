#include <iostream>
#include <vector>
#include <cstring>
#include "interface.h"


using namespace std;

int main(int argc, char *argv[]){

    if (argc != 4){             ///Завершить программу, если поступило не 3 аргумента в мейн
        cout << "Nujno 3 argumenta! 1 - file s studentami, 2 - file s uchitelami, 3 - file s predmetami\n";
        exit(0);
    }

    while (1){
        cout << "\nstudent - 1, U4itel - 2, registraciya (tolko dla uchiteley) - 3 vihod - 0 ";
        int who;
        cin >> who;
        interface ex(who, argv[1], argv[2], argv[3]);
        ex.show_interface();
    }

    return 0;
}
