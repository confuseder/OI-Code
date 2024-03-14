#include <bits/stdc++.h>
using namespace std;

int n, m;
int cnt;
int dt[1000005], version[1000005];

struct node {
    int l, r;
    int val;
} tree[40000005];

int clone(int node) {
    tree[++cnt] = tree[node];
    return cnt;
}

int build(int l, int r) {
    int node = ++cnt;

    if (l == r) {
        tree[node].val = dt[l];
        return node;
    }

    int mid = (l + r) >> 1;

    tree[node].l = build(l, mid);
    tree[node].r = build(mid + 1, r);

    return node;
}

int update(int node, int x, int v, int l, int r) {
    node = clone(node);

    if (l == r) {
        tree[node].val = v;
    } else {
        int mid = (l + r) >> 1;
        if (x <= mid) {
            tree[node].l = update(tree[node].l, x, v, l, mid);
        } else {
            tree[node].r = update(tree[node].r, x, v, mid + 1, r);
        }
    }

    return node;
}

int query(int node, int x, int l, int r) {
    if (l == r) {
        return tree[node].val;
    } else {
        int mid = (l + r) >> 1;
        if (x <= mid) {
            return query(tree[node].l, x, l, mid);
        } else {
            return query(tree[node].r, x, mid + 1, r);
        }
    }
}

int main() {

    // freopen("Persistent Segment Tree I.in", "r", stdin);
    // freopen("Persistent Segment Tree I.out", "w", stdout);

    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &dt[i]);
    }

    version[0] = build(1, n);

    for (int i = 1; i <= m; i++) {
        int ver, op;
        scanf("%d %d", &ver, &op);
        if (op == 1) {
            int x, y;
            scanf("%d %d ", &x, &y);
            version[i] = update(version[ver], x, y, 1, n);
        } else {
            int x;
            scanf("%d", &x);
            printf("%d\n", query(version[ver], x, 1, n));
            version[i] = version[ver];
        }
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}