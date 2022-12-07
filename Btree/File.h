#pragma once
#include <iostream>
#include <fstream>

using namespace std;

#define pointer streampos 
#define keytype int 

class File {
private:
    fstream file;
	string filepath;
	pointer str;
public:
	File(string);
	~File();
	bool WritePtr(pointer, pointer);
	pointer ReadPtr(pointer);
	bool WriteKey(pointer, keytype);
	keytype ReadKey(pointer);
};