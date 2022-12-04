#pragma once

class Node {
private:
	int* keys;
	Node** childrens;
	int keys_count, order;
	bool leaf;
	Node(int, bool);
	~Node();
	friend class Btree;
	void Traverse();
	Node* Search(int);
	void Split(int, Node*);
	void Insert(int);
};