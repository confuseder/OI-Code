#include <bits/stdc++.h>
using namespace std;

#define lowbit(x) (x & -x)

int n, m, r, p;

int         v[100005];
vector<int> mp[100005];

int cnt;
int dep[100005];
int siz[100005];
int son[100005];
int fa[100005];
int top[100005];
int id[100005];

int bitree_a[100005], bitree_b[100005];

void add(int l, int r, int x) {
    x %= p;
    int ad1 = (long long)(l - 1) * x % p;
    int ad2 = (long long)r * x % p;
    for (int t = l; t <= n; t += lowbit(t)) {
        bitree_a[t] = (bitree_a[t] + x) % p;
        bitree_b[t] = (bitree_b[t] + ad1) % p;
    }
    for (int t = r + 1; t <= n; t += lowbit(t)) {
        bitree_a[t] = (bitree_a[t] - x) % p;
        bitree_a[t] = (bitree_a[t] + p) % p;
        bitree_b[t] = (bitree_b[t] - ad2) % p;
        bitree_b[t] = (bitree_b[t] + p) % p;
    }
}

int query(int i) {
    int res = 0;
    for (int t = i; t > 0; t -= lowbit(t)) {
        res = (res + (long long)i * bitree_a[t] % p) % p;
        res = (res - bitree_b[t]) % p;
        res = (res + p) % p;
    }
    return res;
}

int query(int l, int r) {
    int res = (query(r) - query(l - 1)) % p;
    return (res + p) % p;
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
    top[u] = f;
    id[u]  = ++cnt;

    if (v[u] != 0) {
        add(id[u], id[u], v[u]);
    }

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

void addPath(int u, int v, int k) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            swap(u, v);
        }
        add(id[top[u]], id[u], k);
        u = fa[top[u]];
    }

    if (dep[u] > dep[v]) { swap(u, v); }

    add(id[u], id[v], k);
}

int queryPath(int u, int v) {
    int res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            swap(u, v);
        }
        res += query(id[top[u]], id[u]);
        u = fa[top[u]];
    }

    if (dep[u] > dep[v]) { swap(u, v); }
    res += query(id[u], id[v]);

    return res;
}

int querySon(int u) {
    return query(id[u], id[u] + siz[u] - 1);
}

void addSon(int u, int k) {
    add(id[u], id[u] + siz[u] - 1, k);
}

int main() {

    // freopen("P3384.in", "r", stdin);
    // freopen("P3384.out", "w", stdout);

    cin >> n >> m >> r >> p;

    for (int i = 1; i <= n; ++i) {
        cin >> v[i];
    }

    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        mp[x].push_back(y);
        mp[y].push_back(x);
    }

    init_1(r, 0);
    init_2(r, r);

    while (m--) {
        int op, x;

        cin >> op >> x;
        if (op == 1) {
            int y, z;
            cin >> y >> z;

            addPath(x, y, z);
            continue;
        }
        if (op == 2) {
            int y;
            cin >> y;

            cout << queryPath(x, y) % p << endl;
            continue;
        }
        if (op == 3) {
            int z;
            cin >> z;

            addSon(x, z);
            continue;
        }

        cout << querySon(x) % p << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}