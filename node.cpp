#include <iostream>
#include "node.h"

using namespace std;

Node::Node(int _min, bool _leaf) {
	min = _min;
	leaf = _leaf;
	keys = new int[2 * min - 1];
	child = new Node *[2 * min];
	total_keys = 0;
}

void Node::insert_non_full(int _key) {
	int i = total_keys - 1;

	if (leaf == true) {
		while (i >= 0 && keys[i] > _key) {
			keys[i + 1] = keys[i];
			i--;
		}

		keys[i + 1] = _key;
		total_keys += 1;
	}
	else {
		while (i >= 0 && keys[i] > _key)
			i--;

		if (child[i+1]->total_keys == 2 * min - 1) {
			split_child(i + 1, child[i + 1]);

			if (keys[i + 1] < _key)
				i++;
		}

		child[i + 1]->insert_non_full(_key);
	}
}

void Node::split_child(int i, Node* y) {
	Node* z = new Node(y->min, y->leaf);
	z->total_keys = min - 1;

	for (int j = 0; j < min - 1; j++)
		z->keys[j] = y->keys[j + min];

	if (y->leaf == false) {
		for (int j = 0; j < min; j++)
			z->child[j] = y->child[j + min];
	}

	y->total_keys = min - 1;

	for (int j = total_keys; j >= i + 1; j--)
		child[j + 1] = child[j];

	child[i + 1] = z;

	for (int j = total_keys - 1; j >= i; j--)
		keys[j + 1] = keys[j];

	keys[i] = y->keys[min - 1];

	total_keys += 1;
}

void Node::traverse() {
	int i;

	for (i = 0; i < total_keys; i++) {
		if (leaf == false)
			child[i]->traverse();

		cout << " " << keys[i];
	}

	if (leaf == false)
		child[i]->traverse();
}

void Node::remove(int _key) {
	int idx = find_index(_key);

	if (idx < total_keys && keys[idx] == _key) {
		if (leaf)
			remove_from_leaf(idx);
		else
			remove_from_nonleaf(idx);
	}
	else {
		bool flag = ((idx == total_keys) ? true : false);

		if (child[idx]->total_keys < min)
			fill(idx);

		if (flag && idx > total_keys)
			child[idx - 1]->remove(_key);
		else
			child[idx]->remove(_key);
	}
}

void Node::remove_from_leaf(int _idx) {
	for (int i = _idx + 1; i < total_keys; ++i)
		keys[i - 1] = keys[i];

	total_keys--;
}

void Node::remove_from_nonleaf(int _idx) {
	int key = keys[_idx];

	if (child[_idx]->total_keys >= min) {
		int pred = get_pred(_idx);
		keys[_idx] = pred;
		child[_idx]->remove(pred);
	}
	else if (child[_idx + 1]->total_keys >= min) {
		int succ = get_succ(_idx);
		keys[_idx] = succ;
		child[_idx + 1]->remove(succ);
	}
	else {
		merge(_idx);
		child[_idx]->remove(key);
	}
}



void Node::fill(int _idx) {
	if (_idx != 0 && child[_idx - 1]->total_keys >= min)
		borrow_from_prev(_idx);
	else if (_idx != total_keys && child[_idx + 1]->total_keys >= min)
		borrow_from_next(_idx);
	else
		if (_idx != total_keys)
			merge(_idx);
		else
			merge(_idx - 1);
}

void Node::borrow_from_prev(int _idx) {
	Node* _child = child[_idx];
	Node* sibling = child[_idx - 1];

	for (int i = _child->total_keys - 1; i >= 0; --i)
		_child->keys[i + 1] = _child->keys[i];

	if (!_child->leaf) {
		for (int i = _child->total_keys; i >= 0; --i)
			_child->child[i + 1] = _child->child[i];
	}

	_child->keys[0] = keys[_idx - 1];

	if (!_child->leaf)
		_child->child[0] = sibling->child[sibling->total_keys];

	keys[_idx - 1] = sibling->keys[sibling->total_keys - 1];

	_child->total_keys += 1;
	sibling->total_keys -= 1;
}

void Node::borrow_from_next(int _idx) {
	Node* _child = child[_idx];
	Node* sibling = child[_idx + 1];

	_child->keys[_child->total_keys] = keys[_idx];

	if (!_child->leaf)
		_child->child[_child->total_keys + 1] = sibling->child[0];

	keys[_idx] = sibling->keys[0];

	for (int i = 1; i < sibling->total_keys; ++i)
		sibling->keys[i - 1] = sibling->keys[i];

	if (!sibling->leaf) {
		for (int i = 1; i <= sibling->total_keys; ++i)
			sibling->child[i - 1] = sibling->child[i];
	}

	_child->total_keys += 1;
	sibling->total_keys -= 1;
}

void Node::merge(int _idx) {
	Node* _child = child[_idx];
	Node* sibling = child[_idx + 1];

	_child->keys[min - 1] = keys[_idx];

	for (int i = 0; i < sibling->total_keys; ++i)
		_child->keys[i + min] = sibling->keys[i];

	if (!_child->leaf) {
		for (int i = 0; i <= sibling->total_keys; ++i)
			_child->child[i + min] = sibling->child[i];
	}

	for (int i = _idx + 1; i < total_keys; ++i)
		keys[i - 1] = keys[i];

	for (int i = _idx + 2; i <= total_keys; ++i)
		child[i - 1] = child[i];

	_child->total_keys += sibling->total_keys + 1;
	total_keys--;

	delete(sibling);
}

Node* Node::search(int _key) {
	int i = 0;

	while (i < total_keys && _key > keys[i])
		i++;

	if (keys[i] == _key)
		return this;

	if (leaf == true)
		return NULL;

	return child[i]->search(_key);
}

int Node::find_index(int _key) {
	int idx = 0;

	while (idx < total_keys && keys[idx] < _key)
		++idx;

	return idx;
}

int Node::get_pred(int _idx) {
	Node* current = child[_idx];

	while (!current->leaf)
		current = current->child[current->total_keys];

	return current->keys[current->total_keys - 1];
}

int Node::get_succ(int _idx) {
	Node* current = child[_idx + 1];

	while (!current->leaf)
		current = current->child[0];

	return current->keys[0];
}