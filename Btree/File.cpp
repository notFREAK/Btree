#include "File.h"

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

bool File::WritePtr(pointer ptr, pointer key)
{
	file.seekg(ptr);
	file << key;
	return false;
}

pointer File::ReadPtr(pointer ptr)
{
	file.seekg(ptr);
	unsigned long long int tmp;
	file >> tmp;
	return tmp;
}

bool File::WriteKey(pointer ptr, keytype key)
{
	file.seekg(ptr);
	file << key;
	return false;
}

keytype File::ReadKey(pointer ptr)
{
	file.seekg(ptr);
	keytype tmp;
	file >> tmp;
	return tmp;
}
