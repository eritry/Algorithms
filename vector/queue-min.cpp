#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <cstring>
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
		V = (T*)malloc(sizeof(T));
		len = 0, mem = 1;
	}

	~vector() {
		free(V);
	}

	T &operator[] (int ind) {
		assert(0 <= ind && ind < len);
		return V[ind];
	}

	size_t size() {
		return len;
	}

	bool empty() {
		return len == 0;
	}

	T back() {
		assert(len > 0);
		return V[len - 1];
	}

	void push(T x) {
		if (mem <= len + 1) {
			T *v = (T*)malloc((mem * 2) * sizeof(T));
			memcpy(v, V, sizeof(T) * len);
			free(V);
			
			V = v;
			mem = mem * 2;
		}
		V[len++] = x;
	}

	void pop() {
		len--;
		if (len + 1 <= mem / 8) {
			T *v = (T*)malloc((mem / 2) * sizeof(T));
			memcpy(v, V, sizeof(T) * len);
			free(V);

			V = v;
			mem = mem / 2;
		}
	}
};

template <class T> 
struct queueMin {
	vector<pair<T, T>> vb, ve;

	void push(T x) {
		int minE = x;
		if (!ve.empty()) minE = min(minE, ve.back().second);
		ve.push({x, minE});	
	}

	void pop() {
		if (vb.empty()) {
			while (!ve.empty()) {
				int minE = ve.back().first;
				if (!vb.empty()) minE = min(minE, vb.back().second);
				vb.push({ve.back().first, minE});
				ve.pop();
			}
		}
		vb.pop();
	}

	int getMin() {
		int minE = (1ll << 31) - 1;
		if (!vb.empty()) minE = min(minE, vb.back().second);
		if (!ve.empty()) minE = min(minE, ve.back().second);
		return minE;
	}
};

int solve() {
	int n, m, k;
	cin >> n >> m >> k;

	int a, b, c; cin >> a >> b >> c;

	int *x = new int[3];
	queueMin<int> q;

	int i;
	long long ans = 0;
	for (i = 0; i < k; i++) { 
		x[0] = x[1];
		cin >> x[1];
		q.push(x[1]);
		if (i >= m - 1) {
			ans += q.getMin();
			q.pop();
		}
	}

	for (; i < n; i++) {
		x[2] = a * x[0] + b * x[1] + c;
		q.push(x[2]);
		if (i >= m - 1) {
			ans += q.getMin();
			q.pop();
		}
		x[0] = x[1];
		x[1] = x[2];
	}

	cout << ans;
	return 0;
}