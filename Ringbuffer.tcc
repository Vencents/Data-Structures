
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



