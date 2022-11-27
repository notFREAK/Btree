#pragma once

class Node {
private:
	int* keys;
	Node** childrens;
	int keys_count, childrens_count;
	Node* father;
	Node();
	Node(int);
	Node(int, Node*);
	~Node();
	friend class Btree;
};