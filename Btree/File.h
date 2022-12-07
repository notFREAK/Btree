#pragma once
#include "Node.h"


class File {
private:
    fstream file;
	string filepath;
	pointer str;
public:
	File(string);
	~File();
	
};