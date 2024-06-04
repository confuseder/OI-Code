#include <bits/stdc++.h>
using namespace std;

int         n, q;
vector<int> mp[100005];

template <typename T>
class SegmentTree {
  private:
    int n;

    struct node {
        int   l, r;
        node *lc, *rc;
        T     val, lazy = -1;

        void push_down() {
            if (lazy == -1 || l == r) {
                return;
            }
            lc->val  = (lc->r - lc->l + 1) * lazy;
            lc->lazy = lazy;
            rc->val  = (rc->r - rc->l + 1) * lazy;
            rc->lazy = lazy;
            lazy     = -1;
        }

        void push_up() {
            val = lc->val + rc->val;
        }

        node() {}

        node(int _l, int _r, T _val)
            : l(_l), r(_r), val(_val) {}

        ~node() {
            delete lc;
            delete rc;
        }

    } *root;

    node *build(int l, int r) {

        if (l == r) {
            return new node(l, r, 0);
        }

        node *t = new node(l, r, 0);

        int mid = (l + r) / 2;
        t->lc   = build(l, mid);
        t->rc   = build(mid + 1, r);
        t->push_up();

        return t;
    }

  public:
    void build(int n) {
        this->root = build(1, n);
    }

    void modify(int l, int r, T val, node *p = nullptr) {

        if (p == nullptr) {
            p = root;
        }

        if (p->l >= l && p->r <= r) {
            p->val  = (p->r - p->l + 1) * val;
            p->lazy = val;
            return;
        }

        p->push_down();

        int mid = (p->l + p->r) / 2;
        if (l <= mid) {
            modify(l, r, val, p->lc);
        }
        if (r > mid) {
            modify(l, r, val, p->rc);
        }
        p->push_up();
    }

    T get(int l, int r, node *p = nullptr) {

        if (p == nullptr) {
            p = root;
        }

        if (p->l >= l && p->r <= r) {
            return p->val;
        }

        p->push_down();

        int mid = (p->l + p->r) / 2;
        T   sum = 0;
        if (l <= mid) {
            sum += get(l, r, p->lc);
        }
        if (r > mid) {
            sum += get(l, r, p->rc);
        }
        return sum;
    }
};

SegmentTree<int> tr;

int cnt;
int dep[100005];
int siz[100005];
int son[100005];
int fa[100005];
int top[100005];
int id[100005];

void init_1(int u, int f) {
    fa[u] = f, siz[u] = 1, dep[u] = dep[f] + 1;

    for (auto i : mp[u]) {
        if (i == f) {
            continue;
        }
        init_1(i, u);
        siz[u] += siz[i];
        if (siz[i] > siz[son[u]]) {
            son[u] = i;
        }
    }
}

void init_2(int u, int f) {
    top[u] = f;
    id[u]  = ++cnt;

    if (!son[u]) {
        return;
    }

    init_2(son[u], f);

    for (auto i : mp[u]) {
        if (i == son[u] || i == fa[u]) {
            continue;
        }
        init_2(i, i);
    }
}

void setPath(int u, int v, int k) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            swap(u, v);
        }
        tr.modify(id[top[u]], id[u], k);
        u = fa[top[u]];
    }

    if (dep[u] > dep[v]) { swap(u, v); }

    tr.modify(id[u], id[v], k);
}

void setSon(int u, int k) {
    tr.modify(id[u], id[u] + siz[u] - 1, k);
}

int main() {

    // freopen("P2146.in", "r", stdin);
    // freopen("P2146.out", "w", stdout);

    cin >> n;

    tr.build(n + 5);

    for (int i = 2; i <= n; i++) {
        int x;
        cin >> x;

        mp[x + 1].push_back(i);
        mp[i].push_back(x + 1);
    }

    init_1(1, 0);
    init_2(1, 1);

    cin >> q;

    for (int i = 1; i <= q; i++) {
        string op;
        int    x;
        cin >> op >> x;

        if (op == "install") {
            int a = tr.get(1, n + 5);
            setPath(x + 1, 1, 1);

            cout << tr.get(1, n + 5) - a << endl;
        } else if (op == "uninstall") {
            int a = tr.get(1, n + 5);
            setSon(x + 1, 0);

            cout << a - tr.get(1, n + 5) << endl;
        }
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}