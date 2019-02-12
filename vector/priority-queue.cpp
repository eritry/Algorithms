#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

#define TASK "priorityqueue2"
typedef long long ll;
const int INF = (int)1e9 + 23;
const ll LINF = (ll)1e18 + 23;

int solve();

int main() {
	ios_base::sync_with_stdio(0);
#ifdef home
	freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout);
#else
	cin.tie(0);
	cout.tie(0);
	freopen(TASK".in", "r", stdin), freopen(TASK".out", "w", stdout);
#endif
	solve();
	return 0;
}


struct heap {
	vector<pair<int, int>> h;
	vector<int> ind;

	heap() {
		h.resize(1);
		ind.resize(1);
	}

	void push(pair<int, int> p) {
		h.push_back(p);
		if ((int)ind.size() < p.second) {
			ind.resize(p.second + 1);
		}
		ind[p.second] = h.size() - 1;
		sift_up(h.size() - 1);

	}

	pair<int, int> extract_min() {
		swap(h[1], h.back());
		swap(ind[h[1].second], ind[h.back().second]);

		pair<int, int> p = h.back();
		h.pop_back();

		sift_down(1);

		return p;
	}

	void decrease_key(int i, int value) {
		if (i >= (int)ind.size()) return;
		h[ind[i]].first = value;
		sift_up(ind[i]);
		sift_down(ind[i]);
	}

	void sift_up(int i) {
		while (i > 1) {
			if (h[i / 2] > h[i]) {
				swap(h[i / 2], h[i]); 
				swap(ind[h[i / 2].second], ind[h[i].second]);
			}
			i /= 2;
		}
	}

	void sift_down(int i) {
		while (2 * i < (int)h.size()) {
			int l = 2 * i, r = 2 * i + 1;
			int cur = l;
			if (r < (int)h.size() && h[r] < h[cur]) cur = r;

			if (h[i] <= h[cur]) break;

			swap(h[i], h[cur]);
			swap(ind[h[i].second], ind[h[cur].second]);

			i = cur;
		}
	}
} H;


int solve() {
	string s;
	int i = 0;
	while (cin >> s) {
		i++;
		if (s[0] == 'p') {
			int a; cin >> a;
			H.push({a, i});
		}
		if (s[0] == 'e') {
			if (H.h.size() == 1) cout << "*\n";
			else {
				auto p = H.extract_min();
			 	cout << p.first << ' ' << p.second << '\n';
			}
		}
		if (s[0] == 'd') {
			int x, v; cin >> x >> v;
			H.decrease_key(x, v);
		}
	}
	return 0;
}
