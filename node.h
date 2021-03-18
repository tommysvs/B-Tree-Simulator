#ifndef NODE_H
#define NODE_H

class Node {
	private:
		int* keys;
		int min;
		Node** child;
		int total_keys;
		bool leaf;

	public:
		Node(int, bool);

		void insert_non_full(int);
		void split_child(int, Node*);
		void traverse();
		void remove(int);
		void remove_from_leaf(int);
		void remove_from_nonleaf(int);
		void fill(int);
		void borrow_from_prev(int);
		void borrow_from_next(int);
		void merge(int);
		Node* search(int);

		int find_index(int);
		int get_pred(int);
		int get_succ(int);

		friend class BTree;
};

#endif

