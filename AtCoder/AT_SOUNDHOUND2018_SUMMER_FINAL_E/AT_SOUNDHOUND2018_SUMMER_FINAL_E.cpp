#include <bits/stdc++.h>
using namespace std;

const long long mod = 1e9 + 7;
long long       pw[200005], p = 1e6;

struct node {
    node     *lc, *rc;
    int       l, r;
    long long val;

    void push_up() {
        if (l != r) {
            this->val = (this->lc->val + (this->rc->val * pw[int((l + r) / 2) - l + 1] % mod) % mod) % mod;
        }
    }
};

int   n, m, q;
node *root[25];

void build(node *p, int l, int r, string &s) {

    p->l = l, p->r = r;

    if (l == r) {
        p->val = s[l - 1] - 'a' + 1;
        return;
    }

    int mid = (l + r) / 2;

    p->lc = new node;
    p->rc = new node;

    build(p->lc, l, mid, s);
    build(p->rc, mid + 1, r, s);

    p->push_up();
}

void update(node *&p, node *&q, int l, int r) {
    if (p->l >= l && p->r <= r) {
        swap(p, q);
        return;
    }

    int mid = (p->l + p->r) / 2;

    if (l <= mid) {
        update(p->lc, q->lc, l, r);
    }
    if (r > mid) {
        update(p->rc, q->rc, l, r);
    }

    p->push_up();
    q->push_up();
}

long long query(node *p, int l, int r) {
    if (p->l >= l && p->r <= r) {
        return p->val;
    }

    int mid = (p->l + p->r) / 2;

    if (r <= mid) {
        return query(p->lc, l, r);
    }
    if (mid < l) {
        return query(p->rc, l, r);
    }

    return (query(p->lc, l, r) + query(p->rc, l, r) * pw[mid - max(l, p->l) + 1] % mod) % mod;
}

int main() {

    // freopen("AT_SOUNDHOUND2018_SUMMER_FINAL_E.in", "r", stdin);
    // freopen("AT_SOUNDHOUND2018_SUMMER_FINAL_E.out", "w", stdout);

    cin >> n >> m;

    pw[0] = 1;
    for (int i = 1; i <= n + 10; i++) {
        pw[i] = (pw[i - 1] * p) % mod;
    }

    for (int i = 1; i <= m; i++) {
        string s;
        cin >> s;

        root[i] = new node;

        build(root[i], 1, n, s);
    }

    cin >> q;
    for (int i = 1; i <= q; i++) {
        int op, x, y, l, r;
        cin >> op >> x >> y >> l >> r;

        if (op == 1) {
            update(root[x], root[y], l, r);
        } else {
            cout << query(root[x], l, r) << endl;
        }
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}
