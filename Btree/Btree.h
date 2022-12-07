#pragma once

class Node;
class File;

class Btree {
private:
	int order;
	pointer head;
	File* IndexFile;
	friend class Node;
public:
	Btree(int, string);
	~Btree();
	void Traverse();
	void Insert(int);
	void Delete(int);
	Node* Search(int);
};