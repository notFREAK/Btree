#include "File.h"

File::File()
{
}

File::File(int order, string filepath) {
	this->order = order;
	this->filepath = filepath;
	try {
		file = new fstream(filepath, ios::in | ios::out | ios::binary | ios::trunc);
	}
	catch (ios_base::failure& e) {
		cerr << e.what() << endl;
		exit(1);
	}
}

File::~File()
{
	
}

void File::open(string filepath)
{
	this->filepath = filepath;
	try {
		file->open(filepath, ios::in | ios::out | ios::binary);
	}
	catch (ios_base::failure& e) {
		cerr << e.what() << endl;
		exit(1);
	}
}

File& File::operator=(File& copy)
{
	file = copy.file;
	filepath = copy.filepath;
	order = copy.order;
	return copy;
}

pointer File::writePtr(pointer ptr, pointer key)
{
	file->seekp(ptr, ios::beg);
	file->write((char*)&key,sizeof(pointer));
	return key;
}

Node* File::writeNode(pointer ptr, ios_base::seekdir dir, Node* node)
{
	pointer a = file->tellp();
	file->seekp(ptr, dir);
	a = file->tellp();
	node->thisobj = file->tellp();
	int i = 0;
	for (; i < node->keys_count; i++)
	{
		try {
			file->write((char*)&node->childrens[i], sizeof(pointer));
			file->write((char*)&node->keys[i], sizeof(keytype));
		}
		catch (std::fstream::failure& writeErr) {
			std::cerr << "\n\nException occured when writing to a file\n"
				<< writeErr.what()
				<< std::endl;
			exit(1);
		}
	}
	file->write((char*)&node->childrens[i], sizeof(pointer));
	pointer tmp = NULL;
	for (; i < 2*node->order - 1; i++)
	{
		file->write((char*)&tmp, sizeof(pointer));
		file->write((char*)&tmp, sizeof(keytype));
	}
	return node;
}

void File::NULLNode(pointer ptr, ios_base::seekdir dir, int order)
{
	file->seekp(ptr, dir);
	pointer tmp = NULL;
	for (int i = 0; i < 2 * order - 1; i++)
	{
		file->write((char*)&tmp, sizeof(pointer));
		file->write((char*)&tmp, sizeof(keytype));
	}
	file->write((char*)&tmp, sizeof(pointer));
}

Node* File::readNode(pointer ptr)
{
	file->seekg(ptr, ios::beg);
	Node* node = new Node(this->order, true);
	node->thisobj = ptr;
	node->IndexFile = this;
	for (int i = 0; i < 2*node->order-1; i++)
	{
		file->read((char*)&node->childrens[i], sizeof(pointer));
		file->read((char*)&node->keys[i], sizeof(keytype));
	}
	file->read((char*)&node->childrens[2*order - 1], sizeof(pointer));
	for (int i = 0; i < 2*order - 1; i++)
	{
		if (node->keys[i] != 0) {
			node->keys_count = i + 1;
		}
		if (node->childrens[i] != 0)
		{
			node->leaf = false;
		}
	}
	return node;
}



