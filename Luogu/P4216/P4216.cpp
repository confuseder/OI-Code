#include <bits/stdc++.h>
using namespace std;

int n, m;

struct query {
    int type, time;
    int st, ed, v;
    int id;

    query() {}

    query(int _time, int _st, int _ed, int _v)
        : type(1), time(_time), st(_st), ed(_ed), v(_v) {}

    query(int _time, int _id)
        : type(2), time(_time), id(_id) {}
} q[200005];

vector<int> mp[200005];

pair<int, int> ans[200005];

// bitree

template <typename T>
struct bitree {

    int       n;
    vector<T> data;

    bitree() {}

    bitree(int _n)
        : n(_n) {
        data.resize(_n + 5);
    }

    int lowbit(int x) {
        return x & -x;
    }

    void add(int x, int v) {
        while (x <= n) {
            data[x] += v;
            x += lowbit(x);
        }
    }

    T query(int x) {
        T ans = 0;
        while (x) {
            ans += data[x];
            x -= lowbit(x);
        }
        return ans;
    }

    T query(int x, int y) {
        return query(y) - query(x - 1);
    }
};

bitree<int> tr1(200005), tr2(200005);

// pf

int cnt, root;
int dep[200005];
int siz[200005];
int son[200005];
int fa[200005];
int top[200005];
int id[200005];

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

int queryPath(int u, int v, bitree<int> &t) {
    int res = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) {
            swap(u, v);
        }

        res += t.query(id[top[u]], id[u]);
        u = fa[top[u]];
    }

    if (dep[u] > dep[v]) { swap(u, v); }
    res += t.query(id[u], id[v]);

    return res;
}

int main() {

    // freopen("P4216.in", "r", stdin);
    // freopen("P4216.out", "w", stdout);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        if (x == 0) {
            root = i;
            continue;
        } else {
            mp[x].emplace_back(i);
        }
    }

    init_1(root, 0);
    init_2(root, root);

    for (int i = 1; i <= n; i++) {
        tr2.add(id[i], 1);
    }

    cin >> m;

    for (int i = 1; i <= m; i++) {
        int type, x, y, c;
        cin >> type;
        switch (type) {
            case 1: {
                cin >> x >> y >> c;
                q[i] = query(i, x, y, c);
                break;
            }
            case 2: {
                cin >> x;
                q[i]   = query(i, x);
                ans[i] = {-1, -1};
                break;
            }
        }
    }

    sort(q + 1, q + m + 1, [](query a, query b) {
        if (a.type == 2 && b.type == 2) {
            return a.time < b.time;
        } else if (a.type == 1 && b.type == 1) {
            return (a.time - a.v - 1) < (b.time - b.v - 1);
        } else {
            return a.type == 1;
        }
    });

    int modify = 1, start;

    while (q[modify].type == 1) {
        modify++;
    }

    start = modify;

    for (int i = 1; i < start; i++) {
        while (q[modify].time + q[i].v < q[i].time && modify <= m) {

            tr1.add(id[q[modify].id], 1);
            modify++;
        }

        ans[q[i].time] = {queryPath(q[i].st, q[i].ed, tr2), queryPath(q[i].st, q[i].ed, tr1)};
    }

    for (int i = 1; i <= m; i++) {
        if (ans[i].first != -1) {
            cout << ans[i].first << ' ' << ans[i].second << endl;
        }
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}