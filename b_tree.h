#ifndef B_TREE_H
#define B_TREE_H

#include "node.h"

class BTree {
private:
	Node* root;
	int order;

public:
	BTree();

	void set_order(int);

	void insert(int);
	bool remove(int);
	void print();
	void level(int);

	Node* search(int);
};

#endif