struct node {
    int prior, cnt, val;
    node *l, *r;
    node() {
        prior = rand() * rand();
        l = NULL, r = NULL;
        cnt = 1;
    }
    node(int _val) {
        prior = rand() * rand();
        l = NULL, r = NULL;
        cnt = 1;
        val = _val;
    }
};

node *tree = NULL;

int getcnt(node *T) {
    return T ? T->cnt : 0;
}

void recalc(node *&t) {
    if (!t) return;
    t->cnt = getcnt(t->l) + 1 + getcnt(t->r);
}

pair<node*, node*> split(node *tree, int k) {
    if (!tree) return{ NULL, NULL };
    if (getcnt(tree->l) >= k) {
        auto p = split(tree->l, k);
        tree->l = p.second;
        
        recalc(tree->l);
        recalc(tree);

        return{ p.first, tree };
    }
        auto p = split(tree->r, k - getcnt(tree->l) - 1);
        tree->r = p.first;
        
        recalc(tree->r);
        recalc(tree);
        
        return{ tree, p.second };
}

node *merge(node* l, node *r) {
    if (!l || !r)
        return !l ? r : l;
    if (l->prior > r->prior) {
        l->r = merge(l->r, r);
        recalc(l->r);
        recalc(l);
        return l;
    }
    r->l = merge(l, r->l);
    recalc(r->l);
    recalc(r);
    return r;
}

void print(node* root) {
    if (!root) {
        return;
    }
    print(root->l);
    cout << root->val + 1 << " ";
    print(root->r);
}

node *forward(node* tree, int l, int r) {
    auto p = split(tree, l - 1);
    auto p1 = split(p.second, r - l + 1);
    return merge(merge(p1.first, p.first), p1.second);
}
