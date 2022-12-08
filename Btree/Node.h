#pragma once
#include "Header.h"

class File;
class Node {
private:
	File* IndexFile;
	keytype* keys;
	pointer* childrens;
	pointer thisobj;
	int keys_count, order;
	bool leaf;
	friend class File;
	friend class Btree;
	Node(int, bool);
	Node(int, bool, File*);
	void Print();
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
public:
	~Node();
};
