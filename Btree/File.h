#pragma once
#include "Header.h"

class Node;
class File {
private:
	fstream* file;
	string filepath;
	int order;
public:
	File();
	File(int, string);
	~File();
	void open(string);
	File& operator=(File&);
	pointer writePtr(pointer, pointer);
	Node* writeNode(pointer, ios_base::seekdir, Node*);
	void NULLNode(pointer ptr, ios_base::seekdir dir, int order);
	Node* readNode(pointer);
};