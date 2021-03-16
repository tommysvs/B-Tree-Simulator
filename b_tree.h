#ifndef B_TREE_H
#define B_TREE_H

#include "node.h"

class BTree {
	private:
		Node* root;
		int min;

	public:
		BTree();

		void set_min(int);
		
		void insert(int);
		void delete_(int);
		void traverse();

		Node* search(int);
};

#endif
