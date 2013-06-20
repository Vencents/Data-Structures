
template <typename T, typename Alloc>
const Linkedlist_Iterator<T, Alloc> &Linkedlist_Iterator<T, Alloc>::operator ++ () const {
	if (curr->next == 0) throw Erange();
	curr = curr->next;
	return *this;
}

template <typename T, typename Alloc>
const Linkedlist_Iterator<T, Alloc> &Linkedlist_Iterator<T, Alloc>::operator -- () const {
	if (curr->prev == 0) throw Erange();
	curr = curr->prev;
	return *this;
}

template <typename T, typename Alloc>
Linkedlist_Iterator<T, Alloc> Linkedlist_Iterator<T, Alloc>::operator ++ (int) const {
	Linkedlist_Iterator tmp(*this);
	operator ++();
	return tmp;
}

template <typename T, typename Alloc>
Linkedlist_Iterator<T, Alloc> Linkedlist_Iterator<T, Alloc>::operator -- (int) const {
	Linkedlist_Iterator tmp(*this);
	operator --();
	return tmp;
}

template <typename T, typename Alloc>
bool Linkedlist_Iterator<T, Alloc>::operator == (const Linkedlist_Iterator &i) const {
	return curr == i.curr;
}

template <typename T, typename Alloc>
bool Linkedlist_Iterator<T, Alloc>::operator != (const Linkedlist_Iterator &i) const {
	return curr != i.curr;
}

template <typename T, typename Alloc>
typename Linkedlist<T, Alloc>::Iterator Linkedlist<T, Alloc>::begin() {
	return Linkedlist_Iterator<T, Alloc>(base_node.next);
}

template <typename T, typename Alloc>
typename Linkedlist<T, Alloc>::Iterator Linkedlist<T, Alloc>::end() {
	return Linkedlist_Iterator<T, Alloc>(&end_node);
}

template <typename T, typename Alloc>
typename Const<typename Linkedlist<T, Alloc>::Iterator>::type Linkedlist<T, Alloc>::begin() const {
	return Linkedlist_Iterator<T, Alloc>(base_node.next);
}

template <typename T, typename Alloc>
typename Const<typename Linkedlist<T, Alloc>::Iterator>::type Linkedlist<T, Alloc>::end() const {
	return Linkedlist_Iterator<T, Alloc>(&end_node);
}

template <typename T, typename Alloc>
typename Linkedlist<T, Alloc>::Reverser Linkedlist<T, Alloc>::rbegin() {
	return Linkedlist_Iterator<T, Alloc>(&end_node);
}

template <typename T, typename Alloc>
typename Linkedlist<T, Alloc>::Reverser Linkedlist<T, Alloc>::rend() {
	return Linkedlist_Iterator<T, Alloc>(base_node.next);
}

template <typename T, typename Alloc>
typename Const<typename Linkedlist<T, Alloc>::Reverser>::type Linkedlist<T, Alloc>::rbegin() const {
	return Linkedlist_Iterator<T, Alloc>(&end_node);
}

template <typename T, typename Alloc>
typename Const<typename Linkedlist<T, Alloc>::Reverser>::type Linkedlist<T, Alloc>::rend() const {
	return Linkedlist_Iterator<T, Alloc>(base_node.next);
}

template <typename T, typename Alloc>
Linkedlist<T, Alloc>::Linkedlist() : _count(), base_node(), end_node() {
	base_node.next = &end_node;
	base_node.prev = 0;
	end_node.next = 0;
	end_node.prev = &base_node;	
}

template <typename T, typename Alloc>
Linkedlist<T, Alloc>::Linkedlist(size_t n) : _count(), base_node(), end_node() {
	Linkedlist_Node<T> &node, *newnode;
	base_node.prev = 0;
	base_node.next = &end_node;
	end_node.next = 0;
	end_node.prev = &base_node;
	for (_count = 0; _count != n; ++_count) {
		newnode = allocator.alloc(1);
		newnode->construct(value_t());
		newnode->prev = end_node.prev;
		newnode->next = &end_node;
		newnode->prev->next = newnode;
		end_node.prev = newnode;
	}
}

template <typename T, typename Alloc>
template <typename InputIter>
Linkedlist<T, Alloc>::Linkedlist(typename Const<InputIter>::type p, size_t n) : _count(), base_node(), end_node() {
	base_node.next = &end_node;
	base_node.prev = 0;
	end_node.next = 0;
	end_node.prev = &base_node;
	this->set(p, n);	
}

template <typename T, typename Alloc>
Linkedlist<T, Alloc>::Linkedlist(typename Const<ptr_t>::type p, size_t n) : _count(), base_node(), end_node() {
	base_node.next = &end_node;
	base_node.prev = 0;
	end_node.next = 0;
	end_node.prev = &base_node;
	this->set<ptr_t>(p, n);
}

template <typename T, typename Alloc>
Linkedlist<T, Alloc>::Linkedlist(const Linkedlist &l) : _count(l._count), base_node(), end_node()  {
	Linkedlist_Node<T> *node, *newnode;
	base_node.prev = 0;
	base_node.next = &end_node;
	end_node.next = 0;
	end_node.prev = &base_node;
	for (node = l.base_node.next; node != &l.end_node; node = node->next) {
		newnode = allocator.alloc(1);
		newnode->construct(node->val);
		newnode->prev = end_node.prev;
		newnode->next = &end_node;
		newnode->prev->next = newnode;
		end_node.prev = newnode;		
	} 
};

template <typename T, typename Alloc>
Linkedlist<T, Alloc>::~Linkedlist() {
	this->clear();
}

template <typename T, typename Alloc>
void Linkedlist<T, Alloc>::move(Linkedlist &t) {
	t.base_node.prev = base_node.prev;
	t.base_node.next = base_node.next;
	t.end_node.prev = end_node.prev;
	t.end_node.next = end_node.next;
	t._count = _count;
	base_node.prev = 0;
	base_node.next = &end_node;
	end_node.prev = &base_node;	
	end_node.next = 0;
	_count = 0;
}

template <typename T, typename Alloc>
void Linkedlist<T, Alloc>::swap(Linkedlist &t) {
	Algorithm::swap(base_node, t.base_node);
	Algorithm::swap(end_node, t.end_node);
	Algorithm::swap(_count, t._count);
}

template <typename T, typename Alloc>
size_t Linkedlist<T, Alloc>::push(typename Const<ref_t>::type val) {
	Linkedlist_Node<T> *node;
	node = allocator.alloc(1);
	node->construct(val);
	node->prev = end_node.prev;
	node->next = &end_node;
	node->prev->next = node;
	end_node.prev = node;
	return ++_count;	
}

template <typename T, typename Alloc>
typename Linkedlist<T, Alloc>::value_t Linkedlist<T, Alloc>::pop() {
	Linkedlist_Node<T> *last;
	last = end_node.prev;
	if (last == &base_node) throw Enodata();
	value_t tmp(last->val);
	last->prev->next = &end_node;
	end_node.prev = last->prev;
	last->destroy();
	allocator.free(last);
	--_count;
	return tmp;
}

template <typename T, typename Alloc>
size_t Linkedlist<T, Alloc>::unshift(typename Const<ref_t>::type val) {
	Linkedlist_Node<T> *node;
	node = allocator.alloc(1);
	node->construct(val);
	node->prev = &base_node;
	node->next = base_node.next;
	base_node.next->prev = node;
	base_node.next = node;
	return ++_count;	
}

template <typename T, typename Alloc>
typename Linkedlist<T, Alloc>::value_t Linkedlist<T, Alloc>::shift() {
	Linkedlist_Node<T> *first;
	first = base_node.next;
	if (first == &end_node) throw Enodata();
	value_t tmp(first->val);
	base_node.next = first->next;
	first->next->prev = &base_node;
	first->destroy();
	allocator.free(first);
	--_count;
	return tmp;
}

template <typename T, typename Alloc>
typename Linkedlist<T, Alloc>::value_t Linkedlist<T, Alloc>::first() {
	if (base_node.next == &end_node) throw Enodata();
	return base_node.next->val;
}

template <typename T, typename Alloc>
typename Linkedlist<T, Alloc>::value_t Linkedlist<T, Alloc>::last() {
	if (end_node.prev == &base_node) throw Enodata();
	return end_node.prev->val;
}

template <typename T, typename Alloc>
void Linkedlist<T, Alloc>::clear() {
	Linkedlist_Node<T> *node, *next;
	if (_count == 0) return;
	for (node = base_node.next; node != &end_node; node = next) {
		node->destroy();
		next = node->next;
		allocator.free(node);
	}
	base_node.prev = 0;
	base_node.next = &end_node;
	end_node.prev = &base_node;
	end_node.next = 0;
	_count = 0;
}

template <typename T, typename Alloc>
void Linkedlist<T, Alloc>::resize(size_t n, typename Const<ref_t>::type val) {
	Linkedlist_Node<T> *node;
	if (n == _count) return;
	while (n > _count) {
		node = allocator.alloc(1);
		node->construct(val);
		node->prev = end_node.prev;
		node->next = &end_node;
		node->prev->next = node;
		end_node.prev = node;
		++_count;
	}
	while (n < _count) {
		node = end_node.prev;
		node->prev->next = &end_node;
		end_node.prev = node->prev;
		node->destroy();
		allocator.free(node);
		--_count;
	}
}	

template <typename T, typename Alloc>
size_t Linkedlist<T, Alloc>::insert(Iterator pos, typename Const<ref_t>::type val) {
	Linkedlist_Node<T> *node;
	node = allocator.alloc(1);
	node->construct(val);
	node->next = pos.curr;
	node->prev = pos.curr->prev;
	node->prev->next = node;
	node->next->prev = node;
	return ++_count;
}

template <typename T, typename Alloc>
void Linkedlist<T, Alloc>::remove(Iterator pos, size_t n) {
	Linkedlist_Node<T> *node, *next;
	if (n > _count) throw Erange();
	for (size_t i = 0; i != n; ++i) {
		if (pos == &end_node) throw Erange();
		pos.curr->destroy();
		next = pos.curr->next;
		pos.curr->prev->next = next;
		pos.curr->next->prev = pos.curr->prev;
		allocator.free(pos.curr);
		pos = next;
		--_count;
	}
}

template <typename T, typename Alloc>
void Linkedlist<T, Alloc>::fill(Iterator pos, size_t n, typename Const<ref_t>::type val) {
	size_t i = 0;
	Linkedlist_Node<T> *node;
	while (pos.curr != &end_node) {
		pos.curr->val = val;
		++pos; ++i; ++_count;
		if (i == n) return;
	}
	for (; i != n; ++i) {
		node = allocator.alloc(1);
		node->construct(val);
		node->next = &end_node;
		node->prev = end_node.prev;
		node->prev->next = node;
		end_node.prev = node;
		++_count;
	}
}

template <typename T, typename Alloc>
void Linkedlist<T, Alloc>::swap(const Linkedlist &t) {
	Algorithm::swap(base_node, t.base_node);
	Algorithm::swap(end_node, t.end_node);
	Algorithm::swap(_count, t._count);		
}

template <typename T, typename Alloc>
template <typename InputIter>
void Linkedlist<T, Alloc>::set(typename Const<InputIter>::type p, size_t n) {
	Linkedlist_Node<T> *node, *tmp;
	size_t i = 0;
	for (node = base_node.next; node != &end_node; node = node->next) {
		node->val = *p++;
		if (i++ == n) break;
	}
	if (i == n) {
		end_node.prev = node->prev;
		for (; node != &end_node; node = tmp) {
			tmp = node->next;
			node->destroy();
			allocator.free(node);	
		}
		_count = n;
		return;
	}
	for (; i != n; ++i) {
		node = allocator.alloc(1);
		node->construct(*p++);
		node->prev = end_node.prev;
		node->next = &end_node;
		node->prev->next = node;
		end_node.prev = node;
	}		
}

template <typename T, typename Alloc>
void Linkedlist<T, Alloc>::set(typename Const<ptr_t>::type p, size_t n) {
	this->set(p, n);
}

template <typename T, typename Alloc>
typename Linkedlist<T, Alloc>::Iterator Linkedlist<T, Alloc>::find(typename Const<ref_t>::type val) const {
	Linkedlist_Node<T> *node;
	for (node = base_node.next; node != &end_node; node = node->next) {
		if (node->val == val) return Linkedlist_Iterator<T, Alloc>(node);
	}
	return Linkedlist_Iterator<T, Alloc>(&end_node);
}

template <typename T, typename Alloc>
typename Linkedlist<T, Alloc>::Iterator Linkedlist<T, Alloc>::rfind(typename Const<ref_t>::type val) const {
	Linkedlist_Node<T> *node;
	for (node = end_node.prev; node != &base_node; node = node->prev) {
		if (node->val == val) return Linkedlist_Iterator<T, Alloc>(node);
	}
	return Linkedlist_Iterator<T, Alloc>(&end_node);
}

template <typename T, typename Alloc>
typename Linkedlist<T, Alloc>::ref_t Linkedlist<T, Alloc>::operator [] (ssize_t index) {
	size_t i = 0, real_index;
	Linkedlist_Node<T> *node;
	if (index < 0) real_index = _count + index;
	else real_index = index;
	if (real_index >= _count) throw Erange();
	if (real_index <= _count - real_index) {
		for (node = base_node.next; node != &end_node; node = node->next) {
			if (i == real_index) return node->val;
			++i;
		}
	} else {
		i = _count - 1;	
		for (node = end_node.prev; node != &base_node; node = node->prev) {
			if (i == real_index) return node->val;
			--i;
		}
	}
}

template <typename T, typename Alloc>
typename Const<typename Linkedlist<T, Alloc>::ref_t>::type Linkedlist<T, Alloc>::operator [] (ssize_t index) const {
	size_t i = 0, real_index;
	Linkedlist_Node<T> *node;
	if (index < 0) real_index = _count + index;
	else real_index = index;
	if (real_index >= _count) throw Erange();
	if (real_index <= _count - real_index) {
		for (node = base_node.next; node != &end_node; node = node->next) {
			if (i == real_index) return node->val;
			++i;
		}
	} else {
		i = _count - 1;	
		for (node = end_node.prev; node != &base_node; node = node->prev) {
			if (i == real_index) return node->val;
			--i;
		}
	}
}

template <typename T, typename Alloc>
typename Linkedlist<T, Alloc>::Iterator Linkedlist<T, Alloc>::from(ssize_t index) {
	size_t i = 0, real_index;
	Linkedlist_Node<T> *node;
	if (index < 0) real_index = _count + index;
	else real_index = index;
	if (real_index >= _count) throw Erange();
	if (real_index <= _count - real_index) {
		for (node = base_node.next; node != &end_node; node = node->next) {
			if (i == real_index) return typename Linkedlist<T, Alloc>::Iterator(node);
			++i;
		}
	} else {
		i = _count - 1;
		for (node = end_node.prev; node != &base_node; node = node->prev) {
			if (i == real_index) return typename Linkedlist<T, Alloc>::Iterator(node);
			--i;
		}
	}
}

template <typename T, typename Alloc>
typename Const<typename Linkedlist<T, Alloc>::Iterator>::type Linkedlist<T, Alloc>::from(ssize_t index) const {
	size_t i = 0, real_index;
	Linkedlist_Node<T> *node;
	if (index < 0) real_index = _count + index;
	else real_index = index;
	if (real_index >= _count) throw Erange();
	if (real_index <= _count - real_index) {
		for (node = base_node.next; node != &end_node; node = node->next) {
			if (i == real_index) return typename Linkedlist<T, Alloc>::Iterator(node);
			++i;
		}
	} else {
		i = _count - 1;
		for (node = end_node.prev; node != &base_node; node = node->prev) {
			if (i == real_index) return typename Linkedlist<T, Alloc>::Iterator(node);
			--i;
		}
	}
}
