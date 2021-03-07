#include <iostream>
#include "node.h"

Node::Node(int min1, bool leaf1) {
	min = min1;
	leaf = leaf1;
	keys = new int[2 * min - 1];
	child = new Node *[2 * min];
	n = 0;
}

void Node::insertNonFull(int k) {
	int i = n - 1;

	if (leaf == true) {
		while (i >= 0 && keys[i] > k) {
			keys[i + 1] = keys[i];
			i--;
		}

		keys[i + 1] = k;
		n += 1;
	}
	else {
		while (i >= 0 && keys[i] > k)
			i--;

		if (child[i+1]->n == 2 * min - 1) {
			splitChild(i + 1, child[i + 1]);

			if (keys[i + 1] < k)
				i++;
		}

		child[i + 1]->insertNonFull(k);
	}
}

void Node::splitChild(int i, Node* y) {
	Node* z = new Node(y->min, y->leaf);
	z->n = min - 1;

	for (int j = 0; j < min - 1; j++)
		z->keys[j] = y->keys[j + min];

	if (y->leaf == false) {
		for (int j = 0; j < min; j++)
			z->child[j] = y->child[j + min];
	}

	y->n = min - 1;

	for (int j = n; j >= i + 1; j--)
		child[j + 1] = child[j];

	child[i + 1] = z;

	for (int j = n - 1; j >= i; j--)
		keys[j + 1] = keys[j];

	keys[i] = y->keys[min - 1];

	n += 1;
}

void Node::traverse() {
	int i;

	for (i = 0; i < n; i++) {
		if (leaf == false)
			child[i]->traverse();

		std::cout << " " << keys[i];
	}

	if (leaf == false)
		child[i]->traverse();
}

Node *Node::search(int k) {
	int i = 0;

	while (i < n && k > keys[i])
		i++;

	if (keys[i] == k)
		return this;

	if (leaf == true)
		return NULL;

	return child[i]->search(k);
}