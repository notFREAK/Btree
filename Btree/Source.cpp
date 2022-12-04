#include "Btree.h"

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
    t.Traverse();
    int k = 6;
    (t.Search(k) != NULL) ? cout << "\nPresent" : cout << "\nNot Present";
    k = 15;
    (t.Search(k) != NULL) ? cout << "\nPresent" : cout << "\nNot Present";
}