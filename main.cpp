#include <iostream>
#include "SDL.h"
#include "window.h"
#include "graphics.h"
#include "b_tree.h"
#include "node.h"

using namespace std;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);

    BTree tree;
    Window window;

    int min, key, option;

    //cout << "B-TREE SIMULATOR\n\n";
    //cout << "1. Insertion" << endl;
    //cout << "2. Searching" << endl;
    //cout << "3. Deletion" << endl;
    //cout << "4. Exit" << endl;
    //cout << "Option: ";
    //cin >> option;

    //switch (option) {
    //    case 1:
    //        system("cls");
    //        cout << "INSERTION\n\n";

    //        cout << "Insert order: ";
    //        cin >> min;

    //        tree.set_min(min);

    //        cout << endl;
    //        do {
    //            cout << "Insert key: ";
    //            cin >> key;
    //            tree.insert(key);
    //        } while (key != -1);

    //        cout << "\nTraversal of the constucted tree is: ";
    //        tree.traverse();
    //        break;
    //    case 2:
    //        system("cls");
    //        cout << "SEARCHING\n\n";

    //        cout << "\n\nEnter key to search: ";
    //        cin >> key;

    //        (tree.search(key) != NULL) ? cout << "\nPresent" : cout << "\nNot Present";
    //        break;
    //    case 3:
    //        system("cls");
    //        cout << "DELETION\n\n";

    //        cout << "\n\nEnter key to delete: ";
    //        cin >> key;

    //        tree.delete_(key);

    //        break;
    //    case 4:
    //        exit(0);
    //        break;
    //    default:
    //        cout << "Option not valid.";
    //        break;
    //}
    //    
    window.create_window();

    return 0;
}