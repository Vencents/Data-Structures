
template <typename T, typename Alloc>
Linkedlist<T, Alloc>::Linkedlist() {
	head.prev = 0;
	head.next = &tail;
	tail.prev = &head;
	tail.next = 0;
	_count = 0;
}

template <typename T, typename Alloc>
void Linkedlist<T, Alloc>::move(Linkedlist &t) {
	t.clear();
	t.head.prev = 0;
	t.tail.next = 0;
	if ((t._count = _count) == 0) {
		t.head.next = &t.tail;
		t.tail.prev = &t.head;
		return;
	}
	t.head.next = head.next;
	t.tail.prev = tail.prev;
	head.next = &tail;
	tail.prev = &head;
	_count = 0;
}

template <typename T, typename Alloc>
void Linkedlist<T, Alloc>::swap(Linkedlist &t) {
	Linkedlist tmp;
	t.move(tmp);
	this->move(t);
	tmp.move(*this);
}

template <typename T, typename Alloc>
void Linkedlist<T, Alloc>::clear() {
	node_t *node, *next;
	if (_count == 0) return;
	for (node = head.next; node != &tail; node = next) {
		next = node->next;
		node->destroy();
		allocator.free(node);	
	}
	_count = 0;
	head.next = &tail;
	tail.prev = &head;
}

template <typename T, typename Alloc>
T &Linkedlist<T, Alloc>::operator [] (ssize_t index) {
	node_t *node;
	if (index < 0) {
		index *= -1;
		if (index >= _count) throw Erange();
		node = &tail;
		for (size_t i = 0; i != index; ++i) {
			node = node->prev; 	
		}
	} else {
		if (index >= _count) throw Erange();
		node = head.next;
		for (size_t i = 0; i != index; ++i) {
			node = node->next;
		}
	}
	return node->value;
}

template <typename T, typename Alloc>
const T &Linkedlist<T, Alloc>::operator [] (ssize_t index) const {
	node_t *node;
	if (index < 0) {
		index *= -1;
		if (index >= _count) throw Erange();
		node = &tail;
		for (size_t i = 0; i != index; ++i) {
			node = node->prev; 	
		}
	} else {
		if (index >= _count) throw Erange();
		node = head.next;
		for (size_t i = 0; i != index; ++i) {
			node = node->next;
		}
	}
	return node->value;
}

template <typename T, typename Alloc>
void Linkedlist<T, Alloc>::push(const T &val) {
	node_t *node;
	node = allocator.alloc(1);	
	node->construct(val);
	node->prev = tail.prev;
	node->prev->next = node;
	node->next = &tail;
	tail.prev = node;
	++_count;
}

template <typename T, typename Alloc>
T Linkedlist<T, Alloc>::pop() {
	if (_count == 0) throw Enodata();
	node_t *last_node = tail.prev;
	T tmp(last_node->value);
	tail.prev = last_node->prev;
	last_node->prev->next = &tail;
	last_node->destroy();
	allocator.free(last_node);
	--_count;
	return tmp;
}

template <typename T, typename Alloc>
void Linkedlist<T, Alloc>::unshift(const T &val) {
	node_t *node;
	node = allocator.alloc(1);
	node->construct(val);
	node->next = head.next;
	head.next = node;
	node->prev = &head;
	node->next->prev = node;
	++_count;
}

template <typename T, typename Alloc>
T Linkedlist<T, Alloc>::shift() {
	if (_count == 0) throw Enodata();
	node_t *first_node = head.next;
	T tmp(first_node->value);
	head.next = first_node->next;
	first_node->next->prev = &head;
	first_node->destroy();
	allocator.free(first_node);
	--_count;
	return tmp;	
}

template <typename T, typename Alloc>
typename Linkedlist<T, Alloc>::Iterator Linkedlist<T, Alloc>::insertAt(Iterator pos, const T &val) {
	node_t *node;
	node = allocator.alloc(1);
	node->construct(val);
	node->prev = pos.curr->prev;
	node->prev->next = node;
	node->next = pos.curr;
	node->next->prev = node;
	++_count;
	return Iterator(node->next, pos.index + 1);
}

template <typename T, typename Alloc>
typename Linkedlist<T, Alloc>::Iterator Linkedlist<T, Alloc>::removeAt(Iterator pos, size_t n) {
	if (pos.index + n > _count) throw Erange();
	node_t *before_pos = pos.curr->prev, *next;
	size_t saved_pos = pos.index;
	for (size_t i = 0; i != n; ++i) {
		next = pos.curr->next;
		pos.curr->destroy();
		allocator.free(pos.curr);
		pos.curr = next;	
	}
	before_pos->next = pos.curr;
	pos.curr->prev = before_pos; 
	return Iterator(pos.curr, ++saved_pos);
}

template <typename T, typename Alloc>
void Linkedlist<T, Alloc>::insert(ssize_t index, const T &val) {
	if (index < 0) index = _count + index;
	if (index > _count) throw Erange();
	size_t i;
	node_t *node;
	if (_count - index > index) {
		node = head.next;
		for (i = 0; i != index; ++i) {
			node = node->next;
		}
	} else {
		node = &tail;
		for (i = _count; i != index; --i) {
			node = node->prev;
		}
	}
	static_cast<void>(this->insertAt(Iterator(node, index), val));
}

template <typename T, typename Alloc>
void Linkedlist<T, Alloc>::remove(ssize_t index, size_t n) {
	if (index < 0) index = _count + index;
	if (index + n > _count) throw Erange();
	size_t i, index_last;
	node_t *node, *prev, *saved;
	if (_count - index > index) {
		node = head.next;
		for (i = 0; i != index; ++i) {
			node = node->next;
		}
		static_cast<void>(this->removeAt(Iterator(node, index), n));
	} else {
		node = &tail;
		index_last = index + n - 1;
		for (i = _count; i != index_last; --i) {
			node = node->prev;
		}
		saved = node->next;
		for (--index; i != index; --i) {
			node->destroy();
			prev = node->prev;
			allocator.free(node);
			node = prev;
		}
		saved->prev = node;
		node->next = saved;	
	} 
}

template <typename T, typename Alloc>
template <typename InputIter>
void Linkedlist<T, Alloc>::set(InputIter it, size_t n) {
	node_t *node, *next;
	size_t i;
	node = head.next;
	for (i = 0; i != n; ++i, ++it) {
		if (node == &tail) break;
		node->value = *it;
		node = node->next;
	}
	for (; node != &tail; node = next) {
		next = node->next;
		node->destroy();
		allocator.free(node);
	}
	for (; i != n; ++i, ++it) {
		node = allocator.alloc(1);
		node->construct(*it);
		node->next = &tail;
		node->prev = tail.prev;
		node->next->prev = node;
		node->prev->next = node;
	}
	_count = n;
}

template <typename T, typename Alloc>
void Linkedlist<T, Alloc>::resize(size_t n) {
	node_t *node, *saved;
	node = tail.prev;
	if (_count > n) {
		for (; _count > n; --_count) {
			node->destroy();
			saved = node->prev;
			allocator.free(node);
			node = saved;
		}
		node->next = &tail;
		tail.prev = node;
		return;
	} else {
		for (; _count < n; ++_count) {
			node = allocator.alloc(1);
			node->construct();
			node->prev = tail.prev;
			node->next = &tail;
			node->prev->next = node;
			tail.prev = node;
		}
	}
}

template <typename T, typename Alloc>
void Linkedlist<T, Alloc>::resize(size_t n, const T &val) {
	node_t *node, *saved;
	node = tail.prev;
	if (_count > n) {
		for (; _count > n; --_count) {
			node->destroy();
			saved = node->prev;
			allocator.free(node);
			node = saved;
		}
		node->next = &tail;
		tail.prev = node;
		return;
	} else {
		for (; _count < n; ++_count) {
			node = allocator.alloc(1);
			node->construct(val);
			node->prev = tail.prev;
			node->next = &tail;
			node->prev->next = node;
			tail.prev = node;
		}
	}
}

template <typename T, typename Alloc>
Linkedlist<T, Alloc>::Linkedlist(size_t n) {
	head.prev = 0;
	head.next = &tail;
	tail.prev = &head;
	tail.next = 0;
	this->resize(n);
}

template <typename T, typename Alloc>
Linkedlist<T, Alloc>::Linkedlist(size_t n, const T &val) {
	head.prev = 0;
	head.next = &tail;
	tail.prev = &head;
	tail.next = 0;
	this->resize(n, val);
}

template <typename T, typename Alloc>
Linkedlist<T, Alloc>::Linkedlist(const T *p, size_t n) {
	head.prev = 0;
	head.next = &tail;
	tail.prev = &head;
	tail.next = 0;
	this->set<const T*>(p, n);
}

