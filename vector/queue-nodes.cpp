#include <iostream>
#include <cstdio>
#include <cassert>
using namespace std;

int solve();

int main() {
	ios_base::sync_with_stdio(0);
#ifdef home
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else 
	cin.tie(0);
	cout.tie(0);
#endif
	solve();
	return 0;
}
	

template <class T>
struct node {
	node *p;
	T t;

	node() {
		p = NULL;
		t = 0;
	}
};

template <class T>
struct vector {
	node<T> *e;
	size_t sz;

	vector() {
		sz = 0;
		e = new node<T>;
	}

	void push_back(T x) {
		node<T> *n = new node<T>;
		n->t = x;
		n->p = e;
		e = n;

		sz++;
	}

	void pop_back() {
		e = e->p;
		sz--;
	}

	T back() {
		return e->t;
	}

	bool empty() {
		return sz == 0;
	}

	size_t size() {
		return sz;
	}
};

template <class T> 
struct queue {
	vector<T> vb, ve;

	void push_back(T x) {
		ve.push_back(x);
	}

	T pop_front() {
		if (vb.empty()) {
			while (!ve.empty()) {
				vb.push_back(ve.back());
				ve.pop_back();
			}
		}
		T x = vb.back();
		vb.pop_back();
		return x;
	}
};

int solve() {
	int m; 
	cin >> m;
	queue<int> q;
	for (int i = 0; i < m; i++) {
		char c; int x;
		cin >> c;
		if (c == '+') {
			cin >> x;
			q.push_back(x);
		}
		if (c == '-') cout << q.pop_front() << '\n';
	}
	return 0;
}