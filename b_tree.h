#ifndef B_TREE_H
#define B_TREE_H

#include "node.h"

class BTree {
	private:
		Node* root;
		int min;
	public:
		BTree(int _min) {
			root = NULL;
			min = _min;
		}

		void traverse() {
			if (root != NULL)
				root->traverse();
		}

		Node* search(int k) {
			return (root == NULL) ? NULL : root->search(k);
		}

		void insert(int k);
};

#endif
