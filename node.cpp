#include <iostream>
#include "node.h"

using namespace std;

Node::Node(int _order, bool _leaf) {
	order = _order;
	leaf = _leaf;
	data = new int[2 * order - 1];
	child = new Node * [2 * order];
	keys = 0;
}

void Node::insert_non_full(int _key) {
	int i = keys - 1;

	if (leaf == true) {
		while (i >= 0 && data[i] > _key) {
			data[i + 1] = data[i];
			i--;
		}

		data[i + 1] = _key;
		keys += 1;
	}
	else {
		while (i >= 0 && data[i] > _key)
			i--;

		if (child[i + 1]->keys == 2 * order - 1) {
			split_child(i + 1, child[i + 1]);

			if (data[i + 1] < _key)
				i++;
		}

		child[i + 1]->insert_non_full(_key);
	}
}

void Node::split_child(int i, Node* y) {
	Node* z = new Node(y->order, y->leaf);
	z->keys = order - 1;

	for (int j = 0; j < order - 1; j++)
		z->data[j] = y->data[j + order];

	if (y->leaf == false) {
		for (int j = 0; j < order; j++)
			z->child[j] = y->child[j + order];
	}

	y->keys = order - 1;

	for (int j = keys; j >= i + 1; j--)
		child[j + 1] = child[j];

	child[i + 1] = z;

	for (int j = keys - 1; j >= i; j--)
		data[j + 1] = data[j];

	data[i] = y->data[order - 1];

	keys += 1;
}

void Node::traverse() {
	int i;

	for (i = 0; i < keys; i++) {
		if (leaf == false)
			child[i]->traverse();

		cout << " " << data[i];
	}

	if (leaf == false)
		child[i]->traverse();
}

void Node::remove(int _key) {
	int idx = find_index(_key);

	if (idx < keys && data[idx] == _key) {
		if (leaf)
			remove_from_leaf(idx);
		else
			remove_from_nonleaf(idx);
	}
	else {
		bool flag = ((idx == keys) ? true : false);

		if (child[idx]->keys < order)
			fill(idx);

		if (flag && idx > keys)
			child[idx - 1]->remove(_key);
		else
			child[idx]->remove(_key);
	}
}

void Node::remove_from_leaf(int _idx) {
	for (int i = _idx + 1; i < keys; ++i)
		data[i - 1] = data[i];

	keys--;
}

void Node::remove_from_nonleaf(int _idx) {
	int key = data[_idx];

	if (child[_idx]->keys >= order) {
		int pred = get_pred(_idx);
		data[_idx] = pred;
		child[_idx]->remove(pred);
	}
	else if (child[_idx + 1]->keys >= order) {
		int succ = get_succ(_idx);
		data[_idx] = succ;
		child[_idx + 1]->remove(succ);
	}
	else {
		merge(_idx);
		child[_idx]->remove(key);
	}
}

void Node::fill(int _idx) {
	if (_idx != 0 && child[_idx - 1]->keys >= order)
		borrow_from_prev(_idx);
	else if (_idx != keys && child[_idx + 1]->keys >= order)
		borrow_from_next(_idx);
	else
		if (_idx != keys)
			merge(_idx);
		else
			merge(_idx - 1);
}

void Node::borrow_from_prev(int _idx) {
	Node* _child = child[_idx];
	Node* sibling = child[_idx - 1];

	for (int i = _child->keys - 1; i >= 0; --i)
		_child->data[i + 1] = _child->data[i];

	if (!_child->leaf) {
		for (int i = _child->keys; i >= 0; --i)
			_child->child[i + 1] = _child->child[i];
	}

	_child->data[0] = data[_idx - 1];

	if (!_child->leaf)
		_child->child[0] = sibling->child[sibling->keys];

	data[_idx - 1] = sibling->data[sibling->keys - 1];

	_child->keys += 1;
	sibling->keys -= 1;
}

void Node::borrow_from_next(int _idx) {
	Node* _child = child[_idx];
	Node* sibling = child[_idx + 1];

	_child->data[_child->keys] = data[_idx];

	if (!_child->leaf)
		_child->child[_child->keys + 1] = sibling->child[0];

	data[_idx] = sibling->data[0];

	for (int i = 1; i < sibling->keys; ++i)
		sibling->data[i - 1] = sibling->data[i];

	if (!sibling->leaf) {
		for (int i = 1; i <= sibling->keys; ++i)
			sibling->child[i - 1] = sibling->child[i];
	}

	_child->keys += 1;
	sibling->keys -= 1;
}

void Node::merge(int _idx) {
	Node* _child = child[_idx];
	Node* sibling = child[_idx + 1];

	_child->data[order - 1] = data[_idx];

	for (int i = 0; i < sibling->keys; ++i)
		_child->data[i + order] = sibling->data[i];

	if (!_child->leaf) {
		for (int i = 0; i <= sibling->keys; ++i)
			_child->child[i + order] = sibling->child[i];
	}

	for (int i = _idx + 1; i < keys; ++i)
		data[i - 1] = data[i];

	for (int i = _idx + 2; i <= keys; ++i)
		child[i - 1] = child[i];

	_child->keys += sibling->keys + 1;
	keys--;

	delete(sibling);
}

void Node::level(Node* temp, int level) {
	if (level > 1 && leaf) {
		return;
	}
	else if (level == 1) {
		for (int i = 0; i < keys; i++) {
			cout << data[i] << " ";
		}
	}
	else {
		for (int i = 0; i <= keys; i++) {
			child[i]->level(temp, level - 1);
		}
	}
}

Node* Node::search(int _key) {
	int i = 0;

	while (i < keys && _key > data[i])
		i++;

	if (data[i] == _key)
		return this;

	if (leaf == true)
		return NULL;

	return child[i]->search(_key);
}

int Node::find_index(int _key) {
	int idx = 0;

	while (idx < keys && data[idx] < _key)
		++idx;

	return idx;
}

int Node::get_pred(int _idx) {
	Node* current = child[_idx];

	while (!current->leaf)
		current = current->child[current->keys];

	return current->data[current->keys - 1];
}

int Node::get_succ(int _idx) {
	Node* current = child[_idx + 1];

	while (!current->leaf)
		current = current->child[0];

	return current->data[0];
}