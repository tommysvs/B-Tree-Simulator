#ifndef NODE_H
#define NODE_H

class Node {
	private:
		int* keys;
		int min;
		Node** child;
		int n;
		bool leaf;

	public:
		Node(int _min, bool _leaf);

		void insert_non_full(int k);
		void split_child(int i, Node* y);
		void traverse();
		Node* search(int k);

		friend class BTree;
};

#endif

