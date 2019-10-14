#include "Menu.h"
#include "Logika.h"
#include <iostream>
#include <Overload.h>
using namespace std;
Menu::Menu():x(0){}
void Menu::menu()
{
    Logika x;
    system("cls");

    cout << "KURSINIS DARBAS TETRIS"<<endl;
    cout << "1.Pradeti"<<endl;
    cout << "2.Iseiti"<<endl;
    cout << "Pasirinkite [1-2] ";
    int pasirinkimas = 0;
    cin >> pasirinkimas;
    switch (pasirinkimas)
    {
    case 1: x.Ciklas();
    break;
    case 2:

    case 3:
        break;
    default:
        pasirinkimas = 0;
        break;
    }

};

