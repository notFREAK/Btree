#pragma once

#include <iostream>
#include "Node.h"

using namespace std;

class Btree {
private:
	int order;
	Node* head;
public:
	Btree(int);
	~Btree();
	void Traverse();
	void Insert(int);
	void Delete(int);
	Node* Search(int);
};