#include "Logika.h"
#include "Blokai.h"
#include <iomanip>
#include <iostream>
#include <vector>
#include <random>
#include <conio.h>
#include <Overload.h>
using namespace std;
//Konstruktorius
Logika::Logika():PabaigBool(false),y(0),x(4),GREITIS(20000){}
//Destruktorius
Logika::~Logika()
{
delete []  blokai;
delete []  Blokas;
delete []  laukas;
delete []  fonas;
}
void Logika::Ciklas()
{
    int time = 0;
    Pradzia();
    while (!PabaigBool)
    {
        if (kbhit())
        {
            Ivestis();
        }

        if (time < GREITIS)
        {
            time++;
        }
        else
        {
            RodytiBloka();
            time = 0;
        }
    }
}
int Logika::Pabaiga()
{
    char a;
    cout << "PABAIGA"<<endl;
    cout << "Spauskite Mygtuka Noredami Testi";
    cin >> a;
    this->~Logika();
    return 0;
}
void Logika::Vaizdas()
{
    system("cls");
    //Vaizdo Atnaujinimas
    for (int i = 0; i < 24; i++)
    {
        for (int j = 0; j < 14; j++)
        {
            switch (laukas[i][j])
            {
            case 0:
                cout << " " << flush;
                break;
            case 2:
                cout << "*" << flush;
                break;
            default:
                cout << "o" << flush;
                break;
            }
        }
        cout << endl;
    }
    if (PabaigBool)
    {
        system("cls");
        Pabaiga();
    }
}
void Logika::Pradzia()
{
    //Remai, tam tikrose kordinate bus priskiriame reiksme, per kuria bus piesiamas vaizda
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 15; j++)
        {

            if ((j == 0) || (j == 13) || (i == 23))
            {

                laukas[i][j] = fonas[i][j] = 2;
            }
            else
            {
                //Tuscia Erdve
                laukas[i][j] = fonas[i][j] = 0;
            }
        }
    }
    //Ismetame Bloka
    KurtiBloka();
    //Atnaujiname Vaizda
    Vaizdas();
}
bool Logika::KurtiBloka()
{

    x = 4;
    y = 0;

    int BlokoTipas = getRandom();
    //Random budu traukiame 2D bloka is figuru masyvo
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Blokas[i][j] = 0;
            Blokas[i][j] = blokai[BlokoTipas][i][j];
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            //BinarinisOverload
            laukas[i][j + 4] = fonas[i][j + 4] + Blokas[i][j];

            if (laukas[i][j + 4] > 1)
            {
                PabaigBool = true;
                return true;
            }
        }
    }
    return false;
}
void Logika::Valdyti(int x2, int y2)
{

    //Pasalinti Bloka
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            laukas[y + i][x + j] -= Blokas[i][j];
        }
    }
    //Atnaujinti kordinates
    x = x2;
    y = y2;

    // Priskirti bloka atnaujintai reiksmei
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            laukas[y + i][x + j] += Blokas[i][j];
        }
    }
    //Atnaujiname Lauke
    Vaizdas();
}

void Logika::Susidurimas()
{
    for (int i = 0; i<21; i++)
    {
        for (int j = 0; j<12; j++)
        {
            fonas[i][j] = laukas[i][j];
        }
    }
}
bool Logika::ArSusidure(int x2, int y2)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (Blokas[i][j] && fonas[y2 + i][x2 + j] != 0)
            {
                return true;
            }
        }
    }
    return false;
}
void Logika::Ivestis()
{
    char key;

    key = getch();

    switch (key)
    {
    case 'd':
        if (!ArSusidure(x + 1, y))
        {
            Valdyti(x + 1, y);
        }
        break;
    case 'a':
        if (!ArSusidure(x - 1, y))
        {
            Valdyti(x - 1, y);
        }
        break;
    case 's':
        if (!ArSusidure(x, y + 1))
        {
            Valdyti(x, y + 1);
        }
        break;
    case ' ':
        Apversti();
    }
}
bool Logika::Apversti()
{
    vector<vector<int>> tmp(4, vector<int>(4, 0));

    for (int i = 0; i < 4; i++)
    { //Issaugoti laikina bloka
        for (int j = 0; j < 4; j++)
        {
            tmp[i][j] = Blokas[i][j];
        }
    }

    for (int i = 0; i < 4; i++)
    { //Apversti
        for (int j = 0; j < 4; j++)
        {
            Blokas[i][j] = tmp[3 - j][i];
        }
    }

    if (ArSusidure(x, y))
    { // Sustabdyti
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                Blokas[i][j] = tmp[i][j];
            }
        }
        return true;
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
        //BinarinisOverload

        laukas[y + i][x + j] -= tmp[i][j];
        laukas[y + i][x + j] += Blokas[i][j];
    }
    }
    Vaizdas();
    return false;
}
void Logika::RodytiBloka()
{
    if (!ArSusidure(x, y + 1))
    {
        Valdyti(x, y + 1);
    }
    else
    {
        Susidurimas();
        KurtiBloka();
        Vaizdas();
    }

}
