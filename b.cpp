#include <bits/extc++.h>
#define int long long

struct node {
    int val;
    bool f;

    node merge(node oth) const {
        node r = oth;
        r.val += val;
        return r;
    }

    node() {
        f = false;
    }
    node(int _val) {
        *this = node();
        val = _val;
    }
};

struct n2 {
    int first, second;
    n2() {}
};

struct segtree {
    std::vector<node> tree;
    std::vector<node> upd;
    std::vector<node> eq;
    node def = node(0);

    void build(std::vector<node> &arr, int l, int r, int v) {
        if (l == r - 1) {
            tree[v] = arr[l];
            return;
        }
        int m = l + (r - l) / 2;
        int v2 = v << 1;
        build(arr, l, m, v2 + 1);
        build(arr, m, r, v2 + 2);
        tree[v] = tree[v2 + 1].merge(tree[v2 + 2]);
    }

    void push(int l, int r, int v) {
        if (l == r - 1) {
            tree[v].val += upd[v].val;;
            upd[v] = def;

            if (eq[v].f) {
                tree[v] = node(eq[v].val);
                eq[v].f = false;
            }

        } else {
            int v2 = v << 1;
            tree[v].val += upd[v].val * (r - l);
            upd[v2 + 1].val += upd[v].val;
            upd[v2 + 2].val += upd[v].val;
            upd[v] = def;

            if (eq[v].f) {
                tree[v].val = eq[v].val * (r - l);
                eq[v2 + 1] = eq[v2 + 2] = eq[v];
                eq[v].f = false;
            }
        }
    }

    node get(int ql, int qr, int l, int r, int v) {
        if (ql >= r || qr <= l) {
            return def;
        }

        push(l, r, v);
        if (l >= ql && r <= qr) {
            return tree[v];
        }
        int m = l + (r - l) / 2;
        int v2 = v << 1;

        node ans = get(ql, qr, l, m, v2 + 1).merge(get(ql, qr, m, r, v2 + 2));
        tree[v] = tree[v2 + 1].merge(tree[v2 + 2]);
        return ans;
    }

    void update(int ql, int qr, node u, int l, int r, int v) {
        if (ql >= r || qr <= l) {
            return;
        }
        push(l, r, v);

        if (l >= ql && r <= qr) {
            upd[v].val += u.val;
            push(l, r, v);
            return;
        }

        int m = l + (r - l) / 2;
        int v2 = v << 1;
        update(ql, qr, u, l, m, v2 + 1);
        update(ql, qr, u, m, r, v2 + 2);
        tree[v] = tree[v2 + 1].merge(tree[v2 + 2]);
    }

    void eq_upd(int ql, int qr, node u, int l, int r, int v) {
        if (ql >= r || qr <= l) {
            return;
        }
        push(l, r, v);

        if (l >= ql && r <= qr) {
            eq[v] = u;
            eq[v].f = true;
            push(l, r, v);
            return;
        }

        int m = l + (r - l) / 2;
        int v2 = v << 1;
        eq_upd(ql, qr, u, l, m, v2 + 1);
        eq_upd(ql, qr, u, m, r, v2 + 2);
        tree[v] = tree[v2 + 1].merge(tree[v2 + 2]);
    }

    segtree(int n, std::vector<node> &arr) {
        tree.resize(n << 2);
        upd.resize(n << 2);
        eq.resize(n << 2);
        build(arr, 0, n, 0);
    }
};


signed main() {
    int n;
    std::cin >> n;
    std::vector<n2> v(n);
    for (int i = 0; i < n; i++) {
        std::cin >> v[i].first;
        v[i].second = i;
    }


    std::vector<node> l(n);
    std::vector<node> r(n);

    for (int i = 0; i < n; i++) {
        l[i].val = i + 1;
        r[i].val = n - i;
    }

    segtree sgl = segtree(n, l);
    segtree sgr = segtree(n, r);

    std::sort(v.begin(), v.end(), [](n2 a, n2 b) { return a.first < b.first; });
    int ans = 0;

    for (int i = 0; i < n; i++) {
        ans += sgr.get(v[i].second, v[i].second + 1, 0, n, 0).val * v[i].first;
        sgl.update(v[i].second, n, node(-1), 0, n, 0);

        ans += sgl.get(v[i].second, v[i].second + 1, 0, n, 0).val * v[i].first;
        sgl.update(0, v[i].second + 1, node(-1), 0, n, 0);

        sgr.eq_upd(v[i].second, v[i].second + 1, node(0), 0, n, 0);
        sgl.eq_upd(v[i].second, v[i].second + 1, node(0), 0, n, 0);
    }

    std::cout << ans << '\n';
    return 0;
}
