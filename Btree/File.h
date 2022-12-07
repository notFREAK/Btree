#pragma once
#include "Node.h"


class File {
private:
    fstream file;
	string filepath;
	pointer str;
public:
	File();
	~File();
	void open(string filepath);
	
};