#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "Types.h"
#include "Allocator.h"
#include "Stack.h"
#include "Algorithm.h"

template <typename T, typename Alloc>
class BinarySearchTree;

template <typename T, typename Alloc>
class BinarySearchTree_Iterator;

template <typename T>
class BinarySearchTree_Node {
public:
	typedef T	value_t;

	T	key;
	mutable BinarySearchTree_Node *parent, *left, *right;

	BinarySearchTree_Node() : parent(0), left(0), right(0) {}
	BinarySearchTree_Node(const BinarySearchTree_Node &n) :
		key(n.key), parent(n.parent), left(n.left), right(n.right) {}
	BinarySearchTree_Node &operator =(const BinarySearchTree_Node &n) {
		key = T(n.key);
		parent = n.parent;
		left = n.left;
		right = n.right;
		return *this;
	}

	inline void construct()
		{ new ((void*)&key)T(); }
	inline void construct(const T &v)
		{ new ((void*)&key)T(v); }
	inline void destroy()
		{ ((T*)&key)->~T(); }
};

template <typename T, typename Alloc = Allocator>
class BinarySearchTree {
public:
	typedef T	value_t;

	typedef BinarySearchTree_Iterator<T, Alloc>	Iterator;
protected:
	typedef BinarySearchTree_Node<T>	node_t;
	node_t					*root;
	Object_Allocator<node_t, Alloc>	allocator;
	size_t _count;

	void rec_remove(node_t *n, const T &key);
	void rec_insert(node_t *n, const T &key);
	void rec_clear(node_t *n);
	void rec_copy(BinarySearchTree &t, const node_t *n) const;
	void replace_node_in_parent(node_t *node, node_t *newnode);	
public:
	BinarySearchTree() : root(0), allocator(), _count(0) {}
	BinarySearchTree(const BinarySearchTree &b);

	BinarySearchTree &operator = (const BinarySearchTree &b);
	
	Iterator begin() const;
	Iterator end() const;

	void swap(BinarySearchTree &b);
	void move(BinarySearchTree &b);

	void insert(const T &key);
	void remove(const T &key);
	bool exists(const T &key) const;
	const T *find(const T &key) const {
		node_t *node;
		for (node = root; node != 0; ) {
			if (key == node->key) return &node->key;
			if (key < node->key)
				node = node->left;
			else
				node = node->right;
		}
		return 0;
	}
	
	void clear();
	inline size_t count() const { return _count; }
	size_t depth() const;

	~BinarySearchTree() { this->clear(); }
};

template <typename T, typename Alloc>
class BinarySearchTree_Iterator {
	friend class BinarySearchTree<T, Alloc>;
protected:
	mutable BinarySearchTree_Node<T> *node, *last_visited;
public:
	typedef T	value_t;

	BinarySearchTree_Iterator() : node(), last_visited() {}
	BinarySearchTree_Iterator(const BinarySearchTree_Iterator &it) :
		node(it.node), last_visited(it.last_visited) {}
	BinarySearchTree_Iterator(
		BinarySearchTree_Node<T> * const n
	) : node(n), last_visited(0) {}

	const BinarySearchTree_Iterator &operator =(const BinarySearchTree_Iterator &b) {
		node = b.node;
		last_visited = b.last_visited;
		return *this;
	}

	const T & operator * () const { return node->key; }
	const T *operator -> () const { return &node->key; }
	
	const BinarySearchTree_Iterator &operator ++ () const;
	
	BinarySearchTree_Iterator operator ++ (int) const {
		BinarySearchTree_Iterator tmp(*this);
		this->operator ++();
		return tmp;
	}
	
	bool operator == (const BinarySearchTree_Iterator &it) const
		{ return node == it.node; }
	bool operator != (const BinarySearchTree_Iterator &it) const
		{ return node != it.node; }
};


#include "BinarySearchTree.tcc"

#endif
