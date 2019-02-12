struct sTree {
    int n;
    vector<int> a, t, add;
    sTree(int _n) {
        n = _n;
        a.resize(2 * n);
        t.resize(4 * n); add.resize(4 * n);
    }

    void build(int v, int L, int R) {
        int mt = (L + R) >> 1, l = v << 1, r = l + 1;
        if (L == R) t[v] = a[L];
        else {
          build(l, L, mt); build(r, mt + 1, R);
          t[v] = t[l] + t[r];
        }
    }

    void update(int v, int lt, int rt, int pos, int val) {
        if (lt == pos && rt == pos) { t[v] += val;
        } else {
          int l = v << 1, r = l + 1, mt = (lt + rt) >> 1;
          if (pos <= mt) update(l, lt, mt, pos, val);
          else update(r, mt + 1, rt, pos, val);
          t[v] = t[l] + t[r];
        }
    }

    int ask(int v, int lt, int rt, int L, int R) {
        if (L > R) return 0;
        if (lt == L && rt == R) return t[v];
        int l = v << 1, r = l + 1, mt = (lt + rt) >> 1;
        return ask(l, lt, mt, L, min(R, mt)) + ask(r, mt + 1, rt, max(L, mt + 1), R);
    }
    
};
