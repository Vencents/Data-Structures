
template <typename T, typename Alloc>
const Slinkedlist_Iterator<T, Alloc> &Slinkedlist_Iterator<T, Alloc>::operator ++ () const {
	if (curr == 0) return *this;
	curr = curr->next;
	return *this;
}

template <typename T, typename Alloc>
const Slinkedlist_Iterator<T, Alloc> Slinkedlist_Iterator<T, Alloc>::operator ++ (int) const {
	if (curr == 0) return *this;
	Slinkedlist_Iterator tmp(*this);
	curr = curr->next;
	return tmp;
}

template <typename T, typename A>
Slinkedlist<T, A>::Slinkedlist(size_t n, typename Const<ref_t>::type val) :
	front(), back(),
	_count(), allocator() {
	this->resize(n, val);
}

template <typename T, typename A>
template <typename InputIter>
Slinkedlist<T, A>::Slinkedlist(typename Const<InputIter>::type p, size_t n) :
	front(), back(), _count(), allocator() {
	this->set(p, n);	
}

template <typename T, typename A>
Slinkedlist<T, A>::Slinkedlist(typename Const<ptr_t>::type p, size_t n) :
	front(), back(), _count(), allocator() {
	this->set<ptr_t>(p, n);
}

template <typename T, typename A>
template <size_t N>
Slinkedlist<T, A>::Slinkedlist(const value_t (&lst)[N]) : front(), back(), _count(), allocator() {
	this->set<ptr_t>(lst, N);
}

template <typename T, typename A>
Slinkedlist<T, A>::~Slinkedlist() {
	this->clear();
}

template <typename T, typename A>
void Slinkedlist<T, A>::move(Slinkedlist &t) {
	t.front = front;
	t.back = back;
	t.before_front.next = before_front.next;
	t._count = _count;
	front = 0;
	back = 0;
	_count = 0;
}

template <typename T, typename A>
void Slinkedlist<T, A>::swap(Slinkedlist &t) {
	Algorithm::swap(_count, t._count);
	Algorithm::swap(front, t.front);
	Algorithm::swap(back, t.back);
	Algorithm::swap(before_front, t.before_front);
}

template <typename T, typename A>
typename Slinkedlist<T, A>::Iterator Slinkedlist<T, A>::begin() {
	return Slinkedlist_Iterator<T, A>(front);	
}


template <typename T, typename A>
typename Const<typename Slinkedlist<T, A>::Iterator>::type Slinkedlist<T, A>::begin() const {
	return Slinkedlist_Iterator<T, A>(front);	
}

template <typename T, typename A>
typename Slinkedlist<T, A>::Iterator Slinkedlist<T, A>::beforeBegin() {
	before_front.next = front;
	return Slinkedlist_Iterator<T, A>(&before_front);
}

template <typename T, typename A>
typename Const<typename Slinkedlist<T, A>::Iterator>::type Slinkedlist<T, A>::beforeBegin() const {
	before_front.next = front;
	return Slinkedlist_Iterator<T, A>(&before_front);
}


template <typename T, typename A>
typename Slinkedlist<T, A>::Iterator Slinkedlist<T, A>::end() {
	return Slinkedlist_Iterator<T, A>(0);
}

template <typename T, typename A>
typename Const<typename Slinkedlist<T, A>::Iterator>::type Slinkedlist<T, A>::end() const {
	return Slinkedlist_Iterator<T, A>(0);
}

template <typename T, typename A>
typename Slinkedlist<T, A>::Iterator Slinkedlist<T, A>::beforeEnd() {
	return Slinkedlist_Iterator<T, A>(back);
}

template <typename T, typename A>
typename Const<typename Slinkedlist<T, A>::Iterator>::type Slinkedlist<T, A>::beforeEnd() const {
	return Slinkedlist_Iterator<T, A>(back);
}

template <typename T, typename A>
template <typename InputIter>
void Slinkedlist<T, A>::set(typename Const<InputIter>::type p, size_t n) {
	size_t i = 0;
	Slinkedlist_Node<T> *node;
	_count = 0;
	for (node = front; node != 0; node = node->next) {
		if (i == n) return;
		node->val = *p++;
	}
	for (; i != n; ++i) {
		node = allocator.alloc(1);
		node->construct(*p++);
		node->next = 0;
		if (back != 0) back->next = node;
		back = node;
		if (_count++ == 0) front = node;
	}
}

template <typename T, typename A>
void Slinkedlist<T, A>::set(typename Const<ptr_t>::type p, size_t n) {
	this->set<ptr_t>(p, n);
}

void Slinkedlist<T, A>::clear() {
	Slinkedlist_Node<T> *node;
	for (node = front; node != 0; node = node->next) {
		node->destroy();
		allocator.free(node);
	}
	_count = 0;
}

template <typename T, typename A>
void Slinkedlist<T, A>::resize(size_t n, typename Const<ref_t>::type val) {
	size_t i;
	Slinkedlist_Node<T> *node;
	if (n == _count) return;
	if (n < _count) {
		node = front;
		for (i = 0; i != n; ++i) {
			node = node->next;
		}
		while (node != 0) {
			node->destroy();
			allocator.free(node);
			node = node->next;
		}
		_count = n;
		return;	
	}
	for (; _count != n; ++_count) {
		node = allocator.alloc(1);
		node->construct(val);
		if (back != 0) back->next = node;
		back = node;
		back->next = 0;
		if (_count == 0) front = node;
	}
	_count = n;
}

template <typename T, typename A>
typename Slinkedlist<T, A>::value_t Slinkedlist<T, A>::first() const {
	if (_count == 0) throw Enodata();
	return front->val;
}

template <typename T, typename A>
typename Slinkedlist<T, A>::value_t Slinkedlist<T, A>::last() const {
	if (_count == 0) throw Enodata();
	return back->val;
}

template <typename T, typename A>
size_t Slinkedlist<T, A>::unshift(typename Const<ref_t>::type val) {
	Slinkedlist_Node<T> *node;
	node = allocator.alloc(1);
	node->construct(val);
	node->next = front;
	front = node;
	if (back == 0) back = node;
	return ++_count;
}

template <typename T, typename A>
typename Slinkedlist<T, A>::value_t Slinkedlist<T, A>::shift() {
	Slinkedlist_Node<T> *node;
	if (front == 0) throw Enodata();
	value_t tmp(front->val);
	node = front;
	front = node->next;
	node->destroy();
	allocator.free(node);
	return tmp;	
}

template <typename T, typename A>
void Slinkedlist<T, A>::insertAfter(Iterator before, typename Const<ref_t>::type val) {
	Slinkedlist_Node<T> *node;
	node = allocator.alloc(1);
	node->construct(val);
	node->next = before.curr->next;
	before.curr->next = node;
}

template <typename T, typename A>
void Slinkedlist<T, A>::removeAfter(Iterator before, size_t n) {
	size_t i;
	Slinkedlist_Node<T> *node;
	if (n > _count) throw Erange();
	for (i = 0; i != n; ++i) {
		if (before.curr == 0) throw Erange();
		node = before.curr->next;
		node->destroy();
		before.curr->next = node->next;
		allocator.free(node);
		--_count;
	}	
}

template <typename T, typename A>
typename Slinkedlist<T, A>::Iterator Slinkedlist<T, A>::findBefore(typename Const<ref_t>::type val) const {
	Slinkedlist_Node<T> *node, *before = 0;
	for (node = front; node != 0; node = node->next) {
		if (node->val == val) return Slinkedlist_Iterator<T, A>(before);
		before = node;
	}
	return Slinkedlist_Iterator<T, A>(0);	
}

template <typename T, typename A>
typename Slinkedlist<T, A>::Iterator Slinkedlist<T, A>::rfindBefore(typename Const<ref_t>::type val) const {
	Slinkedlist_Node<T> *node, *before = 0, *before_last_found = 0;
	for (node = front; node != 0; node = node->next) {
		if (node->val == val) { before_last_found = before; }
		before = node;
	}
	return Slinkedlist_Iterator<T, A>(0);	
}

template <typename T, typename A>
typename Slinkedlist<T, A>::Iterator Slinkedlist<T, A>::find(typename Const<ref_t>::type val) const {
	Slinkedlist_Node<T> *node;
	for (node = front; node != 0; node = node->next) {
		if (node->val == val) return node;
	}
	return Slinkedlist_Iterator<T, A>(0);
}

template <typename T, typename A>
typename Slinkedlist<T, A>::Iterator Slinkedlist<T, A>::rfind(typename Const<ref_t>::type val) const {
	Slinkedlist_Node<T> *node, *last_found = 0;;
	for (node = front; node != 0; node = node->next) {
		if (node->val == val) last_found = node;
	}
	return Slinkedlist_Iterator<T, A>(last_found);
}

template <typename T, typename A>
typename Slinkedlist<T, A>::ref_t Slinkedlist<T, A>::operator [] (ssize_t index) {
	size_t real_index, i;
	Slinkedlist_Node<T> *node;
	if (index < 0) real_index = _count + index;
	else real_index = index;
	if (real_index >= _count) throw Erange();
	node = front;
	for (i = 0; i != real_index; ++i) {
		node = node->next;
	}
	return node->val;
}	


template <typename T, typename A>
typename Const<typename Slinkedlist<T, A>::ref_t>::type Slinkedlist<T, A>::operator [] (ssize_t index) const {
	size_t real_index, i;
	Slinkedlist_Node<T> *node;
	if (index < 0) real_index = _count + index;
	else real_index = index;
	if (real_index >= _count) throw Erange();
	node = front;
	for (i = 0; i != real_index; ++i) {
		node = node->next;
	}
	return node->val;
}

template <typename T, typename A>
typename Slinkedlist<T, A>::Iterator Slinkedlist<T, A>::from(ssize_t index) {
	size_t i, real_index;
	Slinkedlist_Node<T> *node;
	if (index < 0) real_index = _count + index;
	else real_index = index;
	if (real_index >= _count) throw Erange();
	node = front;
	for (i = 0; i != real_index; ++i) {
		node = node->next;
	}
	return Slinkedlist_Iterator<T, A>(node);
}

template <typename T, typename A>
typename Const<typename Slinkedlist<T, A>::Iterator>::type Slinkedlist<T, A>::from(ssize_t index) const {
	size_t i, real_index;
	Slinkedlist_Node<T> *node;
	if (index < 0) real_index = _count + index;
	else real_index = index;
	if (real_index >= _count) throw Erange();
	node = front;
	for (i = 0; i != real_index; ++i) {
		node = node->next;
	}
	return Slinkedlist_Iterator<T, A>(node);
}


