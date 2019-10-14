#include <iostream>
#include <fstream>

using namespace std;
int xor1(int number1, int number2)
{
return (number1)&(~number2)|(~number1)&(number2);
};
int xor2(int number1, int number2)
{
return ~(~(~number1|~number2)|~number1)|~(~(~number1|~number2)|~number2);
};
int xor3(int number1, int number2)
{
return (number1|number2)&~(number1&number2);
};
int xor4(int number1, int number2)
{
	return (number1|number2)&(~number1|~number2);
};
int main(int argc, int argv[])
{
    int number1=argv[1];
    int number2=argv[2];
	fstream myfile ("rez.csv");
    myfile.open ("rez.csv",ios::out | ios::app);
    myfile<<"Edmundas Kaminskas PRIF18/4"<<'\n';
    myfile<<"XOR1: "<<xor1(number1,number2)<<'\n';
    myfile<<"XOR2: "<<xor2(number1,number2)<<'\n';
    myfile<<"XOR3: "<<xor3(number1,number2)<<'\n';
    myfile<<"XOR4: "<<xor4(number1,number2)<<'\n';
	myfile.close();
    return 0;
}
