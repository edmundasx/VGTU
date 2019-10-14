#include <iostream>
#include  <thread>
#include <iomanip>
#include <conio.h>
#include "read.h"
void callobj(string name, int n)
{

    read x(name, n);
}

using namespace std;

int main()
{


    char key;
    string filename;
    unsigned int padding = 50 ;
    cout << setw(padding) << "Turing Machine Simulator"<<endl;
    cout<<endl;
    cout<<"Options: S - Exit."<<endl;
    cout<<endl;
    cout <<"Enter name of one or multiple .txt files"<<endl;
    cout<<endl;

    getline(cin, filename);
    system("cls");

    istringstream iss(filename);
    vector<string> failai((istream_iterator<string>(iss)),istream_iterator<string>());

    int pos(3);
    thread t[failai.size()];


    for(int i=0;i<failai.size();i++)
    {
        t[i] = thread(callobj,failai[i],pos);
        pos+=3;
    }
      key = getch();
        if(key=='S' || key=='s'){
            exit(0);
        }
    for(int i=0;i<failai.size();i++)
    {
        t[i].join();
    }



/*
system("cls");
thread t(callobj,"1.txt",1);
thread t2(callobj,"2.txt",4);
thread t3(callobj,"3.txt",8);
thread t4(callobj,"4.txt",12);

t.join();
t2.join();
t3.join();
t4.join();
*/





}
