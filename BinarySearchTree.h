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
	typedef T	*ptr_t;
	typedef T	&ref_t;

	value_t	key;
	mutable BinarySearchTree_Node *parent, *left, *right;

	BinarySearchTree_Node() : parent(), left(), right() {}
	BinarySearchTree_Node(const BinarySearchTree_Node &n) :
		key(n.key), parent(n.parent), left(n.left), right(n.right) {}
	BinarySearchTree_Node &operator =(const BinarySearchTree_Node &n) {
		key = value_t(n.key);
		parent = n.parent;
		left = n.left;
		right = n.right;
		return *this;
	}

	inline void construct()
		{ new ((void*)&key)value_t(); }
	inline void construct(typename Const<ref_t>::type v)
		{ new ((void*)&key)value_t(v); }
	inline void destroy()
		{ ((value_t*)&key)->~value_t(); }
};

template <typename T, typename Alloc = Allocator>
class BinarySearchTree {
public:
	typedef T	value_t;
	typedef T	*ptr_t;
	typedef T	&ref_t;

	typedef BinarySearchTree_Iterator<T, Alloc>	Iterator;
protected:
	typedef BinarySearchTree_Node<T>	node_t;
	typedef typename Const<ptr_t>::type	const_ptr_t;
	node_t					*root;
	Object_Allocator<node_t, Alloc>	allocator;
	size_t _count;

	template <typename Callback>
	bool rec_walk(Callback callback, node_t *node);
	void rec_remove(node_t *n, const value_t &key);
	void rec_insert(node_t *n, const value_t &key);
	void rec_clear(node_t *n);
	void replace_node_in_parent(node_t *node, node_t *newnode);	
public:
	BinarySearchTree() : root(), allocator(), _count() {}
	
	Iterator begin() const;
	Iterator end() const;

	void swap(BinarySearchTree &b);
	void move(BinarySearchTree &b);

	void insert(const value_t &key);
	void remove(const value_t &key);
	bool exists(const value_t &key) const;
	const value_t *find(const value_t &key) const {
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

	template <typename Callback>
	void walk(Callback callback);

	~BinarySearchTree() { this->clear(); }
};

template <typename T, typename Alloc>
class BinarySearchTree_Iterator {
	friend class BinarySearchTree<T, Alloc>;
protected:
	mutable BinarySearchTree_Node<T> *node, *last_visited;
public:
	typedef T	value_t;
	typedef T	*ptr_t;
	typedef T	&ref_t;

	BinarySearchTree_Iterator() : node(), last_visited() {}
	BinarySearchTree_Iterator(const BinarySearchTree_Iterator &it) :
		node(it.node), last_visited(it.last_visited) {}
	BinarySearchTree_Iterator(
		BinarySearchTree_Node<T> * const n
	) : node(n), last_visited() {}

	const BinarySearchTree_Iterator &operator =(const BinarySearchTree_Iterator &b) {
		node = b.node;
		last_visited = b.last_visited;
		return *this;
	}

	const value_t & operator * () const { return node->key; }
	const value_t *operator -> () const { return &node->key; }
	
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
