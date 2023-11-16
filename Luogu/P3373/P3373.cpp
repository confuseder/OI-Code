#include <bits/stdc++.h>
using namespace std;

struct node {
    int64_t l, r;
    int64_t j = 0, x = 1;
    int64_t sum;
};

int64_t n, m, q;

int64_t num[100005];
node tree[400005];

void push_up(int64_t u) {
    tree[u].sum = (tree[u << 1].sum + tree[u << 1 | 1].sum) % m;
}

void push_down(int64_t u) {
    tree[u << 1].sum = (tree[u << 1].sum * tree[u].x +
                        tree[u].j * (tree[u << 1].r - tree[u << 1].l + 1)) %
                       m;
    tree[u << 1 | 1].sum =
        (tree[u << 1 | 1].sum * tree[u].x +
         tree[u].j * (tree[u << 1 | 1].r - tree[u << 1 | 1].l + 1)) %
        m;
    tree[u << 1].x *= tree[u].x, tree[u << 1].x %= m;
    tree[u << 1 | 1].x *= tree[u].x, tree[u << 1 | 1].x %= m;
    tree[u << 1].j     = (tree[u << 1].j * tree[u].x + tree[u].j) % m;
    tree[u << 1 | 1].j = (tree[u << 1 | 1].j * tree[u].x + tree[u].j) % m;

    tree[u].x = 1, tree[u].j = 0;
    return;
}

void build(int64_t u, int64_t l, int64_t r) {
    tree[u].l = l, tree[u].r = r;
    if (l == r) {
        tree[u].sum = num[l];
        return;
    }
    int64_t mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    push_up(u);
}

void add(int64_t u, int64_t l, int64_t r, int64_t val) {
    if (tree[u].l >= l && tree[u].r <= r) {
        tree[u].j += val;
        tree[u].j %= m;
        tree[u].sum += val * (tree[u].r - tree[u].l + 1);
        tree[u].sum %= m;
        return;
    }
    push_down(u);
    int64_t mid = (tree[u].l + tree[u].r) >> 1;
    if (l <= mid) {
        add(u << 1, l, r, val);
    }
    if (r > mid) {
        add(u << 1 | 1, l, r, val);
    }
    push_up(u);
    return;
}

void times(int64_t u, int64_t l, int64_t r, int64_t val) {
    if (tree[u].l >= l && tree[u].r <= r) {
        tree[u].sum *= val;
        tree[u].sum %= m;
        tree[u].x *= val;
        tree[u].x %= m;
        tree[u].j *= val;
        tree[u].j %= m;
        return;
    }
    push_down(u);
    int64_t mid = (tree[u].l + tree[u].r) >> 1;
    if (l <= mid) {
        times(u << 1, l, r, val);
    }
    if (r > mid) {
        times(u << 1 | 1, l, r, val);
    }
    push_up(u);
    return;
}

int64_t query(int64_t u, int64_t l, int64_t r) {
    int64_t ans = 0;
    if (tree[u].l >= l && tree[u].r <= r) {
        return tree[u].sum % m;
    }
    push_down(u);
    int64_t mid = (tree[u].l + tree[u].r) >> 1;
    if (l <= mid) {
        ans += query(u << 1, l, r);
    }
    if (r > mid) {
        ans += query(u << 1 | 1, l, r);
    }
    return ans % m;
}

int main() {

    // freopen("P3373.in", "r", stdin);
    // freopen("P3373.out", "w", stdout);

    cin >> n >> q >> m;

    for (int i = 1; i <= n; i++) {
        cin >> num[i];
    }

    build(1, 1, n);

    for (int i = 1; i <= q; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y, k;
            cin >> x >> y >> k;
            times(1, x, y, k);
        } else if (op == 2) {
            int x, y, k;
            cin >> x >> y >> k;
            add(1, x, y, k);
        } else if (op == 3) {
            int x, y;
            cin >> x >> y;
            cout << query(1, x, y) << endl;
        }
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}