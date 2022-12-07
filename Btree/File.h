#pragma once
#include "Node.h"

class Btree;
class Node;
using namespace std;

class File {
protected:
	int order;
	fstream file;
	string filepath;
	pointer str;
	streamsize size;
	friend class Node;
public:
	File();
	File(string);
	~File();
	void open(string);
	Node* WriteNode(pointer ptr, ios_base::seekdir sek, Node* node);
	Node* ReadNode(pointer ptr);
};