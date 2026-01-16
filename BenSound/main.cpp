#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <memory>

using namespace std;

void menu(HANDLE& file, DWORD& fileSize, /*DWORD& readBytes,*/ LPVOID& metadata, string& title, string& artist, string& album);
void displayMetadata(HANDLE& file, DWORD& fileSize, /*DWORD& readBytes*/ LPVOID& metadata, string& title, string& artist, string& album);
void writeMetadata(HANDLE& file, DWORD& fileSize, /*DWORD& readBytes*/ LPVOID& metadata, string& title, string& artist, string& album);
//File processsing
void openFile(HANDLE& file);
void getFileSize(HANDLE& file, DWORD& fileSize);
void allocateMemory(/*HANDLE& file,*/ DWORD& fileSize, LPVOID& data);
void readtoMemory(HANDLE& file, DWORD& fileSize, LPVOID& data /*DWORD& bytes*/);
unique_ptr<char[]> readFileData(HANDLE& file, DWORD& fileSize, LPVOID& data);
bool checkTagExists(const unique_ptr<char[]>& fileD, DWORD& fileSize);


string getTitle(const unique_ptr<char[]>& fileD, DWORD fileSize);
string getArtist(const unique_ptr<char[]>& fileD, DWORD fileSize);
string getAlbum(const unique_ptr<char[]>& fileD, DWORD fileSize);

int main()
{

    HANDLE mp3file;
    DWORD fileSize;
    /*DWORD readBytes;*/
    LPVOID metadata;
    string title;
    string artist;
    string album;


    menu(mp3file, fileSize, /*readBytes*/ metadata, title, artist, album);

}

void menu(HANDLE& file, DWORD& fileSize, /*DWORD& bytes*/ LPVOID& data,  string& title, string& artist, string& album)
{
    int choice;

    cout<<"1. Display metadata"<<endl;
    cout<<"2. Change metadata"<<endl;
    cin>>choice;
    switch(choice){
case 1:
    displayMetadata(file, fileSize, /*bytes*/ data, title, artist, album );
    break;
case 2:
    writeMetadata(file, fileSize, /*bytes*/ data, title, artist, album);
    break;
default:
    break;
    }

}


void displayMetadata(HANDLE& file, DWORD& fileSize, /*DWORD& bytes*/ LPVOID& metadata, string& title, string& artist, string& album){

        openFile(file);
        getFileSize(file, fileSize);
        allocateMemory(/*file,*/ fileSize, metadata);
        readtoMemory(file, fileSize, metadata /*bytes*/);
        unique_ptr<char[]> fileData = readFileData(file, fileSize, metadata);

        	if (!checkTagExists(fileData, fileSize)) {
        cout << "No tag found!!!!"<< endl;
		return;
	}
    	title = getTitle(fileData, fileSize);
        artist = getArtist(fileData, fileSize);
        album = getAlbum(fileData, fileSize);
        cout << "Title: " << title << endl;
        cout << "Artist: " << artist << endl;
    	cout << "Album: " << album << endl;

};

void openFile(HANDLE& file)
{
	file = CreateFile("In_Pure_Form_01.mp3", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == INVALID_HANDLE_VALUE)
	{
		printf("Failed to open file\n");
	}
}
void getFileSize(HANDLE& file, DWORD& fileSize)
{
	fileSize = GetFileSize(file, NULL);
	if (fileSize == INVALID_FILE_SIZE) {
		printf("Failed to get file size\n");
		CloseHandle(file);
	}
}
void allocateMemory(/*HANDLE& file,*/ DWORD& fileSize, LPVOID& data)
{
	data = VirtualAlloc(NULL, fileSize, MEM_RESERVE | MEM_COMMIT | MEM_TOP_DOWN, PAGE_READWRITE);
	if (data == NULL) {
		printf("Failed to allocate memory");
		//CloseHandle(file);
	}
}
void readtoMemory(HANDLE& file, DWORD& fileSize, LPVOID& data /*DWORD& bytes*/)
{
	if (!ReadFile(file, data, fileSize, /*&bytes*/ NULL, NULL)) {
		printf("Failed to read file\n");
		VirtualFree(data, 0, MEM_RELEASE);
		CloseHandle(file);
	}
}
unique_ptr<char[]> readFileData(HANDLE& file, DWORD& fileSize, LPVOID& metadata) {
	unique_ptr<char[]> fileData(new char[fileSize + 1]);
	memcpy(fileData.get(), metadata, fileSize);
	return fileData;
}
bool checkTagExists(const unique_ptr<char[]>& fileD, DWORD& fileSize) {
	return string(fileD.get() + fileSize - 128, 3) == "TAG";

}
string getTitle(const unique_ptr<char[]>& fileD, DWORD fileSize) {
	return string(fileD.get() + fileSize - 125, fileD.get() + fileSize - 95);
}
string getArtist(const unique_ptr<char[]>& fileD, DWORD fileSize) {
	return string(fileD.get() + fileSize - 95, fileD.get() + fileSize - 65);
}
string getAlbum(const unique_ptr<char[]>& fileD, DWORD fileSize) {
	return string(fileD.get() + fileSize - 65, fileD.get() + fileSize - 35);//subtracting string where album info is
}
void writeMetadata(HANDLE& file, DWORD& fileSize, /*DWORD& bytes*/ LPVOID& data, string& title, string& artist, string& album)
{
    cout << "Enter new title: ";
    cin.ignore();
	getline(cin, title);
	cout << "Enter new artist name: ";
	getline(cin, artist);
    cout << "Enter new album name: ";
	getline(cin, album);

    openFile(file);
    getFileSize(file, fileSize);
    allocateMemory(/*file,*/ fileSize, data);
    readtoMemory(file, fileSize, data /*bytes*/);

    CloseHandle(file);

    title.resize(30, ' ');
	artist.resize(30, ' ');
    album.resize(30, ' ');

    memcpy((char*)data + fileSize - 125, title.c_str(), 30);
	memcpy((char*)data + fileSize - 95, artist.c_str(), 30);
    memcpy((char*)data + fileSize - 65, album.c_str(), 30);

	file = CreateFile("In_Pure_Form_01.mp3", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == INVALID_HANDLE_VALUE)
	{
		printf("Failed to open file\n");
	}

	if (!WriteFile(file, data, fileSize, /*&bytes*/NULL, NULL))
	{
		printf("Failed to write the updated metadata to the file\n");
	}
	else
	{
		printf("Success!");
	}

}


