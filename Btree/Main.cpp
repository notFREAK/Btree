#include "Header.h"


int main() {
    Btree t(3, "C:/Users/video/source/repos/notFREAK/Btree/Btree/Index.txt");
    for (int i = 1; i <= 3; i++) {
        t.Insert(i);
    }

    cout << "Traversal of the constructed tree is ";
    t.Traverse();
    
    return 0;
}