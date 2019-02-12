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
struct vector {
	T *V;
	int len, mem;
	vector() {
		V = new T[1];
		len = 0, mem = 1;
	}

	~vector() {
		delete V;
	}

	T &operator[] (int ind) {
		assert(0 <= ind && ind < len);
		return V[ind];
	}

	int size() {
		return len;
	}

	T back() {
		assert(len > 0);
		return V[len - 1];
	}

	void push(T x) {
		if (mem <= len + 1) {
			T *v = new T[len];
			for (int i = 0; i < len; i++) v[i] = V[i];
			delete V;
			V = new T[mem * 2];
			for (int i = 0; i < len; i++) V[i] = v[i];
			delete v;

			mem = mem * 2;
		}
		V[len++] = x;
	}

	void pop() {
		len--;
		if (len + 1 <= mem / 4) {
			T *v = new T[len];
			for (int i = 0; i < len; i++) v[i] = V[i];
			delete V;

			V = new T[mem / 2];
			for (int i = 0; i < len; i++) V[i] = v[i];
			delete v;

			mem = mem / 2;
		}
	}
};

int solve() {
	int m; 
	cin >> m;
	vector<long long> v;
	for (int i = 0; i < m; i++) {
		char c; int x;
		cin >> c;
		if (c == '+') {
			cin >> x;
			v.push(x);
		}
		if (c == '-') cout << v.back() << '\n', v.pop();
	}
	return 0;
}