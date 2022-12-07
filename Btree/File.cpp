#include "Node.h"

File::File()
{
}

File::File(string filepath)
{
	this->filepath = filepath;
	try {
		file.open(filepath, ios::in | ios::out | ios::binary);
	}
	catch( ios_base::failure & e) {
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

Node* File::WriteNode(pointer ptr, ios_base::seekdir sek, Node* node)
{
	file.seekg(ptr, sek);
	node->thisobj = file.tellg();
	int i = 0;
	for (;i < node->keys_count; i++) {
		file.write((char*)&node->keys[i], sizeof(keytype));
		file.write((char*)&node->childrens[i], sizeof(pointer));
	}
	file.write((char*)&node->childrens[node->keys_count], sizeof(pointer));
	for (;i < node->order; i++) {
		file.write((char*)&node->keys[i], sizeof(keytype));
		file.write((char*)&node->childrens[i], sizeof(pointer));
	}
	return node;
}

Node* File::ReadNode(pointer ptr)
{
	file.seekg(ptr, ios::beg);
	Node* tmp = new Node(order);
	for (int i = 0; i < order; i++) {
		file.read((char*)&tmp->childrens[i], sizeof(pointer));
		file.read((char*)&tmp->keys[i], sizeof(pointer));
	}
	file.read((char*)&tmp->childrens[order], sizeof(pointer));
	return tmp;
}


//pointer File::WritePtr(pointer ptr, pointer key)
//{
//	file.seekp(ptr);
//	file.write((char*)&key, sizeof(key));
//	return ptr;
//}
//
//pointer File::ReadPtr(pointer ptr)
//{
//	file.seekg(ptr);
//	unsigned long long int tmp;
//	file.read((char*)&tmp, sizeof(pointer));
//	return tmp;
//}
//
//pointer File::WriteKey(pointer ptr, keytype key)
//{
//	file.seekg(ptr);
//	file.write((char*)&key, sizeof(key));
//	return ptr;
//}
//
//keytype File::ReadKey(pointer ptr)
//{
//	file.seekg(ptr);
//	keytype tmp;
//	file.read((char*)&tmp, sizeof(keytype));
//	return tmp;
//}