#include "Btree.h"

Btree::Btree(int order, int heigth)
{
	this->order = order;
	this->heigth = heigth;
	head = new Node(order);
}

Btree::~Btree()
{
	delete head;
}

void Btree::Insert(int key)
{
	if (head->keys_count < order) {
		head->key_add(key);
	}
	else
	{

	}
}

void Btree::Delete(int key)
{
}

void Btree::Search(int key)
{
}
