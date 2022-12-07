#pragma once
#define pointer uint64_t
#define keytype int 
#include "File.h"

class Btree {
protected:
public:
	File* FileIndex;
	friend class File;
	friend class Node;
	pointer head;
	int order;
	Btree(int);
	Btree(string);
	~Btree();
	void Traverse();
	void Insert(int);
	void Delete(int);
	//	Node* Search(int);
};