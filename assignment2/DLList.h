/*
 * DLList.h
 *
 *  Created on: 2011-11-24
 *      Author: morin
 */

#ifndef DLLIST_H_
#define DLLIST_H_

using namespace std;

namespace ods {

template<class T>
class DLList {
protected:
	struct Node {
		T x;
		Node *prev, *next;
	};
	Node dummy;
	int n;
	void remove(Node *w);
	Node* addBefore(Node *w, T x);
	Node* getNode(int i);
public:
	DLList();
	virtual ~DLList();
	int size() { return n; }
	T get(int i);
	T set(int i, T x);
	virtual void add(int i, T x);
	virtual void add(T x) { add(size(), x); }
	virtual T remove(int i);
	virtual void clear();
	//My new methods
	virtual bool isPalindrome();
	virtual void rotate(int r);
	virtual void absorb(DLList<T> &l2);
	virtual void deal(DLList<T> &l2);
};

template<class T>
DLList<T>::DLList() {
	dummy.next = &dummy;
	dummy.prev = &dummy;
	n = 0;
}

template<class T>
typename DLList<T>::Node* DLList<T>::addBefore(Node *w, T x) {
	Node *u = new Node;
	u->x = x;
	u->prev = w->prev;
	u->next = w;
	u->next->prev = u;
	u->prev->next = u;
	n++;
	return u;
}

template<class T>
typename DLList<T>::Node* DLList<T>::getNode(int i) {
	Node* p;
	if (i < n / 2) {
		p = dummy.next;
		for (int j = 0; j < i; j++)
			p = p->next;
	} else {
		p = &dummy;
		for (int j = n; j > i; j--)
			p = p->prev;
	}
	return (p);
}


template<class T>
DLList<T>::~DLList() {
	clear();
}

template<class T>
void DLList<T>::clear() {
	Node *u = dummy.next;
	while (u != &dummy) {
		Node *w = u->next;
		delete u;
		u = w;
	}
	n = 0;
}



template<class T>
void DLList<T>::remove(Node *w) {
	w->prev->next = w->next;
	w->next->prev = w->prev;
	delete w;
	n--;
}


template<class T>
T DLList<T>::get(int i) {
	return getNode(i)->x;
}

template<class T>
T DLList<T>::set(int i, T x) {
	Node* u = getNode(i);
	T y = u->x;
	u->x = x;
	return y;
}

template<class T>
void DLList<T>::add(int i, T x) {
	addBefore(getNode(i), x);
}

template<class T>
T DLList<T>::remove(int i) {
	Node *w = getNode(i);
	T x = w->x;
	remove(w);
	return x;
}

template<class T>
bool DLList<T>::isPalindrome() {
	Node* temp1 = dummy.next;
	Node* temp2 = dummy.prev;
	for (int i = 0; i < n/2; i++) {
		if (temp1->x != temp2->x) {
			return false;
		}
		temp1 = temp1->next;
		temp2 = temp2->prev;
	}
	return true;
}

template<class T>
void DLList<T>::rotate(int r) {
	if (r <= 0) {
	}
	else {
		Node* w = getNode(r);
		Node* x = w->prev;
		Node* head = dummy.next;
		Node* tail = dummy.prev;
		dummy.next = w;
		dummy.prev = x;
		x->next = &dummy;
		w->prev = &dummy;
		head->prev = tail;
		tail->next = head;
	}
}

template<class T>
void DLList<T>::absorb(DLList<T> &l2) {
	Node* tail_l1 = dummy.prev;
	Node* head_l2 = l2.dummy.next;
	Node* tail_l2 = l2.dummy.prev;

	tail_l1->next = head_l2;
	head_l2->prev = tail_l1;
	dummy.prev = tail_l2;
	tail_l2->next = &dummy;

	n += l2.n;
	l2.n = 0;

	l2.dummy.next = &(l2.dummy);
	l2.dummy.prev = &(l2.dummy);
}

template<class T>
void DLList<T>::deal(DLList<T> &l2) {
	Node* node = dummy.next;
	Node* temp = dummy.next;
	int j = 0;
	for (int i = 0; i < n; i++) {
		temp = temp->next;
		if (i % n == 1) {
			node->prev->next = node->next;
			node->next->prev = node->prev;

			node->prev = l2.dummy.prev;

			l2.dummy.next->prev = node;
			l2.dummy.prev = node;

			node->next = &(l2.dummy);
			j++;
		}
		node = temp;
	}
	n = n - j;
	l2.n = l2.n + j;
}

} /* namespace ods */
#endif /* DLLIST_H_ */
