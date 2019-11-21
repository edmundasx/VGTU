#include <iostream>
#include <fstream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
struct instructions
{
    char command_code;
    char register_number;
};
int main() {
    instructions object[32];
    char prog_mem[256];
    unsigned char regs[16];
    char mystring [100];
    int REGX;
    int REGY;
    bool endflag = false;
	bool zeroflag = false;
    ofstream outfile ("output.txt");
    fstream in("q1_encr.txt");
    string text;
    FILE * pFile;
    pFile = fopen("decryptor.bin", "rb");
	for (int i = 0; i < 256; i++) {
		fread(prog_mem + i, 1, 1, pFile);
		if (feof(pFile))
        {
            break;
        }
	}
	fclose(pFile);
    for(int i=0;i<32;i+=2)
    {
        object[i].command_code=prog_mem[i];
        object[i].register_number=prog_mem[i+1];
    }
    for(int i=0;i<32;i+=2)
    {
        cout<<hex<<(int)object[i].command_code<<" "<<(int)object[i].register_number<<endl;
    }
    for(int i=0;i<32;i++)
    {
        REGX=object[i].register_number&0x0F;
        REGY=(object[i].register_number&0xF0)>>4;
    switch(object[i].command_code)
        {
    case 0x01:
                if (regs[REGX]==0) {
					zeroflag = true;
				}
            regs[REGX]=regs[REGX]+1;
            break;
    case 0x02:
                if (regs[REGX]==0) {
					zeroflag = true;
				}
            regs[REGX]=regs[REGX]-1;
            break;
    case 0x03:
            regs[REGX]=regs[REGY];
            break;
    case 0x04:
            regs[0]=object[i].register_number;
            break;
    case 0x05:
            regs[REGX]=regs[REGX]<<1;
                if (regs[REGX]==0) {
					zeroflag = true;
				}
            break;
    case 0x06:
            regs[REGX]=regs[REGX]>>1;
                if (regs[REGX]==0) {
					zeroflag = true;
				}
            break;
    case 0x07:
            i=i+object[i].register_number;
            i--;
            break;
     case 0x08:
            if (zeroflag == true) {
                i=i+object[i].register_number;
                i--;
}
            break;
     case 0x09:
            if (zeroflag == false) {
                i=i+object[i].register_number;
                i--;
}
            break;
    case 0x0A:
            if (endflag == true) {
                i=i+object[i].register_number;
                i--;
}
            break;
    case 0x0B:
        in.close();
        return 0;
            break;
    case 0x0D:
              regs[REGX]=regs[REGX]-regs[REGY];
                if (regs[REGX]==0) {
					zeroflag = true;
				}
            break;
    case 0x0E:
              regs[REGX]=regs[REGX]^regs[REGY];
                if (regs[REGX]==0) {
					zeroflag = true;
				}
            break;
    case 0x0F:
              regs[REGX]=regs[REGX]|regs[REGY];
                if (regs[REGX]==0) {
					zeroflag = true;
				}
            break;
    case 0x10:
              in>>regs[REGX];
              				if (in.eof()) {
					endflag = true;
				}
            break;
    case 0x11:
             outfile<<regs[REGX];
        }
    }
}

