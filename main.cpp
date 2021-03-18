#include <iostream>
#include <conio.h>
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

    do {
        system("cls");
        cout << "B-TREE SIMULATOR\n\n";
        cout << "1. Insertion" << endl;
        cout << "2. Searching" << endl;
        cout << "3. Deletion" << endl;
        cout << "4. Exit" << endl;
        cout << "Option: ";
        cin >> option;

        switch (option) {
        case 1:
            system("cls");
            cout << "INSERTION\n\n";

            cout << "Insert order: ";
            cin >> min;

            tree.set_min(min);

            cout << endl;
            do {
                cout << "Insert key: ";
                cin >> key;
                tree.insert(key);
            } while (key != -1);

            cout << "\nTraversal of the constucted tree is: ";
            tree.print();

            //window.create_window();

            _getch();

            break;
        case 2:
            system("cls");
            cout << "SEARCHING\n\n";

            cout << "Enter key to search: ";
            cin >> key;

            (tree.search(key) != NULL) ? cout << "\nPresent" : cout << "\nNot Present";

            _getch();

            break;
        case 3:
            system("cls");
            cout << "DELETION\n\n";

            cout << "Enter key to delete: ";
            cin >> key;

            if (tree.remove(key)) {
                //window.create_window();
                cout << "Key deleted.";

                cout << "\nTraversal of the constucted tree is: ";
                tree.print();
            }
            else
                cout << "Key not found.";

            _getch();

            break;
        case 4:
            exit(0);
            break;
        default:
            cout << "Option not valid.";
            _getch();
            break;
        }
    } while (option != 4);
        
    return 0;
}