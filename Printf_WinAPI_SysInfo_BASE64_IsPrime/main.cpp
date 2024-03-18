#include <iostream>
#include <cstdio>
#include <windows.h>
#pragma comment(lib, "crypt32.lib")
#include <wincrypt.h>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;


const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

string base64_encode(const std::string& input) {
    string encoded;

    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    size_t i = 0;
    size_t input_length = input.length();

    while (input_length--) {
        char_array_3[i++] = input[input.length() - input_length - 1];
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; (i < 4); i++)
                encoded += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i) {
        for (size_t j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

        for (size_t j = 0; (j < i + 1); j++)
            encoded += base64_chars[char_array_4[j]];

        while ((i++ < 3))
            encoded += '=';
    }

    return encoded;
}

void formatError(DWORD errorCode) {
    string msg;
    LPSTR buffer = NULL;
    DWORD messageLength = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        errorCode,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&buffer,
        0,
        NULL
    );

    if (messageLength == 0) {
       cout<<"No such error exists"<<endl;
    }
    else {
        msg = buffer;
        LocalFree(buffer);
            cout << "Message "<<errorCode<< ": "<< msg << endl;
    }


}

void function2()
{
   int errorCode;
    cin >> errorCode;
    formatError(errorCode);
    cin >> errorCode;
    formatError(errorCode);
    cin >> errorCode;
    formatError(errorCode);

}

void format_number( ) {
    float num1;
    float num2;
    int num3;
    cin>>num1;
    printf("%.2f\n", num1);
    cin>>num2;
    printf("%.1f\n", num2);
    cin>>num3;
    printf("%.2e\n",(float) num3);


}
void function3(){
 SYSTEM_INFO systemInfo;
    GetNativeSystemInfo(&systemInfo);
    cout << "Number of Logical Processors: " << systemInfo.dwNumberOfProcessors << endl;
    cout << "Page size: " << systemInfo.dwPageSize <<" Bytes"<< endl;
    cout << "Processor Mask: "<< "0x" << setw(16) << setfill('0') << hex << systemInfo.dwActiveProcessorMask << endl;

    printf("Minimum process address: 0x%p\n", systemInfo.lpMinimumApplicationAddress);
    printf("Maximum process address: 0x%p\n", systemInfo.lpMaximumApplicationAddress);
}

void function4(){


    string encoded = base64_encode("Secure Programming");
    cout << encoded << endl;
}



bool isPrime(int n)
{
    if (n <= 1) {
        return false;
    }
    int limit = sqrt(n);
    for (int i = 2; i <= limit; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void function5(){
   int number;
     do{
    cin >> number;
    if(number!=0){
    if (isPrime(number)) {
        cout << "TRUE" << endl;
    } else {
        cout << "FALSE" << endl;
    }}}while(number!=0);
}


int main()
{
    int user_input;
    cout << "1. Formatting the entered number with printf." <<endl;
    cout << "2. Displaying error messages using Windows API." <<endl;
    cout << "3. Displaying system information." <<endl;
    cout << "4. BASE64 computation for \"Secure Programming\" text." <<endl;
    cout << "5. Finding prime numbers." <<endl;

    cin >> user_input;

    switch (user_input) {
        case 1:
            format_number();
            break;
        case 2:
            function2();
            break;
        case 3:
            function3();
            break;
        case 4:
            function4();
            break;
        case 5:
            function5();
            break;
        default:
            cout << "Invalid input. Please enter a number between 1 and 5." << endl;
            break;
    }
}
