template <typename Key, typename Val, typename Hashfunc, typename Alloc>
void Hashtable<Key, Val, Hashfunc, Alloc>::rehash(size_t newtablesize) {
	table_t newtable(newtablesize);
	typename table_t::Iterator it, end;
	size_t hash;

	end = table.end();
	for (it = table.begin(); it != end; ++it) {
		if (it->count()) {
			hash = hasher(it->operator [](0).key) % newtablesize;
			it->move(newtable[hash]);
		}
	}
	newtable.move(table);
}

template <typename Key, typename Val, typename Hashfunc, typename Alloc>
typename Hashtable<Key, Val, Hashfunc, Alloc>::value_t &Hashtable<Key, Val, Hashfunc, Alloc>::operator [] (const key_t &k) {
	pair_t newpair;
	bucket_t *bucket;
	typename bucket_t::Iterator it, end;
	size_t hash;

	hash = hasher(k) % table.count();
	if (_count ? table.count() / _count < 3 : 0)
		rehash(table.count() * 3);
	bucket = &table[hash];
	end = bucket->end();
	for (it = bucket->begin(); it != end; ++it) {
		if (it->key == k) return it->value;
	}
	newpair.key = k;
	bucket->push(newpair);
	return bucket->operator [](-1).value;
}


template <typename Key, typename Val, typename Hashfunc, typename Alloc>
void Hashtable<Key, Val, Hashfunc, Alloc>::remove(const key_t &k) {
	size_t hash;
	bucket_t *bucket;
	typename bucket_t::Iterator it, end;
	
	hash = hasher(k) % table.count();
	bucket = &table[hash];
	if (bucket.count() == 0) throw Erange();
	end = bucket.end();
	for (it = bucket.begin(); it != end; ++it) {
		if (it->key == k) {
			bucket.remove(it - bucket.begin(), 1);
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
	if (bucket.count() == 0) return false;
	end = bucket.end();
	for (it = bucket.begin(); it != end; ++it) {
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
	table.clear();
}

