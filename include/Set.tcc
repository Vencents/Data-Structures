
template <typename T, typename Container>
bool Set<T, Container>::exists(const Set &s) const {
	Iterator it, end = s.end();
	for (it = s.begin(); it != end; ++it)
		if (!c.exists(*it)) { return false; }
	return true;
}

template <typename T, typename Container>
void Set<T, Container>::insert(const Set &s) {
	Iterator it, end = s.end();
	for (it = s.begin(); it != end; ++it)
		c.insert(*it);
}

template <typename T, typename Container>
void Set<T, Container>::remove(const Set &s) {
	Iterator it, end = s.end();
	for (it = s.begin(); it != end; ++it) {
		try { c.remove(*it); } catch(Exception &e) {}
	}
}

