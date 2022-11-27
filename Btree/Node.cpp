#include "Node.h"
#include "Btree.h"

Node::Node(int order, Node* father)
{
	try {
		keys = new int[order];
		childrens = new Node * [order + 1];
	}
	catch (...) {
		 cout << "Error memory allocation" << endl;
	}
	this->order = order;
	keys_count = 0;
	childrens_count = 0;
	this->father = father;
}

Node::Node(int order) : Node::Node(order, nullptr)
{
}

Node::Node()
{
	keys = nullptr;
	childrens = nullptr;
	father = nullptr;
	keys_count = 0; 
	childrens_count = 0;
	order = 0;
}


Node::~Node()
{
	delete[] keys;
	delete[] childrens;
}

void Node::childrens_add(int)
{

}

void Node::key_add(int)
{

}

Node& Node::Search(int key) {
	int i = 0;
	for (; i < keys_count && keys[i] < key; i++);
	if (keys[i] == key) {
		return *this;
	}
	else {
		try {
			childrens[i]->Search(key);
		}
		catch (...) {
			cout << "Error node searth" << endl;
		}
	}
}
