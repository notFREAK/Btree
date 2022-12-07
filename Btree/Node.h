#pragma once
#include <iostream>
#include <fstream>
using namespace std;

#define pointer streampos 
#define keytype int 
#include "Btree.h"


class Node {
private:
	int* keys;
	Node** childrens;
	int keys_count, order;
	bool leaf;
	Node(int, bool);
	friend class Btree;
	void Traverse();
	Node* Search(int);
	void Split(int, Node*);
	void Insert(int);
	int FindKey(int);
	int getPred(int);
	int getSucc(int);
	void Fill(int);
	void BorrowFromPrev(int);
	void BorrowFromNext(int);
	void Merge(int);
	void Delete(int);
};