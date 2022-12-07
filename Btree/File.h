#pragma once

class Node;
class Btree;

class File {
private:
    fstream file;
	string filepath;
	int order;
public:
	File(int, string);
	~File();
	void open(string);
	Node* writeNode(pointer, ios_base::seekdir, Node*);
	Node* readNode(pointer);
};