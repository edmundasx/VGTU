#include "read.h"
read::read(string filename, int pos){
//lines=countlines(filename);
//openfile(filename, Object);
cdirection='r';
state=0;
lines=0;
string line;
ifstream file(filename);
  if (file.is_open())
  {
    if (getline(file, line)){
    step = stoi(line);}
    if (getline(file, line)){
    vector<char> tape(line.begin(), line.end());
    Tape=tape;
    }
    while (!file.eof())
    {
      getline (file,line);
      if(line!=""){
        lines++;
      }
    }
    file.close();
  }
  else {
    cout << "Unable to open file";
  }
Instructions Object[lines];
int x(0);
file.open(filename);
  if (file.is_open())
  {
    if (getline(file, line)){
    step = stoi(line);
    }
    if (getline(file, line)){
    while (!file.eof())
    {
      getline (file,line);
      if(line!=""){
        istringstream temp(line);
        vector<string> results((istream_iterator<string>(temp)), istream_iterator<string>());
        istringstream tempnr(results[0]);
        int number=0;
        tempnr>>number;
        Object[x].current_state=number;
        istringstream tempchar(results[1]);
        char tempchr='x';
        tempchar>>tempchr;
        Object[x].current_symbol=tempchr;
        istringstream tempcharx(results[2]);
        tempcharx>>tempchr;
        Object[x].new_symbol=tempchr;
        istringstream tempcharxx(results[3]);
        tempcharxx>>tempchr;
        Object[x].direction=tempchr;
        istringstream tempnrx(results[4]);
        tempnrx>>number;
        Object[x].new_state=number;
        x++;
      }
    }
    file.close();
  }
  }
  else{
    cout << "Unable to open file";
  }

simulate(Tape, Object, state, pos);
}

int read::check(Instructions m[], int &state, char &symbol)
{
for(int i=0;i<lines;i++)
{
if(m[i].current_state==state&&m[i].current_symbol==symbol)
{return i;}
}
return -1;
}

void read::funkcija(struct Instructions m[], int &state, char &symbol, int &index, char &direction)
{
symbol=m[index].new_symbol;
state=m[index].new_state;
direction=m[index].direction;
}

void read::gotoxy(int eex, int eey)
{
  COORD coord;
  coord.X = eex;
  coord.Y = eey;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void read::simulate(vector<char> &Tape, struct Instructions m[], int &state, int pos){
int x, y, lastx, lasty;
x = step-1; y = pos;
lastx = x; lasty = pos;
setbuf(stdout, NULL);
int head(0);
int steps(0);
int i=step-1;
while(true)
{
    mtx.lock();
    int index=check(m,state,Tape[i]);
    if(index!=-1){
    funkcija(m, state, Tape[i], index,cdirection);
    fflush(stdout);
    gotoxy(lastx, lasty);
    //printf("^");
    printf("\b");
    Sleep(2);
    cout.flush();
    //system("cls");
    gotoxy(0, pos-1);
    for(int i=0;i<Tape.size();i++){printf("%c",Tape[i]);}
    lastx = x; lasty = y;
    if(cdirection=='l'||cdirection=='L')
        {
            i--;
            x--;
       }
       else{
    i++;
    x++;
       }
cout<<endl;
cout<<endl;
    steps++;
    }
    else
        {
    fflush(stdout);
    gotoxy(0, pos-1);
    system("cls");
    cout<<"HALTED AT STATE: "<<state<<" SYMBOL: "<<"'"<<Tape[i]<<"'"<<endl;
             mtx.unlock();
            break;
        }
        mtx.unlock();
}
}
