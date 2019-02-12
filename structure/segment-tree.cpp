int tree[4 * MAXN], leave[MAXN], n, k;

void upd(int i, int mod) {
    int v = leave[i];
    tree[v] = mod;
    while (v) {
        v = (v - 1) / 2;
        tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
    }
}

int get(int v, int l, int r, int L, int R) {
    if (L <= l && R >= r) return tree[v];
    if (l > R || r < L) return 0;
    int m = (l + r) / 2;
    return get(2 * v + 1, l, m, L, R) + get(2 * v + 2, m + 1, r, L, R);
}

void build(int v, int l, int r) {
    tree[v] = r - l + 1;
    if (l == r) {
        leave[l] = v;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v + 1, l, m);
    build(2 * v + 2, m + 1, r);
}