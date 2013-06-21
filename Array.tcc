template <typename T, typename Alloc>
void Array<T, Alloc>::move(Array &a) {
	if (a.buf_base != ptr_t()) {
		allocator.destroy_range(a.buf_base, a.buf_dend - a.buf_base);
		allocator.free(a.buf_base);
		a.buf_base = ptr_t();
	}
	a.buf_base = buf_base;
	a.buf_dend = buf_dend;
	a.buf_end = buf_end;
	buf_base = ptr_t();
	buf_dend = ptr_t();
	buf_end = ptr_t();
}

template <typename T, typename Alloc>
void Array<T, Alloc>::double_capacity() {
	ptr_t newbase;
	ptrdiff_t dend_offset, end_offset;
	dend_offset = buf_dend - buf_base;
	end_offset = buf_end - buf_base;
	if (buf_base == 0) end_offset = 2;
	newbase = allocator.realloc(buf_base, (end_offset *= 2));
	buf_base = newbase;
	buf_dend = newbase + dend_offset;
	buf_end = newbase + end_offset;
}

template <typename T, typename Alloc>
void Array<T, Alloc>::swap(Array &a) {
	Algorithm::swap(buf_base, a.buf_base);
	Algorithm::swap(buf_dend, a.buf_dend);
	Algorithm::swap(buf_end, a.buf_end);
}

template <typename T, typename Alloc>
Array<T, Alloc>::Array(size_t n) : allocator(), buf_base(), buf_dend(), buf_end() {
	buf_base = allocator.alloc(n);
	allocator.construct_range(buf_base, n);
	buf_dend = buf_base + n;
	buf_end = buf_dend;
}

template <typename T, typename Alloc>
template <size_t N>
Array<T, Alloc>::Array(const value_t (&lst)[N]) : allocator(), buf_base(), buf_dend(), buf_end() {
	ptr_t p, lst_p;
	buf_base = allocator.alloc(N);
	buf_dend = buf_base + N;
	buf_end = buf_dend;
	lst_p = (ptr_t)lst;
	for (p = buf_base; p != buf_dend; ++p, ++lst_p) {
		allocator.construct(p, *lst_p);
	}
}

template <typename T, typename Alloc>
template <typename InputIter>
Array<T, Alloc>::Array(typename Const<InputIter>::type p, size_t n) : allocator(), buf_base(), buf_dend(), buf_end() {
	this->set(p, n);
}

template <typename T, typename Alloc>
Array<T, Alloc>::Array(typename Const<ptr_t>::type p, size_t n) : allocator(), buf_base(), buf_dend(), buf_end() {
	this->set(p, n);
}

template <typename T, typename Alloc>
Array<T, Alloc>::~Array() {
	if (buf_base != ptr_t()) {
		allocator.destroy_range(buf_base, buf_dend - buf_base);
		allocator.free(buf_base);
	}
}

template <typename T, typename Alloc>
template <typename InputIter>
void Array<T, Alloc>::set(typename Const<InputIter>::type p, size_t n) {
	ptr_t ptr, old_dend;
	size_t i;
	if (buf_base == ptr_t()) {
		buf_base = allocator.alloc(n);
		buf_dend = buf_base + n;
		buf_end = buf_dend;
		for (ptr = buf_base; ptr != buf_dend; ++ptr) {
			allocator.construct(ptr, *p++);
		}
	} else {
		while (buf_base + n > buf_end) double_capacity();
		i = 0;
		for (ptr = buf_base; ptr != buf_dend; ++ptr) {
			if (i++ == n) break;
			*ptr = *p++;
		}
		for (; i < n; ++i) {
			allocator.construct(ptr++, *p++);
		}
		old_dend = buf_dend;
		buf_dend = buf_base + n;	
		if (buf_dend < old_dend) {
			allocator.destroy_range(buf_dend, old_dend - buf_dend);
		}
	}
}

template <typename T, typename Alloc>
void Array<T, Alloc>::set(typename Const<ptr_t>::type p, size_t n) {
	this->set<typename Const<ptr_t>::type>(p, n);
}

template <typename T, typename Alloc>
typename Array<T, Alloc>::value_t Array<T, Alloc>::pop() {
	if (this->count() == 0) throw Enodata();
	value_t tmp(*--buf_dend);
	allocator.destroy(buf_dend);
	return tmp;
}

template <typename T, typename Alloc>
size_t Array<T, Alloc>::push(typename Const<ref_t>::type val) {
	if (buf_dend == buf_end) double_capacity();
	allocator.construct(buf_dend++, val);
	return buf_dend - buf_base;
}

template <typename T, typename Alloc>
void Array<T, Alloc>::reserve(size_t n) {
	ptr_t newbase;
	ptrdiff_t dend_offset;
	dend_offset = buf_dend - buf_base;
	newbase = allocator.realloc(buf_base, n);
	buf_base = newbase;
	buf_dend = newbase + dend_offset;
	buf_end = newbase + n;
}

template <typename T, typename Alloc>
void Array<T, Alloc>::resize(size_t n, typename Const<ref_t>::type val) {
	ptr_t old_dend;
	if (n == buf_dend - buf_base) return;
	while (buf_base + n > buf_end) double_capacity();
	old_dend = buf_dend;
	buf_dend = buf_base + n;
	if (old_dend < buf_dend) {
		for (; old_dend != buf_dend; ++old_dend) {
			allocator.construct(old_dend, val);
		}
	} else {
		for (; old_dend != buf_dend; --old_dend) {
			allocator.destroy(old_dend);
		}
	}
}

template <typename T, typename Alloc>
Array<T, Alloc>& Array<T, Alloc>::operator = (const Array &a) {
	this->set(a.buf_base, a.count());
}

template <typename T, typename Alloc>
typename Array<T, Alloc>::ref_t Array<T, Alloc>::operator [](ssize_t i) {
	if (this->count() == 0) throw Enodata();
	if ((i > 0 ? i : -i - 1) >= buf_dend - buf_base) throw Erange();
	if (i < 0) return *(buf_dend + i);
	return buf_base[i];	
}

template <typename T, typename Alloc>
typename Const<typename Array<T, Alloc>::ref_t>::type Array<T, Alloc>::operator [](ssize_t i) const {
	if (this->count() == 0) throw Enodata();
	if ((i > 0 ? i : -i - 1) >= buf_dend - buf_base) throw Erange();
	if (i < 0) return *(buf_dend + i);
	return buf_base[i];
}

template <typename T, typename Alloc>
typename Array<T, Alloc>::value_t Array<T, Alloc>::shift() {
	size_t c = this->count();
	if (c == 0) throw Enodata();
	value_t tmp(*buf_base);
	allocator.destroy(buf_base);
	Algorithm::move(buf_base, buf_base + 1, c - 1);
	allocator.destroy(buf_dend--);
	return tmp;
}

template <typename T, typename Alloc>
size_t Array<T, Alloc>::unshift(typename Const<ref_t>::type val) {
	if (buf_dend == buf_end) double_capacity();
	allocator.construct(buf_dend, *(buf_dend - 1));
	Algorithm::move(buf_base + 1, buf_base, this->count() - 1);
	*buf_base = val;
	return ++buf_dend - buf_base;
}

template <typename T, typename Alloc>
size_t Array<T, Alloc>::insert(ssize_t index, typename Const<ref_t>::type val) {
	ptr_t ptr;
	if (buf_dend == buf_end) double_capacity();
	if (index < 0) ptr = buf_dend - index;
	else ptr = buf_base + index;
	if (ptr == buf_dend) {
		allocator.construct(ptr, val);
		return ++buf_dend - buf_base;
	}
	allocator.construct(buf_dend, *(buf_dend - 1));
	Algorithm::move(ptr + 1, ptr, buf_dend - ptr - 1);
	*ptr = val;
	return ++buf_dend - buf_base;
}

template <typename T, typename Alloc>
void Array<T, Alloc>::remove(ssize_t index, size_t n) {
	ptr_t p;
	if (this->count() < n) throw Erange();
	if (index < 0) p = buf_dend - index + n;
	else p = buf_base + index + n;
	if (p < buf_dend) Algorithm::move(p - n, p, buf_dend - p);
	buf_dend -= n;
	allocator.destroy_range(buf_dend, n);
}

template <typename T, typename Alloc>
Array<T, Alloc> Array<T, Alloc>::slice(ssize_t start, ssize_t length) const {
	size_t c, real_start;
	c = this->count();
	if (buf_base + end >= buf_dend) throw Erange();
	if (start < 0) real_start = c + start;
	else real_start = start;
	return Array(buf_base + real_start, length);
}

template <typename T, typename Alloc>
Array<T, Alloc> Array<T, Alloc>::splice(ssize_t start, size_t length, const Array &a) const {
	Array tmp;
	ptr_t src, dst;
	size_t i, c, real_start;
	c = this->count();
	if (buf_base + start + length >= buf_dend) throw Erange();
	if (start < 0) real_start = c + start;
	else real_start = start;
	tmp.reserve(c - length + a.count());
	src = buf_base;
	dst = tmp.buf_base;
	c = a.count();
	for (i = 0; i != real_start; ++i) {
		allocator.construct(dst++, *src++);
	}
	dst = tmp.buf_base + real_start + c;
	src = buf_base + real_start + length;
	while (dst != tmp.buf_end) allocator.construct(dst++, *src++);
	src = a.buf_base;
	dst = tmp.buf_base + real_start;
	for (i = 0; i != c; ++i) allocator.construct(dst++, *src++);
	tmp.buf_dend = tmp.buf_end;
	return tmp;
}

template <typename T, typename Alloc>
void Array<T, Alloc>::fill(ssize_t start, size_t n, typename Const<ref_t>::type val) {
	size_t real_start;
	ptr_t insert_point, src, dst;
	if (buf_base + start > buf_dend) throw Erange();
	if (start < 0) real_start = this->count() + start;
	else real_start = start;
	while (buf_dend + n > buf_end) double_capacity();
	insert_point = buf_base + real_start;
	src = buf_dend - 1;
	dst = buf_dend + n - 1;
	if (insert_point == buf_dend) {
		allocator.construct_range(buf_dend, val, n);
		buf_dend += n;
		return;
	}
	while (dst >= buf_dend) {
		allocator.construct(dst--, *src--);
	}
	while (src >= insert_point) {
		*dst-- = *src--;
	}
	for (dst = insert_point + n; insert_point != dst; ++insert_point) {
		*insert_point = val;
	}
	buf_dend += n;
	
}

template <typename T, typename Alloc>
ssize_t Array<T, Alloc>::find(typename Const<ref_t>::type val) const {
	if (this->count() == 0) return -1;
	ptr_t p = Algorithm::find(buf_base, val, buf_dend - buf_base);
	if (p == ptr_t()) return -1;
	return p - buf_base;
}

template <typename T, typename Alloc>
ssize_t Array<T, Alloc>::rfind(typename Const<ref_t>::type val) const {
	if (this->count() == 0) return -1;
	ptr_t p = Algorithm::rfind(buf_dend, val, buf_dend - buf_base);
	if (p == ptr_t()) return -1;
	return p - buf_base;
}

template <typename T, typename Alloc>
typename Array<T, Alloc>::Iterator Array<T, Alloc>::from(ssize_t index) {
	ptr_t p;
	if (buf_base == ptr_t()) throw Erange();
	if (index < 0) p = buf_dend + index;
	else p = buf_base + index;
	if (p >= buf_dend) throw Erange();
	return p;
}

template <typename T, typename Alloc>
typename Const<typename Array<T, Alloc>::Iterator>::type Array<T, Alloc>::from(ssize_t index) const {
	ptr_t p;
	if (buf_base == ptr_t()) throw Erange();
	if (index < 0) p = buf_dend + index;
	else p = buf_base + index;
	if (p >= buf_dend) throw Erange();
	return p;
}
