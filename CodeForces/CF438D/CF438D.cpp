#include <bits/stdc++.h>
using namespace std;

int       n, m;
long long dt[100005];

struct node {
    int       l, r;
    long long mx, sum;
    node     *lc;
    node     *rc;
} *root;

void push_up(node *p) {
    p->sum = p->lc->sum + p->rc->sum;
    p->mx  = max(p->lc->mx, p->rc->mx);
}

void build(int l, int r, node *p) {
    p->l = l, p->r = r;

    if (l == r) {
        p->sum = dt[l];
        p->mx  = dt[l];
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, p->lc = (new node));
    build(mid + 1, r, p->rc = (new node));
    push_up(p);
}

void mod(int l, int r, node *p, long long m) {
    if (l <= p->l && r >= p->r) {
        if (m > p->mx) {
            return;
        }
        if (p->l == p->r) {
            p->mx %= m;
            p->sum %= m;
            return;
        }
    }

    int mid = (p->l + p->r) / 2;
    if (l <= mid) {
        mod(l, r, p->lc, m);
    }
    if (mid < r) {
        mod(l, r, p->rc, m);
    }

    push_up(p);
}

void modify(int l, int r, node *p, long long k) {
    if (l == p->l && r == p->r) {
        p->mx  = k;
        p->sum = k;
        return;
    }

    int mid = (p->l + p->r) / 2;
    if (l <= mid) {
        modify(l, r, p->lc, k);
    }
    if (mid < r) {
        modify(l, r, p->rc, k);
    }

    push_up(p);
}

long long query(int l, int r, node *p) {
    if (p->l >= l && p->r <= r) {
        return p->sum;
    }

    long long tot = 0;
    int       mid = (p->l + p->r) / 2;

    if (l <= mid) {
        tot += query(l, r, p->lc);
    }
    if (mid < r) {
        tot += query(l, r, p->rc);
    }

    return tot;
}

int main() {

    // freopen("CF438D.in", "r", stdin);
    // freopen("CF438D.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> dt[i];
    }

    root = new node;

    build(1, n, root);

    while (m--) {
        int op;
        cin >> op;

        switch (op) {
            case 1: {
                int l, r;
                cin >> l >> r;

                cout << query(l, r, root) << endl;
            } break;
            case 2: {
                int l, r, x;
                cin >> l >> r >> x;

                mod(l, r, root, x);
            } break;
            case 3: {
                int k, x;
                cin >> k >> x;
                modify(k, k, root, x);
            }
        }
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}