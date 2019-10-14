#include <iostream>
#include <fstream>
#include <sstream>
unsigned int table[128]={199,252,233,226,228,224,229,231,234,235,232,239,238,236,196,197,201,230,198,244,246,242,251,249,255,214,220,162,163,165,8359,402,
225,237,243,250,241,209,170,186,191,8976,172,189,188,161,171,187,9617,9618,9619,9474,9508,9569,9570,9558,9557,9571,9553,9559,9565,9564,9563,9488,
9492,9524,9516,9500,9472,9532,9566,9567,9562,9556,9577,9574,9568,9552,9580,9575,9576,9572,9573,9561,9560,9554,9555,9579,9578,9496,9484,9608,9604,9612,
9616,9600,945,223,915,960,931,963,181,964,934,920,937,948,8734,966,949,8745,8801,177,8805,8804,8992,8993,247,8776,176,8729,183,8730,8319,178,9632,160};
using namespace std;
string unicode(unsigned int decimal)
{
    string simbolis;
    if (decimal <= 0x7F) {
        simbolis="0";
        simbolis[0] = (decimal & 0x7F);
       // simbolis[1] = '\0';
        return simbolis;
    }
    else if (decimal <= 0x7FF) {
        simbolis="01";
        simbolis[1] = 0x80 | (decimal & 0x3F);
        decimal = (decimal >> 6);
        simbolis[0] = 0xC0 | (decimal & 0x1F);
       // simbolis[2] = '\0';
          return simbolis;
    }
    else if (decimal <= 0xFFFF) {
        simbolis="013";
        simbolis[2] = 0x80 | (decimal & 0x3F);
        decimal = (decimal >> 6);
        simbolis[1] = 0x80 | (decimal & 0x3F);
        decimal = (decimal >> 6);
        simbolis[0] = 0xE0 | (decimal & 0xF);
      //  simbolis[3] = '\0';
    }
    else if (decimal <= 0x10FFFF) {
        simbolis="0123";
        simbolis[3] = 0x80 | (decimal & 0x3F);
        decimal = (decimal >> 6);
        simbolis[2] = 0x80 | (decimal & 0x3F);
        decimal = (decimal >> 6);
        simbolis[1] = 0x80 | (decimal & 0x3F);
        decimal = (decimal >> 6);
        simbolis[0] = 0xF0 | (decimal & 0x7);
       // simbolis[4] = '\0';
    }
    else {
        simbolis="012";
        simbolis[2] = 0xEF;
        simbolis[1] = 0xBF;
        simbolis[0] = 0xBD;
       // simbolis[3] = '\0';
    }
      return simbolis;
}
int main()
{
ofstream outfile ("rez.txt");
ifstream in("386intel.txt");
    char c;
    if(in.is_open()) {
        while(in.good()) {

            in.get(c);
        unsigned char o=c;
     int f=int(o);
        if(f<127){
        outfile<<c;
        }
        else
            {
            outfile<<unicode(table[f-128]);
            }
    }
    if(!in.eof() && in.fail()){
        cout << "error reading " << "386intel.txt" << endl;}

    in.close();
    }
return 0;
}
