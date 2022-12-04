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
	this->leaf = leaf;
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

void Node::Split(int i, Node* root)
{
	Node* newChildren = new Node(root->order, root->leaf);
	newChildren->keys_count = order - 1;
	for (int j = 0; j < order - 1; j++)
		newChildren->keys[j] = root->keys[j + order];
	if (root->leaf == false)
	{
		for (int j = 0; j < order; j++)
			newChildren->childrens[j] = root->childrens[j + order];
	}
	root->keys_count = order - 1;
	for (int j = keys_count; j >= i + 1; j--)
		childrens[j + 1] = childrens[j];
	childrens[i + 1] = newChildren;
	for (int j = keys_count - 1; j >= i; j--)
		keys[j + 1] = keys[j];
	keys[i] = root->keys[order - 1];
	keys_count = keys_count + 1;
}

void Node::Insert(int k)
{
	int i = keys_count - 1;

	if (leaf == true)
	{
		for (;i >= 0 && keys[i] > k; i--)
			keys[i + 1] = keys[i];
		keys[i + 1] = k;
		keys_count = keys_count+ 1;
	}
	else
	{
		for (; i >= 0 && keys[i] > k; i--);
		if (childrens[i + 1]->keys_count == 2 * order - 1)
		{
			Split(i + 1, childrens[i + 1]);
			if (keys[i + 1] < k)
				i++;
		}
		childrens[i + 1]->Insert(k);
	}
}