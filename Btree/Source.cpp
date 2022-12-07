#include "Btree.h"
#include "File.h"

int main() {
    Btree t(3);
    t.Insert(10);
    t.Insert(20);
    t.Insert(5);
    t.Insert(6);
    t.Insert(12);
    t.Insert(30);
    t.Insert(7);
    t.Insert(17);
    return 0;
}