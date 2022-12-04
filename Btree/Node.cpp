#include "Node.h"
#include "Btree.h"

Node::Node(int order, bool leaf)
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
}

Node::~Node()
{
	delete[] keys;
	delete[] childrens;
}

void Node::Traverse() {
	int i;
	for (i = 0; i < keys_count; i++)
	{
		if (leaf == false)
			childrens[i]->Traverse();
		cout << " " << keys[i];
	}
	if (leaf == false)
		childrens[i]->Traverse();
}

Node* Node::Search(int key) {
	int i = 0;
	for (; i < keys_count && keys[i] < key; i++);
	if (keys[i] == key) {
		return this;
	}
	else {
		try {
			return childrens[i]->Search(key);
		}
		catch (...) {
			cout << "Error node searth" << endl;
			return nullptr;
		}
	}
}
