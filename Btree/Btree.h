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
	void Insert(int);
	void Delete(int);
	void Search(int);
};