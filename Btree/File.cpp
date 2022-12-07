#include "File.h"

File::File()
{
}

File::File(int order, string filepath) {
	this->order = order;
	this->filepath = filepath;
	try {
		file.open(filepath, ios::in | ios::out | ios::binary);
	}
	catch (ios_base::failure& e) {
		cerr << e.what() << endl;
		exit(1);
	}
}

File::~File()
{
	file.close();
}

void File::open(string filepath)
{
	this->filepath = filepath;
	try {
		file.open(filepath, ios::in | ios::out | ios::binary);
	}
	catch (ios_base::failure& e) {
		cerr << e.what() << endl;
		exit(1);
	}
}

Node* File::writeNode(pointer ptr, ios_base::seekdir dir, Node* node)
{
	file.seekp(ptr, dir);
	node->thisobj = file.tellp();
	int i = 0;
	for (; i < node->keys_count; i++)
	{
		file.write((char*)node->childrens[i], sizeof(pointer));
		file.write((char*)node->keys[i], sizeof(keytype));
	}
	file.write((char*)node->childrens[i], sizeof(pointer));
	for (; i < node->order; i++)
	{
		file.write(NULL, sizeof(pointer));
		file.write(NULL, sizeof(keytype));
	}
	return node;
}

Node* File::readNode(pointer ptr)
{
	file.seekg(ptr, ios::beg);
	Node* node = new Node(this->order, true);
	node->thisobj = file.tellp();
	for (int i = 0; i < node->order; i++)
	{
		file.read((char*)node->childrens[i], sizeof(pointer));
		file.read((char*)node->keys[i], sizeof(keytype));
	}
	file.read((char*)node->childrens[order], sizeof(pointer));
	for (int i = 0; i <= order; i++)
	{
		if (node->childrens[i] == NULL) {
			node->keys_count = i;
		}
		else
		{
			node->leaf = false;
		}
	}
	return node;
}



