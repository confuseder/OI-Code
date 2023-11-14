#include <bits/stdc++.h>
using namespace std;

const int64_t inf = -1e18;

struct node {
    int64_t l, r;
    int64_t lazy_j, lazy_g;
    int64_t mx;
    node() : l(0), r(0), lazy_j(0), lazy_g(0), mx(0) {}
};

int64_t n, q;
int64_t num[1000005];
node tree[4000005];

void push_up(int64_t u) {
    tree[u].mx = max(tree[u << 1].mx, tree[u << 1 | 1].mx);
}

void push_down(int64_t u) {
    if (tree[u].lazy_g != inf) {
        tree[u << 1].lazy_g     = tree[u].lazy_g;
        tree[u << 1 | 1].lazy_g = tree[u].lazy_g;
        tree[u << 1].mx         = tree[u].lazy_g;
        tree[u << 1 | 1].mx     = tree[u].lazy_g;
        tree[u << 1].lazy_j     = 0;
        tree[u << 1 | 1].lazy_j = 0;
        tree[u].lazy_g          = inf;
    }
    if (tree[u].lazy_j != 0) {
        tree[u << 1].lazy_j += tree[u].lazy_j;
        tree[u << 1 | 1].lazy_j += tree[u].lazy_j;
        tree[u << 1].mx += tree[u].lazy_j;
        tree[u << 1 | 1].mx += tree[u].lazy_j;
        tree[u].lazy_j = 0;
    }
}

void build(int64_t u, int64_t l, int64_t r) {
    tree[u].l = l, tree[u].r = r;
    if (l == r) {
        tree[u].lazy_g = inf;
        tree[u].lazy_j = 0;
        tree[u].mx     = num[l];
        return;
    }
    int64_t mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    tree[u].lazy_g = inf;
    push_up(u);
}

int64_t query(int64_t u, int64_t l, int64_t r) {
    int64_t res = inf;
    if (tree[u].l >= l && tree[u].r <= r) {
        return tree[u].mx;
    }
    push_down(u);
    int mid = (tree[u].l + tree[u].r) >> 1;
    if (l <= mid) {
        res = max(res, query(u << 1, l, r));
    }
    if (r > mid) {
        res = max(res, query(u << 1 | 1, l, r));
    }
    return res;
}

void update_j(int64_t u, int64_t l, int64_t r, int64_t val) {
    if (tree[u].l >= l && tree[u].r <= r) {
        push_down(u);
        tree[u].mx += val;
        tree[u].lazy_j += val;
        return;
    }
    push_down(u);
    uint64_t mid = (tree[u].l + tree[u].r) >> 1;
    if (l <= mid) {
        update_j(u << 1, l, r, val);
    }
    if (r > mid) {
        update_j(u << 1 | 1, l, r, val);
    }
    push_up(u);
    return;
}

void update_g(int64_t u, int64_t l, int64_t r, int64_t val) {
    if (tree[u].l >= l && tree[u].r <= r) {
        tree[u].mx     = val;
        tree[u].lazy_g = val;
        tree[u].lazy_j = 0;
        return;
    }
    push_down(u);
    uint64_t mid = (tree[u].l + tree[u].r) >> 1;
    if (l <= mid) {
        update_g(u << 1, l, r, val);
    }
    if (r > mid) {
        update_g(u << 1 | 1, l, r, val);
    }
    push_up(u);
    return;
}

int main() {

    // freopen("P1253.in", "r", stdin);
    // freopen("P1253.out", "w", stdout);

    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &num[i]);
    }

    build(1, 1, n);

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int64_t l, r, x;
            scanf("%lld%lld%lld", &l, &r, &x);
            update_g(1, l, r, x);
        } else if (op == 2) {
            int64_t l, r, x;
            scanf("%lld%lld%lld", &l, &r, &x);
            update_j(1, l, r, x);
        } else if (op == 3) {
            int64_t l, r;
            scanf("%lld%lld", &l, &r);
            cout << query(1, l, r) << endl;
        }
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}