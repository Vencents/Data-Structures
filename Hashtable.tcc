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
	pair_t newpair;
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
	newpair.key = k;
	bucket->push(newpair);
	++_count;
	return bucket->operator [](-1).value;
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
bool Hashtable<Key, Val, Hashfunc, Alloc>::exists(const key_t &k) {
	size_t hash;
	bucket_t *bucket;
	typename bucket_t::Iterator it, end;

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

