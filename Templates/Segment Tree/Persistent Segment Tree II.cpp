#include <bits/stdc++.h>
using namespace std;

int n, m;
int num[1000005], ls[1000005];
int cnt, version[1000005];

struct node {
    int l, r;
    int sum;
} tree[40000005];

int clone(int node) {
    tree[++cnt]   = tree[node];
    tree[cnt].sum = tree[node].sum + 1;
    return cnt;
}

int build(int l, int r) {
    int node = ++cnt;

    if (l == r) {
        return node;
    }

    int mid = (l + r) >> 1;

    tree[node].l = build(l, mid);
    tree[node].r = build(mid + 1, r);

    return node;
}

int update(int node, int x, int l, int r) {
    node = clone(node);

    if (l != r) {
        int mid = (l + r) >> 1;
        if (x <= mid) {
            tree[node].l = update(tree[node].l, x, l, mid);
        } else {
            tree[node].r = update(tree[node].r, x, mid + 1, r);
        }
    }

    return node;
}

int query(int x, int y, int l, int r, int k) {
    if (l >= r) {
        return l;
    }
    int tmp = tree[tree[y].l].sum - tree[tree[x].l].sum;

    int mid = (l + r) / 2;

    if (tmp >= k) {
        return query(tree[x].l, tree[y].l, l, mid, k);
    } else {
        return query(tree[x].r, tree[y].r, mid + 1, r, k - tmp);
    }
}

int main() {

    // freopen("Persistent Segment Tree II.in", "r", stdin);
    // freopen("Persistent Segment Tree II.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> num[i];
        ls[i] = num[i];
    }

    sort(ls + 1, ls + n + 1);
    int _n     = unique(ls + 1, ls + n + 1) - ls - 1;
    version[0] = build(1, _n);

    for (int i = 1; i <= n; i++) {
        int tmp    = lower_bound(ls + 1, ls + _n + 1, num[i]) - ls;
        version[i] = update(version[i - 1], tmp, 1, _n);
    }

    for (int i = 1; i <= m; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        int tmp = query(version[l - 1], version[r], 1, _n, k);
        cout << ls[tmp] << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}