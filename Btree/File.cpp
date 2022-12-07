#include "File.h"

File::File() {
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

