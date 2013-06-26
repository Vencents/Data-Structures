template <typename Key, typename Hashfunc, typename Alloc>
void Hashtable<Key, Hashfunc, Alloc>::rehash(size_t newtablesize) {
	table_t newtable(newtablesize);
	typename table_t::Iterator it, end;
	typename bucket_t::Iterator b_it, b_end;
	size_t hash;

	end = table.end();
	for (it = table.begin(); it != end; ++it) {
		if (it->count()) {
			b_end = it->end();
			for (b_it = it->begin(); b_it != b_end; ++b_it) {
				hash = hasher(*b_it) % newtablesize;
				newtable[hash].push(*b_it);
			}
		}
	}
	newtable.move(table);
}

template <typename Key, typename Hashfunc, typename Alloc>
void Hashtable<Key, Hashfunc, Alloc>::insert(const key_t &k) {
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
		if (*it == k) *it = k;
	}
	bucket->push(k);
	++_count;
}

template <typename Key, typename Hashfunc, typename Alloc>
void Hashtable<Key, Hashfunc, Alloc>::remove(const key_t &k) {
	size_t hash;
	bucket_t *bucket;
	typename bucket_t::Iterator it, end;
	
	hash = hasher(k) % table.count();
	bucket = &table[hash];
	if (bucket->count() == 0) throw Erange();
	end = bucket->end();
	for (it = bucket->begin(); it != end; ++it) {
		if (*it == k) {
			bucket->remove(it - bucket->begin(), 1);
			--_count;
			return;
		}
	}		
	throw Erange();
}

template <typename Key, typename Hashfunc, typename Alloc>
bool Hashtable<Key, Hashfunc, Alloc>::exists(const key_t &k) const {
	size_t hash;
	typename Const<bucket_t *>::type bucket;
	typename Const<typename bucket_t::Iterator>::type it, end;

	hash = hasher(k) % table.count();
	bucket = &table[hash];
	if (bucket->count() == 0) return false;
	end = bucket->end();
	for (it = bucket->begin(); it != end; ++it) {
		if (*it == k) return true;
	}
	return false;
}

template <typename Key, typename Hashfunc, typename Alloc>
void Hashtable<Key, Hashfunc, Alloc>::clear() {
	typename table_t::Iterator it, end;
	end = table.end();
	for (it = table.begin(); it != end; ++it) {
		it->clear();
	}
	_count = 0;
}

template <typename Key, typename Hashfunc, typename Alloc>
void Hashtable<Key, Hashfunc, Alloc>::move(Hashtable &h) {
	table.move(h.table);
	h._count = _count;	
}

template <typename Key, typename Hashfunc, typename Alloc>
void Hashtable<Key, Hashfunc, Alloc>::swap(Hashtable &h) {
	table_t tmp;
	table.move(tmp);
	h.table.move(table);
	tmp.move(h.table);
	Algorithm::swap(_count, h._count);
}

template <typename Key, typename Hashfunc, typename Alloc>
typename Hashtable<Key, Hashfunc, Alloc>::Iterator Hashtable<Key, Hashfunc, Alloc>::begin() const {
	size_t tpos = 0, count = table.count();
	for (; tpos != count; ++tpos) {
		if (table[tpos].count()) {
			return Iterator(table, tpos, 0);
		}
	}
	throw Enodata();
}

template <typename Key, typename Hashfunc, typename Alloc>
typename Hashtable<Key, Hashfunc, Alloc>::Iterator Hashtable<Key, Hashfunc, Alloc>::end() const {
	return Iterator();
}


template <typename Key, typename Hashfunc, typename Alloc>
const Hashtable_Iterator<Key, Hashfunc, Alloc> &Hashtable_Iterator<Key, Hashfunc, Alloc>::operator ++ () const {
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

template <typename Key, typename Hashfunc, typename Alloc>
const Hashtable_Iterator<Key, Hashfunc, Alloc> &Hashtable_Iterator<Key, Hashfunc, Alloc>::operator -- () const {
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


