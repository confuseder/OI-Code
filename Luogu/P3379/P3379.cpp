#include <bits/stdc++.h>
using namespace std;

int n, m, s;

vector<int> mp[500005];

int siz[500005];
int fa[500005];
int dep[500005];
int son[500005];
int top[500005];

void init_1(int p, int f) {
    fa[p]  = f;
    siz[p] = 1;
    dep[p] = dep[f] + 1;

    for (auto i : mp[p]) {
        if (i != f) {
            init_1(i, p);

            siz[p] += siz[i];

            if (siz[i] > siz[son[p]]) {
                son[p] = i;
            }
        }
    }
}

void init_2(int p, int f) {
    top[p] = f;

    if (!son[p]) { return; }

    init_2(son[p], f);

    for (auto i : mp[p]) {
        if (i == son[p] || i == fa[p]) {
            continue;
        }
        init_2(i, i);
    }
}

int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] > dep[top[v]]) {
            u = fa[top[u]];
        } else {
            v = fa[top[v]];
        }
    }
    return dep[u] > dep[v] ? v : u;
}

int main() {

    // freopen("P3379.in", "r", stdin);
    // freopen("P3379.out", "w", stdout);

    cin >> n >> m >> s;

    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;

        mp[u].push_back(v);
        mp[v].push_back(u);
    }

    init_1(s, 0);
    init_2(s, s);

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;

        cout << lca(u, v) << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}