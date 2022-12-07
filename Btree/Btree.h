#pragma once
#include "File.h"

using namespace std;

class Btree {
private:
	int order;
	pointer* head;
public:
	Btree(int);
	~Btree();
	void Traverse();
	void Insert(int);
	void Delete(int);
	Node* Search(int);
};