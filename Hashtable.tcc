template <typename Key, typename Val, typename Hashfunc, typename Alloc>
void Hashtable<Key, Val, Hashfunc, Alloc>::rehash(size_t newtablesize) {
	table_t newtable(newtablesize);
	typename table_t::Iterator it, end;
	typename bucket_t::Iterator b_it, b_end;
	size_t hash;

	end = table.end();
	for (it = table.begin(); it != end; ++it) {
		if (it->count()) {
			b_end = it->end();
			for (b_it = it->begin(); b_it != b_end; ++b_it) {
				hash = hasher(b_it->key) % newtablesize;
				newtable[hash].push(*b_it);
			}
		}
	}
	newtable.move(table);
}

template <typename Key, typename Val, typename Hashfunc, typename Alloc>
typename Hashtable<Key, Val, Hashfunc, Alloc>::value_t &Hashtable<Key, Val, Hashfunc, Alloc>::operator [] (const key_t &k) {
	bucket_t *bucket;
	typename bucket_t::Iterator it, end;
	size_t hash, size;

	size = table.count();
	if ((long double)_count / size >= 0.77)
		rehash(size * 2);
	hash = hasher(k) % table.count();
	bucket = &table[hash];
	end = bucket->end();
	for (it = bucket->begin(); it != end; ++it) {
		if (it->key == k) return it->value;
	}
	pair_t newpair(k);
	bucket->push(newpair);
	++_count;
	return bucket->operator [](-1).value;
}

template <typename Key, typename Val, typename Hashfunc, typename Alloc>
typename Hashtable<Key, Val, Hashfunc, Alloc>::Iterator Hashtable<Key, Val, Hashfunc, Alloc>::from(const key_t &k) {
	size_t hash, bpos = 0;
	bucket_t *bucket;
	typename bucket_t::Iterator it, end;

	hash = hasher(k) % table.count();
	bucket = &table[hash];
	if (bucket->count() == 0) throw Erange();
	end = bucket->end();
	for (it = bucket->begin(); it != end; ++it, ++bpos) {
		if (it->key == k) return Hashtable_Iterator<Key, Val, Hashfunc, Alloc>(table, hash, bpos);	
	}
	throw Erange();
}

template <typename Key, typename Val, typename Hashfunc, typename Alloc>
typename Const<typename Hashtable<Key, Val, Hashfunc, Alloc>::Iterator>::type Hashtable<Key, Val, Hashfunc, Alloc>::from(const key_t &k) const {
	size_t hash, bpos = 0;
	bucket_t *bucket;
	typename bucket_t::Iterator it, end;

	hash = hasher(k) % table.count();
	bucket = &table[hash];
	if (bucket->count() == 0) throw Erange();
	end = bucket->end();
	for (it = bucket->begin(); it != end; ++it, ++bpos) {
		if (it->key == k) return Hashtable_Iterator<Key, Val, Hashfunc, Alloc>(table, hash, bpos);	
	}
	throw Erange();
}

template <typename Key, typename Val, typename Hashfunc, typename Alloc>
void Hashtable<Key, Val, Hashfunc, Alloc>::remove(const key_t &k) {
	size_t hash;
	bucket_t *bucket;
	typename bucket_t::Iterator it, end;
	
	hash = hasher(k) % table.count();
	bucket = &table[hash];
	if (bucket->count() == 0) throw Erange();
	end = bucket->end();
	for (it = bucket->begin(); it != end; ++it) {
		if (it->key == k) {
			bucket->remove(it - bucket->begin(), 1);
			--_count;
			break;
		}
	}		
}

template <typename Key, typename Val, typename Hashfunc, typename Alloc>
bool Hashtable<Key, Val, Hashfunc, Alloc>::contains(const key_t &k) const {
	size_t hash;
	typename Const<bucket_t *>::type bucket;
	typename Const<typename bucket_t::Iterator>::type it, end;

	hash = hasher(k) % table.count();
	bucket = &table[hash];
	if (bucket->count() == 0) return false;
	end = bucket->end();
	for (it = bucket->begin(); it != end; ++it) {
		if (it->key == k) return true;
	}
	return false;
}

template <typename Key, typename Val, typename Hashfunc, typename Alloc>
void Hashtable<Key, Val, Hashfunc, Alloc>::clear() {
	typename table_t::Iterator it, end;
	end = table.end();
	for (it = table.begin(); it != end; ++it) {
		it->clear();
	}
	_count = 0;
}

template <typename Key, typename Val, typename Hashfunc, typename Alloc>
void Hashtable<Key, Val, Hashfunc, Alloc>::move(Hashtable &h) {
	table.move(h.table);
	h._count = _count;	
}

template <typename Key, typename Val, typename Hashfunc, typename Alloc>
void Hashtable<Key, Val, Hashfunc, Alloc>::swap(Hashtable &h) {
	table_t tmp;
	table.move(tmp);
	h.table.move(table);
	tmp.move(h.table);
	Algorithm::swap(_count, h._count);
}

template <typename Key, typename Val, typename Hashfunc, typename Alloc>
typename Hashtable<Key, Val, Hashfunc, Alloc>::Iterator Hashtable<Key, Val, Hashfunc, Alloc>::remove(Iterator pos, size_t n) {
	size_t i, j, k;
	if (pos.table != &table) throw Einval();
	if (pos == this->end()) throw Erange();
	k = pos.table->count();
	for (i = 0; pos.tpos != k;) {
		j = pos.table->operator [](pos.tpos).count();
		if (j == 0) { ++pos.tpos; pos.bpos = 0; continue; }
		if (i == n) return pos;
		if (n - i < j) {
			pos.table->operator [](pos.tpos).remove(pos.bpos, n - i);
			return pos;
		} else {
			pos.table->operator [](pos.tpos).clear();
			i += j;
			++pos.tpos;
			pos.bpos = 0;
		} 
	}
	return Hashtable_Iterator<Key, Val, Hashfunc, Alloc>();
}

template <typename Key, typename Val, typename Hashfunc, typename Alloc>
typename Hashtable<Key, Val, Hashfunc, Alloc>::Iterator Hashtable<Key, Val, Hashfunc, Alloc>::begin() {
	size_t tpos = 0, count = table.count();
	for (; tpos != count; ++tpos) {
		if (table[tpos].count()) {
			return Hashtable_Iterator<Key, Val, Hashfunc, Alloc>(table, tpos, 0);
		}
	}
	throw Enodata();
}

template <typename Key, typename Val, typename Hashfunc, typename Alloc>
typename Hashtable<Key, Val, Hashfunc, Alloc>::Iterator Hashtable<Key, Val, Hashfunc, Alloc>::end() {
	return Hashtable_Iterator<Key, Val, Hashfunc, Alloc>();
}

template <typename Key, typename Val, typename Hashfunc, typename Alloc>
typename Const<typename Hashtable<Key, Val, Hashfunc, Alloc>::Iterator>::type Hashtable<Key, Val, Hashfunc, Alloc>::begin() const {
	size_t tpos = 0, count = table.count();
	for (; tpos != count; ++tpos) {
		if (table[tpos].count()) {
			return Hashtable_Iterator<Key, Val, Hashfunc, Alloc>(table, tpos, 0);
		}
	}
	throw Enodata();
}

template <typename Key, typename Val, typename Hashfunc, typename Alloc>
typename Const<typename Hashtable<Key, Val, Hashfunc, Alloc>::Iterator>::type Hashtable<Key, Val, Hashfunc, Alloc>::end() const {
	return Hashtable_Iterator<Key, Val, Hashfunc, Alloc>();
}


template <typename Key, typename Val, typename Hashfunc, typename Alloc>
const Hashtable_Iterator<Key, Val, Hashfunc, Alloc> &Hashtable_Iterator<Key, Val, Hashfunc, Alloc>::operator ++ () const {
	if (table == 0) throw Erange();
	if (bpos == table->operator [](tpos).count() - 1) {
		bpos = 0;
		for (++tpos; tpos != table->count(); ++tpos) {
			if (table->operator [](tpos).count()) {
				return *this;
			}
		}
		table = 0;
		tpos = 0;
		return *this;
	} else ++bpos;
	return *this;
}

template <typename Key, typename Val, typename Hashfunc, typename Alloc>
const Hashtable_Iterator<Key, Val, Hashfunc, Alloc> &Hashtable_Iterator<Key, Val, Hashfunc, Alloc>::operator -- () const {
	if (bpos == 0) {
		for (;;) {
			--tpos;
			if (tpos == 0 && table->operator [](tpos).count() == 0) {
				table = 0;
				tpos = 0;
				bpos = 0;
				return *this;
			}
			if (bpos = table->operator [](tpos).count()) {
				--bpos; return *this;
			}
		}
	} else --bpos;
	return *this;
}


