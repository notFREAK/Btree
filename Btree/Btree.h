#pragma once

#include <iostream>
#include "Node.h"

using namespace std;

class Btree {
private:
	int order;
	int heigth;
	Node* head;
public:
	Btree();
	Btree(int, int);
	~Btree();
	void Insert(int);
	void Delete(int);
	void Search(int);
};