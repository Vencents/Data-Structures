template <typename T, typename Alloc>
void Array<T, Alloc>::move(Array &a) {
	Object_Allocator<Array<T, Alloc> >::destroy(&a);
	a._base = _base;
	a._dend = _dend;
	a._end = _end;
	_base = _dend = _end = 0;	
}

template <typename T, typename Alloc>
void Array<T, Alloc>::swap(Array &a) {
	Algorithm::swap(_base, a._base);
	Algorithm::swap(_dend, a._dend);
	Algorithm::swap(_end, a._end);
}

template <typename T, typename Alloc>
Array<T, Alloc>::~Array() {
	if (_base) {
		allocator.destroy_range(_base, _dend - _base);
		allocator.free(_base);
		_base = _dend = _end = 0;
	}
}

template <typename T, typename Alloc>
void Array<T, Alloc>::double_capacity() {
	T *new_base;
	ptrdiff_t dend_off, end_off;
	dend_off = _dend - _base;
	end_off = _end - _base;
	if (_base == 0) end_off = 2;
	new_base = allocator.realloc(_base, (end_off *= 2));
	_base = new_base;
	_dend = new_base + dend_off;
	_end = new_base + end_off;
}

template <typename T, typename Alloc>
void Array<T, Alloc>::push(const T &val) {
	if (_dend == _end) double_capacity();
	allocator.construct(_dend++, val);	
}

template <typename T, typename Alloc>
T Array<T, Alloc>::pop() {
	if (_base == 0 || _dend - _base == 0)
		throw Enodata();
	T tmp(*--_dend);
	allocator.destroy(_dend);
	return tmp;
}

template <typename T, typename Alloc>
void Array<T, Alloc>::unshift(const T &val) {
	if (_dend == _end) double_capacity();
	T *p = _dend;
	if (p != _base) { allocator.construct(p, *(p - 1)); --p; }
	for (; p != _base; --p) {
		*p = *(p - 1);
	}
	*_base = val;
	++_dend;
}

template <typename T, typename Alloc>
T Array<T, Alloc>::shift() {
	if (_base == 0 || _dend == _base)
		throw Enodata();
	T *p;
	T tmp(*_base);
	--_dend;
	for (p = _base; p != _dend; ++p) {
		*p = *(p + 1);
	}
	allocator.destroy(p);
	return tmp;
}

template <typename T, typename Alloc>
T &Array<T, Alloc>::operator [] (ssize_t i) {
	if (_base == 0 || _dend - _base == 0)
		throw Enodata();
	if ((i > 0 ? i : -i - 1) >= _dend - _base)
		throw Erange();
	if (i < 0) return *(_dend + i);
	return *(_base + i);
}

template <typename T, typename Alloc>
const T &Array<T, Alloc>::operator [] (ssize_t i) const {
	if (_base == 0 || _dend - _base == 0)
		throw Enodata();
	if ((i > 0 ? i : -i - 1) >= _dend - _base)
		throw Erange();
	if (i < 0) return *(_dend + i);
	return *(_base + i);
}

template <typename T, typename Alloc>
void Array<T, Alloc>::insert(ssize_t index, const T &val) {
	T *p, *p2;
	if (_dend == _end) double_capacity();
	if (index < 0) p = _dend + index;
	else p = _base + index;
	if (p > _dend) throw Erange();

	if (p == _dend) {
		allocator.construct(p, val);
		++_dend;
		return;
	}
	
	p2 = _dend++;
	allocator.construct(p2, *(p2 - 1));
	--p2;
	for (; p2 != p; --p2) {
		*p2 = *(p2 - 1);
	}
	*p2 = val;
}

template <typename T, typename Alloc>
void Array<T, Alloc>::remove(ssize_t index, size_t n) {
	T *pstart, *pend, *p;
	if (index < 0) pstart = _dend + index;
	else pstart = _base + index;
	pend = pstart + n;
	if (pend  > _dend) throw Erange();

	for (p = pend; pstart != pend && p != _dend; ++pstart, ++p) {
		*pstart = *p;
	}
	for (; p != _dend; ++p, ++pstart) {
		*pstart = *p;
	}
	for (; pstart != _dend; ++pstart) {
		allocator.destroy(pstart);
	}
	_dend -= n;
}

template <typename T, typename Alloc>
void Array<T, Alloc>::insertAt(Iterator pos, const T &val) {
	T *p;
	if (_dend == _end) double_capacity();
	if (pos > _dend) throw Erange();
	
	if (pos == _dend) {
		allocator.construct(pos, val);
		++_dend;
		return;
	}

	p = _dend++;
	allocator.construct(p, *(p - 1));
	--p;
	for (; p != pos; --p) {
		*p = *(p - 1);
	}
	*p = val;
}

template <typename T, typename Alloc>
void Array<T, Alloc>::removeAt(Iterator pos, size_t n) {
	T *p, *pend;
	pend = pos + n;
	if (pend > _dend) throw Erange();
	
	for (p = pend; pos != pend && p != _dend; ++pos, ++p) {
		*pos = *p;
	}
	for (; p != _dend; ++p, ++pos) {
		*pos = *p;
	}
	for (; pos != _dend; ++pos) {
		allocator.destroy(pos);
	}
	_dend -= n;
}

template <typename T, typename Alloc>
Array<T, Alloc> Array<T, Alloc>::slice(ssize_t index, size_t n) const {
	Array tmp;
	size_t capacity = n;
	T *p;
	if (index < 0) p = _dend + index;
	else p = _base + index;
	if (p + n > _dend) throw Erange();

	while (capacity % 2) ++capacity;
	tmp._base = tmp._dend = tmp.allocator.alloc(capacity);
	tmp._end = tmp._base + capacity;
	for (size_t i = 0; i != n; ++i, ++tmp._dend, ++p) {
		tmp.allocator.construct(tmp._dend, *p);
	}
	return tmp;
}

template <typename T, typename Alloc>
Array<T, Alloc> Array<T, Alloc>::sliceAt(Iterator pos, size_t n) const {
	Array tmp;
	size_t capacity = n;
	if (pos + n > _dend) throw Erange();
	
	while (capacity % 2) ++capacity;
	tmp._base = tmp._dend = tmp.allocator.alloc(capacity);
	tmp._end = tmp._base + capacity;
	for (size_t i = 0; i != n; ++i, ++tmp._dend, ++pos) {
		tmp.allocator.construct(tmp._dend, *pos);
	}
	return tmp;
}

template <typename T, typename Alloc>
template <typename InputIter>
void Array<T, Alloc>::set(InputIter it, size_t n) {
	T *p;
	size_t i = 0;

	for (p = _base; i != n && p != _dend; ++p, ++it, ++i) {
		*p = *it;
	}
	for (; p != _dend; ++p) {
		allocator.destroy(p);
	}
	for (; i != n; ++i, ++it, ++p) {
		if (_dend == _end) double_capacity();
		allocator.construct(p, *it);
	}
	_dend = _base + n;
}

template <typename T, typename Alloc>
void Array<T, Alloc>::resize(size_t n) {
	T *new_dend;
	new_dend = _base + n;
	
	for (; _dend > new_dend; --_dend) {
		allocator.destroy(_dend);
	}
	for (; _dend < new_dend; ++_dend) {
		if (_dend == _end) double_capacity();
		allocator.construct(_dend);
	}
}

template <typename T, typename Alloc>
void Array<T, Alloc>::resize(size_t n, const T &val) {
	T *new_dend;
	new_dend = _base + n;
	for (; _dend > new_dend; --_dend) {
		allocator.destroy(_dend);
	}
	for (; _dend < new_dend; ++_dend) {
		if (_dend == _end) double_capacity();
		allocator.construct(_dend, val);
	}
}
