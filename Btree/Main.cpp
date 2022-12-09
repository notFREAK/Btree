#include "Header.h"


int main() {
    Btree t(5, "C:/Users/video/source/repos/notFREAK/Btree/Btree/Index.txt");
    srand(time(0));
    for (int i = 1; i <= 51; i++) {
        t.Insert(i);
    }
    t.Traverse();
    t.Delete(2);
    t.Traverse();
    return 0;
}