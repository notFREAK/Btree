#include <iostream>
#include <fstream>
#define pointer uint64_t
#define keytype int 
using namespace std;
#include "File.h"
#include "Btree.h"
#include "Node.h"

int main() {
    Btree t(3, "C:/Users/video/source/repos/notFREAK/Btree/Btree/Index.txt");
    t.Insert(10);
    t.Insert(20);
    t.Insert(5);
    t.Insert(6);
    t.Insert(12);
    t.Insert(30);
    t.Insert(7);
    t.Insert(17);

    cout << "Traversal of the constructed tree is ";
    t.Traverse();

    int k = 6;
    (t.Search(k) != NULL) ? cout << "\nPresent" : cout << "\nNot Present";

    k = 15;
    (t.Search(k) != NULL) ? cout << "\nPresent" : cout << "\nNot Present";

    return 0;
}