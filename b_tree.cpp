#include <iostream>
#include "b_tree.h"
#include "node.h"

BTree::BTree() : root(nullptr), min(0) { }

void BTree::set_min(int _min) {
	min = _min;
}

void BTree::insert(int _key) {
	if (root == nullptr) {
		root = new Node(min, true);
		root->keys[0] = _key;
		root->n = 1;
	}
	else {
		if (root->n == 2 * min - 1) {
			Node* s = new Node(min, false);
			s->child[0] = root;
			s->split_child(0, root);

			int i = 0;
			
			if (s->keys[0] < _key)
				i++;

			s->child[i]->insert_non_full(_key);
			root = s;
		}
		else {
			root->insert_non_full(_key);
		}
	}
}

void BTree::delete_(int _key) {

}

void BTree::traverse() {
	if (root != nullptr)
		root->traverse();
}

Node* BTree::search(int _key) {
	return (root == nullptr) ? nullptr : root->search(_key);
}