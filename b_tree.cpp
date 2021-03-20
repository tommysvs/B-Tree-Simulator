#include <iostream>
#include "b_tree.h"
#include "node.h"

BTree::BTree() : root(nullptr), order(0) { }

void BTree::set_order(int _order) {
	order = _order;
}

void BTree::insert(int _key) {
	if (root == nullptr) {
		root = new Node(order, true);
		root->data[0] = _key;
		root->keys = 1;
	}
	else {
		if (root->keys == 2 * order - 1) {
			Node* s = new Node(order, false);
			s->child[0] = root;
			s->split_child(0, root);

			int i = 0;

			if (s->data[0] < _key)
				i++;

			s->child[i]->insert_non_full(_key);
			root = s;
		}
		else {
			root->insert_non_full(_key);
		}
	}
}

bool BTree::remove(int _key) {
	if (root != nullptr && search(_key))
		root->remove(_key);
	else
		return false;

	return true;
}

void BTree::print() {
	if (root != nullptr)
		root->traverse();
}

void BTree::level(int _level) {
	if (root != nullptr)
		root->level(root, _level);
}

Node* BTree::search(int _key) {
	return (root == nullptr) ? nullptr : root->search(_key);
}