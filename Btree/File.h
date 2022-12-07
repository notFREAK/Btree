#pragma once

#include <fstream>

using namespace std;

#define pointer uint16_t 
#define key uint16_t 

class File {
private:
	string filename;
	pointer str;
public:
	bool WritePtr(pointer, pointer);
	pointer ReadPtr(pointer);
	bool WriteKey(pointer, key);
	key ReadKey(pointer);
};