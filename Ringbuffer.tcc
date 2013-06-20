
template <typename T, typename C>
Ringbuffer<T, C>::Ringbuffer(size_t size) : c(size), front_index(), rear_index() {
	front = typename C::Iterator(c.begin());
	rear = typename C::Iterator(c.begin());
}

template <typename T, typename C>
Ringbuffer<T, C>::Ringbuffer(const Ringbuffer &r) : c(r.c), front(r.front), rear(r.rear), _count(r._count), front_index(r.front_index), rear_index(r.rear_index) {}

template <typename T, typename C>
Ringbuffer<T, C>::Ringbuffer(const C &container) : c(container), front(c.begin()), rear(c.end()), _count(c.count()), front_index(), rear_index(c.count()) {
	--rear; --rear_index; c.resize(c.count() * 2);
}

template <typename T, typename C>
void Ringbuffer<T, C>::move(Ringbuffer &r) {
	r.front_index = front_index;
	r.rear_index = rear_index;
	r._count = _count;
	c.move(r.c);
	_count = 0;
}

template <typename T, typename C>
void Ringbuffer<T, C>::swap(Ringbuffer &r) {
	Algorithm::swap(front_index, r.front_index);
	Algorithm::swap(rear_index, r.rear_index);
	Algorithm::swap(_count, r._count);
	Algorithm::swap(front, r.front);
	Algorithm::swap(rear, r.rear);
	c.swap(r.c);
}

template <typename T, typename C>
size_t Ringbuffer<T, C>::push(typename Const<ref_t>::type val) {
	*rear = val;
	if (rear == front) next(front, front_index);
	next(rear, rear_index);
	return ++_count;
}

template <typename T, typename C>
typename Ringbuffer<T, C>::value_t Ringbuffer<T, C>::pop() {
	value_t tmp(*rear);
	prev(rear, rear_index);
	--_count;
	return tmp;
}

template <typename T, typename C>
size_t Ringbuffer<T, C>::unshift(typename Const<ref_t>::type val) {
	prev(front, front_index);
	*front = val;
	return ++_count;
}

template <typename T, typename C>
typename Ringbuffer<T, C>::value_t Ringbuffer<T, C>::shift() {
	value_t tmp(*front);
	next(front, front_index);
	--_count;
	return tmp;
}

template <typename T, typename C>
void Ringbuffer<T, C>::resize(size_t n) {
	c.resize(n);
	front = c.from(front_index);
	rear = c.from(rear_index);	
}

template <typename T, typename C>
typename Ringbuffer<T, C>::ref_t Ringbuffer<T, C>::operator [] (ssize_t index) {
	size_t s = c.count();
	if (index < 0) {
		if (rear_index + index < 0)
			return c.operator []((rear_index + index) + s);
		else return c.operator [](rear_index + index);
	} else {
		if (front_index + index >= s)
			return c.operator []((front_index + index) - s);
		else return c.operator [] (index + front_index);
	}
}

template <typename T, typename C>
typename Const<typename Ringbuffer<T, C>::ref_t>::type Ringbuffer<T, C>::operator [] (ssize_t index) const {
	size_t s = c.count();
	if (index < 0) {
		if (rear_index + index < 0)
			return c.operator []((rear_index + index) + s);
		else return c.operator [](rear_index + index);
	} else {
		if (front_index + index >= s)
			return c.operator []((front_index + index) - s);
		else return c.operator [] (index + front_index);
	}
}



