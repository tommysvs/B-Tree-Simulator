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
		bool remove(int);
		void print();

		Node* search(int);
};

#endif
