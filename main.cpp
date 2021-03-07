#include <iostream>
#include <conio.h>
#include "node.h"
#include "b_tree.h"

using namespace std;

int main() {
    int min, key;

    cout << "B-TREE SIMULATOR\n\n";

    cout << "Insert order: ";
    cin >> min;
    BTree t(min);

    cout << endl;
    do {
        cout << "Insert key: ";
        cin >> key;
        t.insert(key);
    } while (key != -1);

    cout << "\nTraversal of the constucted tree is: ";
    t.traverse();
            
    cout << "\n\nEnter key to search: ";
    cin >> key;

    (t.search(key) != NULL) ? cout << "\nPresent" : cout << "\nNot Present";

    _getch();
}