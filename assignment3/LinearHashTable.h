/*
 * LinearHashTable.h
 *
 *  Created on: 2011-12-16
 *      Author: morin
 */

#ifndef LINEARHASHTABLE_H_
#define LINEARHASHTABLE_H_
#include <climits>
#include <iostream>
using namespace std;
#include "array.h"
namespace ods {

extern unsigned int tab[4][256];

template<class T>
class LinearHashTable {

	static const int w = 32;
	static const int r = 8;
	array<T> t;
	array<T> u;
	int n;   // number of values in T
	int q;   // number of non-null entries in T
	int d;   // t.length = 2^d
	T null, del;
	void resize();
	int hash(T x) {
		return (unsigned) x*3 % (1 << d);
	}
	int hash2(T x) {
		return 1 + hash(x) % ((1 << d) - 1);
	}
	int BackingSize();


public:
	// FIXME: get rid of default constructor
	LinearHashTable();
	LinearHashTable(T null, T del);
	virtual ~LinearHashTable();
	bool add(T x);
	bool addSlow(T x);
	T remove(T x);
	T find(T x);
	int size() { return n; }
	void clear();
	// FIXME: yuck
	void setNull(T null) { this->null = null; t.fill(null); }
	void setDel(T del) { this->del = del; }
};


/**
 * FIXME: Dangerous - leaves null and del uninitialized
 */
template<class T>
LinearHashTable<T>::LinearHashTable() : t(2), u(2) {
/*
	this->null = null;
	this->del = del;
*/
	n = 0;
	q = 0;
	d = 1;
}


template<class T>
LinearHashTable<T>::LinearHashTable(T null, T del) : t(2, null), u(2, null) {
	this->null = null;
	this->del = del;
	n = 0;
	q = 0;
	d = 1;
}


template<class T>
LinearHashTable<T>::~LinearHashTable() {
}


/*
template<class T>
void LinearHashTable<T>::resize() {
	d = 1;
	while ((1<<d) < 3*n) d++;
	array<T> tnew(1<<d, null);
	q = n;
	// insert everything into tnew
	for (int k = 0; k < t.length; k++) {
		if (t[k] != null && t[k] != del) {
			int i = 0;
			int probe = hash(t[k]);
			while (tnew[probe] != null) {
				i = (i == tnew.length-1) ? 0 : i + 1; // increment i
				probe = abs(hash(t[k]) + i*hash2(t[k])) % (1 << d);
			}
			tnew[probe] = t[k];
		}
	}
	t = tnew;
}
*/


template<class T>
void LinearHashTable<T>::resize() {
	d = 1;
	while ((1 << d) < 3*n) d++;
	array<T> tnew(1 << d, null);
	array<T> unew(1 << d, null);
	q = n;
	// insert everything into tnew
	for (int k = 0; k < t.length; k++) {
		if (t[k] != null && t[k] != del) {
			int probe = 0;
			for (int i = 0; i < tnew.length; i++) {
				probe = abs(hash(t[k]) + i*hash2(t[k])) % (1 << d);
				tnew[probe] = t[k];
			}
		}
	}
	t = tnew;
	// insert everything into unew
	for (int k = 0; k < u.length; k++) {
		if (u[k] != null && u[k] != del) {
			int probe = 0;
			for (int i = 0; i < unew.length; i++) {
				probe = abs(hash(u[k]) + i*hash2(u[k])) % (1 << d);
				unew[probe] = u[k];
			}
		}
	}
	u = unew;
}


template<class T>
void LinearHashTable<T>::clear() {
	n = 0;
	q = 0;
	d = 1;
	array<T> tnew(2, null);
	t = tnew;
	array<T> unew(2, null);
	u = unew;
}


/*
template<class T>
bool LinearHashTable<T>::add(T x) {
	if (find(x) != null) return false;
	if (2*(q+1) > t.length) resize();   // max 50% occupancy
	int i = 0;
	int probe = hash(x);
	while (t[probe] != null && t[probe] != del) {
		i = (i == t.length-1) ? 0 : i + 1; // increment i
		probe = abs(hash(x) + i*hash2(x)) % (1 << d);
	}
	if (t[probe] == null) q++;
	n++;
	t[probe] = x;
	return true;
}
*/


template<class T>
bool LinearHashTable<T>::add(T x) {
	if (find(x) != null) return false;
	if (2*(q + 1) > BackingSize()) resize(); // max 50% occupancy
	int probe = 0;
	for (int i = 0; i < BackingSize(); i++) {
		probe = abs((hash(x) + i*hash2(x)) % (1 << d));
		if (probe < t.length) {
			if (t[probe] == null || t[probe] == del) {
				t[probe] = x;
				n++;
				q++;
				return true;
			}
		}
		else {
			if (u[probe - t.length] == null || u[probe - t.length] == del) {
				u[probe - t.length] = x;
				n++;
				q++;
				return true;
			}
		}
	}
	return false;
}


/*
template<class T>
T LinearHashTable<T>::find(T x) {
	int i = 0;
	int probe = hash(x);
	while (t[probe] != null) {
		if (t[probe] != del && t[probe] == x) return t[probe];
		i = (i == t.length-1) ? 0 : i + 1; // increment i
		probe = abs(hash(x) + i*hash2(x)) % (1 << d);
	}
	return null;
}
*/


template<class T>
T LinearHashTable<T>::find(T x) {
	int probe = 0;
	for (int i = 0; i < BackingSize(); i++) {
		probe = abs((hash(x) + i*hash2(x)) % (1 << d));
		if (probe < t.length) {
			if (t[probe] == null) {
				return null;
			}
			if (t[probe] != del && t[probe] == x) {
				return t[probe];
			}
		}
		else {
			if (u[probe - t.length] == null) {
				return null;
			}
			if (u[probe - t.length] != del && u[probe - t.length] == x) {
				return u[probe - t.length];
			}
		}
	}
	return null;
}


/*
template<class T>
T LinearHashTable<T>::remove(T x) {
	int i = 0;
	int probe = hash(x);
	while (t[probe] != null) {
		T y = t[probe];
		if (y != del && x == y) {
			t[probe] = del;
			n--;
			if (8*n < t.length) resize(); // min 12.5% occupancy
			return y;
		}
		i = (i == t.length-1) ? 0 : i + 1;  // increment i
		probe = abs(hash(x) + i*hash2(x)) % (1 << d);
	}
	return null;
}
*/


template<class T>
T LinearHashTable<T>::remove(T x) {
	int probe = 0;
	for (int i = 0; i < BackingSize(); i++) {
		probe = abs(hash(x) + i*hash2(x)) % (1 << d);
		if (probe < t.length) {
			T y = t[probe];
			if (y == null) {
				return null;
			}
			if (y != del && x == y) {
				t[probe] = del;
				n--;
				q--;
				if (8*n < BackingSize())
					resize();
				return y;
			}
		}
		else {
			T y = u[probe - t.length];
			if (y == null) {
				return null;
			}
			if (y != del && x == y) {
				u[probe - t.length] = del;
				n--;
				q--;
				if (8*n < BackingSize())
					resize();
				return y;
			}
		}
	}
	return null;
}


/*
template<class T>
bool LinearHashTable<T>::addSlow(T x) {
	if (2*(q+1) > t.length) resize();   // max 50% occupancy
	int i = 0;
	int probe = hash(x);
	while (t[probe] != null) {
			if (t[probe] != del && x.equals(t[probe])) return false;
			i = (i == t.length-1) ? 0 : i + 1; // increment i
			probe = abs(hash(x) + i*hash2(x)) % (1 << d);
	}
	t[probe] = x;
	n++; q++;
	return true;
}
*/


template<class T>
bool LinearHashTable<T>::addSlow(T x) {
	if (2*(q + 1) > BackingSize())
		resize();
	int probe = 0;
	for (int i = 0; i < BackingSize(); i++) {
		probe = abs(hash(x) + i*hash2(x)) % (1 << d);
		if (probe < t.length) {
			if (t[probe] != del && x.equals(t[probe])) {
				return false;
			}
			t[probe] = x;
			n++;
			q++;
			return true;
		}
		else {
			if (u[probe - t.length] != del && x.equals(u[probe - t.length])) {
				return false;
			}
			u[probe - t.length] = x;
			n++;
			q++;
			return true;
		}
	}
	return false;
}


template<class T>
int LinearHashTable<T>::BackingSize() {
	return t.length + u.length;
}


} /* namespace ods */
#endif /* LINEARHASHTABLE_H_ */
