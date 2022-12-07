#pragma once
#include "File.h"

using namespace std;
class Node;
class File;

class Btree {
private:
	int order;
	pointer* head;
	File* IndexFile;
public:
	Btree(int, string);
	~Btree();
	void Traverse();
	void Insert(int);
	void Delete(int);
	Node* Search(int);
};