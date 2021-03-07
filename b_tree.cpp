#include <iostream>
#include "b_tree.h"
#include "node.h"

void BTree::insert(int k) {
	if (root == NULL) {
		root = new Node(min, true);
		root->keys[0] = k;
		root->n = 1;
	}
	else {
		if (root->n == 2 * min - 1) {
			Node* s = new Node(min, false);
			s->child[0] = root;
			s->splitChild(0, root);

			int i = 0;
			
			if (s->keys[0] < k)
				i++;

			s->child[i]->insertNonFull(k);
			root = s;
		}
		else {
			root->insertNonFull(k);
		}
	}
}