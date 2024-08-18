#include <bits/stdc++.h>
using namespace std;

struct seg {
    long long mi, tag;
    int       l, r;
    seg      *lc, *rc;

    void push_up() {
        if (l != r) {
            this->mi = min(lc->mi, rc->mi);
        }
    }

    void push_down() {
        if (tag != 0 && l != r) {
            lc->tag = rc->tag = tag;
            lc->mi = rc->mi = tag;
            tag             = 0;
        }
    }
};

int         n, m;
vector<int> mp[100005];
long long   val[100005];

int cnt, rt = 1;
int dep[100005];
int siz[100005];
int son[100005];
int fa[100005];
int top[100005];
int id[100005];
int rnk[100005];

seg *root;

void build(int l, int r, seg *p = nullptr) {
    if (p == nullptr) {
        p = root = new seg;
    }

    p->l = l, p->r = r;

    if (l == r) {
        p->mi = val[rnk[l]];
        return;
    }

    p->lc = new seg;
    p->rc = new seg;

    int mid = (l + r) / 2;

    build(l, mid, p->lc);
    build(mid + 1, r, p->rc);

    p->push_up();
}

void modify(int l, int r, int x, seg *p = nullptr) {
    if (p == nullptr) {
        p = root;
    }

    if (p->l >= l && p->r <= r) {
        p->mi = p->tag = x;
    } else {

        p->push_down();

        int mid = (p->l + p->r) / 2;

        if (l <= mid) {
            modify(l, r, x, p->lc);
        }
        if (r > mid) {
            modify(l, r, x, p->rc);
        }

        p->push_up();
    }
}

long long query(int l, int r, seg *p = nullptr) {

    if (p == nullptr) {
        p = root;
    }

    if (p->l >= l && p->r <= r) {
        return p->mi;
    }

    int       mid = (p->l + p->r) / 2;
    long long ans = 1e18;

    p->push_down();

    if (l <= mid) {
        ans = min(ans, query(l, r, p->lc));
    }
    if (r > mid) {
        ans = min(ans, query(l, r, p->rc));
    }

    return ans;
}

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
    top[u]   = f;
    id[u]    = ++cnt;
    rnk[cnt] = u;

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

void chain_modify(int u, int v, int k) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            swap(u, v);
        }
        modify(id[top[u]], id[u], k);
        u = fa[top[u]];
    }

    if (dep[u] > dep[v]) { swap(u, v); }

    modify(id[u], id[v], k);
}

int find(int u) {
    if (u == rt) { return -1; }
    if (id[u] >= id[rt] || id[u] + siz[u] - 1 < id[rt]) { return 0; }

    int now = rt;
    while (top[now] != top[u]) {
        if (fa[top[now]] == u) { return top[now]; }
        now = fa[top[now]];
    }

    return son[u];
}

int tree_query(int u) {
    int bo = find(u);

    if (bo == -1) {
        return root->mi;
    }
    if (bo == 0) {
        return query(id[u], id[u] + siz[u] - 1);
    } else {
        long long ans = query(1, id[bo] - 1);

        if (id[bo] + siz[bo] - 1 != n) {
            ans = min(ans, query(id[bo] + siz[bo], n));
        }

        return ans;
    }
}

int main() {

    // freopen("P3979.in", "r", stdin);
    // freopen("P3979.out", "w", stdout);

    scanf("%d%d", &n, &m);

    for (int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        mp[u].emplace_back(v);
        mp[v].emplace_back(u);
    }

    for (int i = 1; i <= n; ++i) {
        scanf("%d", &val[i]);
    }

    init_1(1, 0), init_2(1, 1);
    build(1, n);

    scanf("%d", &rt);

    for (int i = 1, bo, u, v, w; i <= m; ++i) {
        scanf("%d", &bo);
        if (bo == 1) {
            scanf("%d", &rt);
        }
        if (bo == 2) {
            scanf("%d %d %d", &u, &v, &w);
            chain_modify(u, v, w);
        }
        if (bo == 3) {
            scanf("%d", &u);
            printf("%lld\n", tree_query(u));
        }
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}