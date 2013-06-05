
template <typename T, typename C>
size_t Ringbuffer<T, C>::push(typename Const<ref_t>::type val) {
	*rear = val;
	++rear_index;
	if (++rear == c.end()) {
		rear = c.begin();
		rear_index = 0;
	}
	return ++_count;
}

template <typename T, typename C>
typename Ringbuffer<T, C>::value_t Ringbuffer<T, C>::pop() {
	value_t tmp(*rear);
	if (rear == c.begin()) { rear = c.end(); rear_index = c.count(); }
	--rear;
	--rear_index;
	--_count;
	return tmp;
}

template <typename T, typename C>
size_t Ringbuffer<T, C>::unshift(typename Const<ref_t>::type val) {
	if (front == c.begin()) { front = c.end(); front_index = c.count(); }
	--front;
	--front_index;
	*front = val;
	return ++_count;
}

template <typename T, typename C>
typename Ringbuffer<T, C>::value_t Ringbuffer<T, C>::shift() {
	value_t tmp(*front);
	++front_index;
	if (++front == c.end()) { front = c.begin(); front_index = 0; }
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
	if (index < 0) return c.operator [] (index + rear_index);
	else return c.operator [] (index + front_index);
}

template <typename T, typename C>
typename Const<typename Ringbuffer<T, C>::ref_t>::type Ringbuffer<T, C>::operator [] (ssize_t index) const {
	if (index < 0) return c.operator [] (index + rear_index);
	else return c.operator [] (index + front_index);
}



