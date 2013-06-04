
template <size_t N, typename T>
Vector<N, T>::Vector(typename Const<ref_t>::type r, ...) {
	va_list v;
	va_start(v, r);
	a[0] = r;
	for (register size_t i = 1; i < N; ++i) a[i] = va_arg(v, value_t);	
	va_end(v);
}

template <size_t N, typename T>
Vector<N, T> Vector<N, T>::operator - (const Vector &v) const {
	Vector tmp(*this);
	for (register size_t i = 0; i < N; ++i)
		tmp[i] -= v[i];
	return tmp;
}

template <size_t N, typename T>
Vector<N, T> Vector<N, T>::operator + (const Vector &v) const {
	Vector tmp(*this);
	for (register size_t i = 0; i < N; ++i)
		tmp[i] += v[i];
	return tmp;
}

template <size_t N, typename T>
Vector<N, T> &Vector<N, T>::operator = (const Vector &v) {
	a = v.a;
	return *this;
}

template <size_t N, typename T>
Vector<N, T> Vector<N, T>::operator * (typename Const<ref_t>::type r) const {
	Vector tmp(*this);
	for (register size_t i = 0; i < N; ++i)
		tmp[i] *= r;
	return tmp;
}

template <size_t N, typename T>
Vector<N, T> &Vector<N, T>::operator -= (const Vector &v) {
	for (register size_t i = 0; i < N; ++i)
		a[i] -= v[i];
	return *this;
}

template <size_t N, typename T>
Vector<N, T> &Vector<N, T>::operator += (const Vector &v) {
	for (register size_t i = 0; i < N; ++i)
		a[i] += v[i];
	return *this;
}

template <size_t N, typename T>
Vector<N, T> &Vector<N, T>::operator *= (typename Const<ref_t>::type r) {
	for (register size_t i = 0; i < N; ++i)
		a[i] *= r;
	return *this;
}

template <size_t N, typename T>
Vector<N, T> Vector<N, T>::operator ~ () const {
	Vector tmp(*this);
	for (register size_t i = 0; i < N; ++i)
		a[i] = -a[i];
	return tmp;
}

template <size_t N, typename T>
void Vector<N, T>::Assign(typename Const<ref_t>::type r, ...) {
	va_list v;
	va_start(v, r);
	a[0] = r;
	for (register size_t i = 1; i < N; ++i) a[i] = va_arg(v, value_t);	
	va_end(v);
}

template <size_t N, typename T>
void Vector<N, T>::Clear() {
	for (register size_t i = 0; i < N; ++i)
		a[i] = value_t();
}

template <size_t N, typename T>
typename Vector<N, T>::value_t Vector<N, T>::DotProduct(const Vector &v) const {
	value_t result = value_t();
	for (register size_t i = 0; i < N; ++i)
		result += a[i]*v[i];
	return result;
}

template <size_t N, typename T>
void Vector<N, T>::Snap() {
	for (register size_t i = 0; i < N; ++i)
		a[i] = (int)a[i];
}

template <size_t N, typename T>
void Vector<N, T>::Normalize() {
	value_t len, ilen;
	len = this->Length();
	if (len != value_t()) {
		ilen = 1/len;
		for (register size_t i = 0; i < N; ++i)
			a[i] *= ilen;
	}
}

template <size_t N, typename T>
typename Vector<N, T>::value_t Vector<N, T>::Length() const {
	value_t result = value_t();
	for (register size_t i = 0; i < N; ++i)
		result += a[i]*a[i];
	return (value_t)sqrt(result);
}

template <size_t N, typename T>
typename Vector<N, T>::value_t Vector<N, T>::LengthSquared() const {
	value_t result;
	for (register size_t i = 0; i < N; ++i)
		result += a[i]*a[i];
	return result;
}

template <size_t N, typename T>
bool Vector<N, T>::operator == (const Vector &v) const {
	for (register size_t i = 0; i < N; ++i)
		if (a[i] != v[i]) return false;
	return true;
}

template <size_t N, typename T>
bool Vector<N, T>::operator != (const Vector &v) const {
	for (register size_t i = 0; i < N; ++i)
		if (a[i] != v[i]) return true;
	return false;
}
