#pragma once

class Btree;
class File;

class Node {
private:
	static File* IndexFile;
	keytype* keys;
	pointer* childrens;
	pointer thisobj;
	int keys_count, order;
	bool leaf;
	Node(int, bool);
	Node(int, bool, File*);
	friend class Btree;
	friend class File;
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