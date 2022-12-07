#pragma once
#include "Header.h"

class Node;
class File {
private:
	fstream file;
	string filepath;
	int order;
public:
	File();
	File(int, string);
	~File();
	void open(string);
	Node* writeNode(pointer, ios_base::seekdir, Node*);
	Node* readNode(pointer);
};