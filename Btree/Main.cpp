#include "Header.h"


int main() {
    Btree t(1000, "C:/Users/video/source/repos/notFREAK/Btree/Btree/Index.txt");
    srand(time(0));
    for (int i = 1000; i >= 1; i--) {
        t.Insert(rand());
    }

    cout << "Traversal of the constructed tree is ";
    t.Traverse();
    
    return 0;
}