#include "Header.h"


int main() {
    Btree t(3, "C:/Users/video/source/repos/notFREAK/Btree/Btree/Index.txt");
    srand(time(0));
    for (int i = 1; i <= 20; i++) {
        t.Insert(i);
    }
    t.Traverse();
    t.Delete(3);
    t.Traverse();
    for (int i = 1; i <= 20; i++) {
        t.Insert(i);
    }
    t.Traverse();
    t.Delete(9);
    t.Traverse();
    /*for (int i = 1; i <= 51; i++) {
        cout << "delete " << i << ':';
        t.Delete(i);
        t.Traverse();
        t.Insert(i);
    }*/
    return 0;
}