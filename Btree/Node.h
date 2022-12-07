#pragma once
#include <fstream>
#include <iostream>
#include "Btree.h"

using namespace std;
class File;

class Node {
	(File*)FileIndex;
	keytype* keys;
	pointer* childrens;
	pointer thisobj;
	int keys_count, order;
	bool leaf;
	Node(int);
	void add_key(int, int);
	void add_children(pointer, int);
	friend class Btree;
	friend class File;
	void Traverse();
	void Insert(int);
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