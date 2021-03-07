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

		void insertNonFull(int k);
		void splitChild(int i, Node* y);
		void traverse();
		Node* search(int k);

		friend class BTree;
};

#endif

