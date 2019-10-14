#ifndef MENU_H
#define MENU_H
#include <iostream>

using namespace std;
//Abstrakti klase
class Menu
{
    private:
        int x;
    public:
        Menu();
        virtual void menu();
};

#endif // MENU_H
