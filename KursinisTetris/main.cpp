#include <iostream>
#include "Menu.h"
#include "AbstractClassMenu.h"
#include "Overload.h"
using namespace std;

int main()
{


    //Virtaulios funkcijos iskvietimas per AbstractClassMenu
    Menu *pointeris;
    AbstractClassMenu x;
    pointeris = &x;
    pointeris->menu();
    return 0;
}
