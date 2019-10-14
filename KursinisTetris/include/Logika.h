#ifndef LOGIKA_H
#define LOGIKA_H
#include "Blokai.h"
#include <iomanip>
#include <iostream>
#include <vector>
#include <random>
#include <conio.h>
#include <Overload.h>
using namespace std;
 struct Random
{
    Random(int min, int max)
        : mUniformDistribution(min, max)
    {}
    int operator()()
    {
        return mUniformDistribution(variklis);
    }
    default_random_engine variklis{random_device()() };
    uniform_int_distribution<int>mUniformDistribution;
};
class Logika
{
    private:
int fonas[25][15];
int laukas[25][15];

    bool PabaigBool;
    int y;
    int x;
    int GREITIS;
    public:
    Logika();
    ~Logika();
    Random getRandom{ 0, 6 };
    void Ciklas();
    void Vaizdas();
    bool KurtiBloka();
    void Pradzia();
    void Valdyti(int, int);
    void Susidurimas();
    bool ArSusidure(int, int);
    void Ivestis();
    bool Apversti();
    void RodytiBloka();
    int Pabaiga();


};

#endif // LOGIKA_H
