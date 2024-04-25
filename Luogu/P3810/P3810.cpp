#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
using namespace std;

int n, k;

mt19937 rnd(random_device{}());

template <typename T>
class Treap {
  private:
    struct node {
        T     key;
        int   val, size;
        node *lc, *rc;

        node(const T& k, const int& v)
            : key(k), val(v), size(1), lc(nullptr), rc(nullptr) {}
    }* root;

    int sz(node* const& x) {
        return x ? x->size : 0;
    }

    void push_up(node* const& x) {
        x->size = 1 + sz(x->lc) + sz(x->rc);
    }

    node* merge(node* const& a, node* const& b) {
        if (!a || !b) return a ? a : b;
        if (a->val < b->val) {
            a->rc = merge(a->rc, b);
            push_up(a);
            return a;
        } else {
            b->lc = merge(a, b->lc);
            push_up(b);
            return b;
        }
    }

    void split(node* const rt, node*& a, node*& b, const T& key) {
        if (!rt) {
            a = b = nullptr;
        } else if (rt->key >= key) {
            b = rt;
            split(rt->lc, a, rt->lc, key);
        } else {
            a = rt;
            split(rt->rc, rt->rc, b, key);
        }
        if (rt) { push_up(rt); }
    }

    T* getKth(node* const& rt, const int& x) {
        if (!rt) return nullptr;
        int tmp = sz(rt->lc) + 1;
        if (x < tmp) {
            return getKth(rt->lc, x);
        } else if (x > tmp) {
            return getKth(rt->rc, x - tmp);
        } else {
            return &rt->key;
        }
    }

  public:
    Treap()
        : root(nullptr) {}

    T* getKth(const int& x) {
        return getKth(root, x);
    }

    int rank(const T& x) {
        node *a, *b;
        a = b = nullptr;

        split(root, a, b, x + 1);
        int tmp = sz(a);
        root    = merge(a, b);

        return tmp;
    }

    void insert(const T& k, const int& v = rnd()) {
        node *a, *b;
        a = b = nullptr;

        split(root, a, b, k);
        root = merge(a, merge(new node(k, v), b));
    }

    void remove(const T& x) {
        node *a, *b, *c, *tmp;
        a = b = c = tmp = nullptr;

        split(root, a, tmp, x);
        split(tmp, b, c, x + 1);
        b    = merge(b->lc, b->rc);
        root = merge(a, merge(b, c));
    }

    T* prev(const T& k) {
        int vnr = rank(k);
        T*  tmp = getKth(vnr);
        return tmp && *tmp < k ? tmp : getKth(vnr - 1);
    }

    T* next(const T& k) {
        int vnr = rank(k + 1);
        T*  tmp = getKth(vnr);
        return tmp && *tmp > k ? tmp : getKth(vnr + 1);
    }
};

struct Pr {
    int x, y, z;
};

Pr         dt[200005];
Treap<int> tree[200005];
int        f[200005], g[200005];
bool       vis[200005];

void insert(int x, int y) {
    for (; x <= k; x += lowbit(x)) {
        tree[x].insert(y);
    }
}

int query(int x, int y) {
    int ans = 0;

    for (; x; x -= lowbit(x)) {
        ans += tree[x].rank(y);
    }

    return ans;
}

int main() {

    // freopen("P3810.in", "r", stdin);
    // freopen("P3810.out", "w", stdout);

    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        dt[i] = {a, b, c};
    }

    sort(dt + 1, dt + n + 1, [&](Pr& a, Pr& b) { return a.x < b.x; });

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            for (int j = i; dt[j].x == dt[i].x && j <= n; j++) {
                insert(dt[j].y, dt[j].z);
                vis[j] = true;
            }
        }

        f[i] = query(dt[i].y, dt[i].z);
    }

    for (int i = 1; i <= n; i++) {
        ++g[f[i]];
    }

    for (int i = 1; i <= n; i++) {
        cout << g[i] << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}