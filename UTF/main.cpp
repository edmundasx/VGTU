#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;
void unicode(unsigned int decimal)
{
    char simbolis[5];
    if (decimal <= 0x7F) {
        simbolis[0] = (decimal & 0x7F);
        printf("%x", (unsigned int)(unsigned char)simbolis[0]);
        simbolis[1] = '\0';
    }
    else if (decimal <= 0x7FF) {
        simbolis[1] = 0x80 | (decimal & 0x3F);
        decimal = (decimal >> 6);
        simbolis[0] = 0xC0 | (decimal & 0x1F);
        simbolis[2] = '\0';
    printf("%x", (unsigned int)(unsigned char)simbolis[0]);
        printf(" ");
    printf("%x", (unsigned int)(unsigned char)simbolis[1]);
    }
    else if (decimal <= 0xFFFF) {
        simbolis[2] = 0x80 | (decimal & 0x3F);
        decimal = (decimal >> 6);
        simbolis[1] = 0x80 | (decimal & 0x3F);
        decimal = (decimal >> 6);
        simbolis[0] = 0xE0 | (decimal & 0xF);
        simbolis[3] = '\0';
    printf("%x", (unsigned int)(unsigned char)simbolis[0]);
    printf(" ");
    printf("%x", (unsigned int)(unsigned char)simbolis[1]);
    printf(" ");
    printf("%x", (unsigned int)(unsigned char)simbolis[2]);
    }
    else if (decimal <= 0x10FFFF) {
        simbolis[3] = 0x80 | (decimal & 0x3F);
        decimal = (decimal >> 6);
        simbolis[2] = 0x80 | (decimal & 0x3F);
        decimal = (decimal >> 6);
        simbolis[1] = 0x80 | (decimal & 0x3F);
        decimal = (decimal >> 6);
        simbolis[0] = 0xF0 | (decimal & 0x7);
        simbolis[4] = '\0';
    printf("%x", (unsigned int)(unsigned char)simbolis[0]);
    printf(" ");
    printf("%x", (unsigned int)(unsigned char)simbolis[1]);
    printf(" ");
    printf("%x", (unsigned int)(unsigned char)simbolis[2]);
    printf(" ");
    printf("%x", (unsigned int)(unsigned char)simbolis[3]);
    }
    else {
        simbolis[2] = 0xEF;
        simbolis[1] = 0xBF;
        simbolis[0] = 0xBD;
        simbolis[3] = '\0';
    printf("%x", (unsigned int)(unsigned char)simbolis[0]);
    printf(" ");
    printf("%x", (unsigned int)(unsigned char)simbolis[1]);
    printf(" ");
    printf("%x", (unsigned int)(unsigned char)simbolis[2]);

    }
    cout<<endl;
    cout<<simbolis<<endl;
}
void convert_to_hex(int decimal)
{
string answer=" ";
int remainder;
while(decimal>0)
{
    remainder=decimal%16;
    if(remainder>9)
        {
        switch(remainder)
        {
            case 10:  answer="A"+answer; break;
            case 11:  answer="B"+answer; break;
            case 12:  answer="C"+answer; break;
            case 13:  answer="D"+answer; break;
            case 14:  answer="E"+answer; break;
            case 15:  answer="F"+answer; break;
        }
    }
    else
        {
        stringstream ss;
        ss<<remainder;
        string number(ss.str());
        answer=number+answer;
        }
        decimal=decimal/16;
}
if(decimal<=0xFFFF){
cout<<"U+"<<setfill('0')<<setw(5)<<answer<<endl;}
else if(decimal<=0x100000){
cout<<"U+"<<setfill('0')<<setw(6)<<answer<<endl;}
else{
cout<<"U+"<<setfill('0')<<setw(7)<<answer<<endl;}
}
int main()
{
    int n;
    scanf("%d",&n);
    convert_to_hex(n);
    unicode(n);

    return 0;
}
