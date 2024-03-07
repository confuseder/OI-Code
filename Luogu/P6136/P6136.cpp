#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;

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

        split(root, a, b, x);
        int tmp = sz(a);
        root    = merge(a, b);

        return tmp + 1;
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

int        n, m, last, ans;
Treap<int> treap;

int main() {

    // freopen("P6136.in", "r", stdin);
    // freopen("P6136.out", "w", stdout);

    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        int x;
        scanf("%d", &x);
        treap.insert(x);
    }

    for (int i = 1; i <= m; i++) {
        int op, x;
        scanf("%d %d", &op, &x);
        x ^= last;

        switch (op) {
            case 1:
                treap.insert(x);
                break;
            case 2:
                treap.remove(x);
                break;
            case 3:
                ans ^= (last = treap.rank(x));
                break;
            case 4:
                ans ^= (last = *treap.getKth(x));
                break;
            case 5:
                ans ^= (last = *treap.prev(x));
                break;
            case 6:
                ans ^= (last = *treap.next(x));
                break;
        }
    }

    printf("%d", ans);

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}