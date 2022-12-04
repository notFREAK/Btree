#include "Btree.h"

Btree::Btree(int order)
{
	this->order = order;
	head = nullptr;
}

Btree::~Btree()
{
	delete head;
}

void Btree::Insert(int key)
{
	
}

void Btree::Delete(int key)
{
}

void Btree::Search(int key)
{
}
