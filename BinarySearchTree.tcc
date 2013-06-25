template <typename T, typename Alloc>
const BinarySearchTree_Iterator<T, Alloc> &BinarySearchTree_Iterator<T, Alloc>::operator ++ () const {
	if (node == 0) throw Erange();
	if (node->parent == 0 && last_visited != 0) {
		if (last_visited == node->left) {
			if (node->right == 0) { node = 0; return *this; }
			last_visited = node;
			node = node->right;
			while (node->left != 0) node = node->left;
			return *this;
		} else { node = 0; return *this; }
	}
	if (node->left == 0 && node->right == 0) {
		last_visited = node;
		node = node->parent;
		if (node->left == last_visited) return *this;
		else {
			while (node->key < last_visited->key) {
				if (node->parent == 0) { node = 0; return *this; }
				node = node->parent;
			}
			last_visited = node->left;
		}
		return *this;
	} else if (node->left == last_visited || node->left == 0) {
		last_visited = node;
		if (node->right == 0) { node = node->parent; return *this; }
		else node = node->right;
	} else if (node->right == last_visited && last_visited != 0) {
		last_visited = node;
		node = node->parent;
		return *this;
	}
	while (node->left != 0) { node = node->left; }
	return *this;
	
}

template <typename T, typename Alloc>
typename BinarySearchTree<T, Alloc>::Iterator BinarySearchTree<T, Alloc>::begin() const {
	node_t *node = root;
	if (node == 0) return Iterator(0);
	while (node->left != 0) { node = node->left; }	
	return Iterator(node);
}

template <typename T, typename Alloc>
typename BinarySearchTree<T, Alloc>::Iterator BinarySearchTree<T, Alloc>::end() const {
	return Iterator(0);
}

template <typename T, typename Alloc>
bool BinarySearchTree<T, Alloc>::exists(const value_t &key) const {
	node_t *node;
	for (node = root; node != 0; ) {
		if (key == node->key) return true;
		if (key < node->key)
			node = node->left;
		else
			node = node->right;
	}
	return false;
}
/*
template <typename T, typename Alloc>
typename BinarySearchTree<T, Alloc>::const_ptr_t BinarySearchTree<T, Alloc>::find(const value_t &key) const {
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
*/

template <typename T, typename Alloc>
template <typename Callback>
bool BinarySearchTree<T, Alloc>::rec_walk(Callback callback, node_t *node) {
	if (node == 0) return true;
	if (this->real_walk(callback, node->left) == false) return false;
	if (callback(node->key) == false) return false;
	if (this->real_walk(callback, node->right) == false) return false;
	return true;
}

template <typename T, typename Alloc>
template <typename Callback>
void BinarySearchTree<T, Alloc>::walk(Callback callback) {
	this->rec_walk<Callback>(callback, root);
}

template <typename T, typename Alloc>
void BinarySearchTree<T, Alloc>::rec_clear(node_t *node) {
	if (node == 0) return;
	rec_clear(node->left);
	rec_clear(node->right);
	node->destroy();
	allocator.free(node);
}

template <typename T, typename Alloc>
void BinarySearchTree<T, Alloc>::clear() {
	this->rec_clear(root);
	root = 0;
	_count = 0;
}

template <typename T, typename Alloc>
void BinarySearchTree<T, Alloc>::move(BinarySearchTree &b) {
	if (b.root) b.clear();
	b.root = root;
	b._count = _count;
	root = 0;
	_count = 0;
}

template <typename T, typename Alloc>
void BinarySearchTree<T, Alloc>::swap(BinarySearchTree &b) {
	Algorithm::swap(root, b.root);
	Algorithm::swap(_count, b._count);
}

template <typename T, typename Alloc>
void BinarySearchTree<T, Alloc>::rec_insert(node_t *node, const value_t &key) {
	node_t *newnode;
	if (key < node->key) {
		if (node->left == 0) {
			newnode = allocator.alloc(1);
			allocator.construct(newnode);
			newnode->construct(key);
			node->left = newnode;
			newnode->parent = node;
			++_count;
		} else rec_insert(node->left, key);
	} else if (node->key < key) {
		if (node->right == 0) {
			newnode = allocator.alloc(1);
			allocator.construct(newnode);
			newnode->construct(key);
			node->right = newnode;
			newnode->parent = node;
			++_count;
		} else rec_insert(node->right, key);
	} else {
		node->key = key;
	}
}

template <typename T, typename Alloc>
void BinarySearchTree<T, Alloc>::insert(const value_t &key) {
	if (root == 0) {
		root = allocator.alloc(1);
		allocator.construct(root);
		root->construct(key);
	} else this->rec_insert(root, key);
}

template <typename T, typename Alloc>
void BinarySearchTree<T, Alloc>::replace_node_in_parent(node_t *node, node_t *newnode) {
	if (node->parent) {
		if (node == node->parent->left)
			node->parent->left = newnode;
		else
			node->parent->right = newnode;
	}
	if (newnode) newnode->parent = node->parent;
	node->destroy();
	allocator.free(node);
}

template <typename T, typename Alloc>
void BinarySearchTree<T, Alloc>::rec_remove(node_t *node, const value_t &key) {
	node_t *successor;
	if (key < node->key) {
		if (node->left == 0) throw Erange();
		rec_remove(node->left, key);
	} else if (node->key < key) {
		if (node->right == 0) throw Erange();
		rec_remove(node->right, key);
	} else {
		if (node->left && node->right) {
			successor = node->right;
			while (successor->left) successor = successor->left;
			rec_remove(successor, successor->key);
		} else if (node->left) {
			replace_node_in_parent(node, node->left);
		} else if (node->right) {
			replace_node_in_parent(node, node->right);
		} else {
			replace_node_in_parent(node, 0);
		}
	}
}

template <typename T, typename Alloc>
void BinarySearchTree<T, Alloc>::remove(const value_t &key) {
	if (_count == 0) throw Enodata();
	this->rec_remove(root, key);
}

template <typename T, typename Alloc>
size_t BinarySearchTree<T, Alloc>::depth() const {
	node_t *left, *right;
	size_t left_depth = 0, right_depth = 0;
	for (left = root; left != 0; left = left->left) ++left_depth;
	for (right = root; right != 0; right = right->right) ++right_depth;
	return (left_depth > right_depth) ? left_depth : right_depth;
}
