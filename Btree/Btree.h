#pragma once

#include <iostream>
#include "Node.h"

using namespace std;

class Btree {
private:
	Node* head;
public:
	Btree();
	~Btree();
	void Insert(int);
	void Delete(int);
	void Search(int)
	//конструктор
	//деструктор
	//добавление
	//удаление
	//поиск
};