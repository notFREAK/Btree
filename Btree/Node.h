#pragma once

class Node {
private:
	int* keys;
	Node** childrens;
	int keys_count, childrens_count, order;
	Node* father;
	Node();
	Node(int);
	Node(int, Node*);
	~Node();
	friend class Btree;
	Node& Search(int);
	void childrens_add(int);
	void key_add(int);
};