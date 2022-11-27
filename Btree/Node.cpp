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
}


Node::~Node()
{
	delete[] keys;
	delete[] childrens;
}

