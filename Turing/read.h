#ifndef READ_H
#define READ_H
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <windows.h>
#include <mutex>
using namespace std;

static mutex mtx;
class read
{
private:
struct Instructions{
int current_state;
char current_symbol;
char new_symbol;
char direction;
int new_state;
};
void gotoxy(int eex, int eey);
public:
int state;
read(string filename, int pos);
char cdirection;
int lines;
int step;
vector<char>Tape;
int countlines(string filename);
void openfile(string filename, struct Instructions m[]);
void simulate(vector<char> &Tape, struct Instructions m[], int &state, int pos);
int check(struct Instructions m[], int &state, char &symbol);
void funkcija(struct Instructions m[], int &state, char &current_symbol, int &index, char &direction);
};

#endif // READ_H
