#include <bits/stdc++.h>
using namespace std;

int n, m, q;

vector<int> mp[300005];
bool        vis[300005];
int         bc[300005], l[300005];

int find(int x) {
    return bc[x] == x ? x : bc[x] = find(bc[x]);
}

void merge(int u, int v) {
    bc[find(u)] = find(v);
}

pair<int, int> dfs(int u, int f, int len) {

    if (mp[u].size() == 1 && f != 0) {
        return {len, u};
    }

    int mx = 0;
    int id = 0;

    for (auto i : mp[u]) {
        if (i != f) {
            auto j = dfs(i, u, len + 1);
            if (j.first > mx) {
                mx = j.first, id = j.second;
            }
        }
    }

    return {mx, id};
}

int len(int x) {
    return dfs(dfs(x, 0, 0).second, 0, 0).first;
}

int main() {

    // freopen("P2195.in", "r", stdin);
    // freopen("P2195.out", "w", stdout);

    cin >> n >> m >> q;

    for (int i = 1; i <= n; i++) {
        bc[i] = i;
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;

        mp[u].emplace_back(v);
        mp[v].emplace_back(u);
        merge(u, v);
    }

    for (int i = 1; i <= n; ++i) {
        if (bc[i] != i || vis[i]) {
            continue;
        }
        l[i]   = len(i);
        vis[i] = true;
    }

    for (int i = 1; i <= q; i++) {
        int op;
        cin >> op;

        if (op == 1) {
            int x;
            cin >> x;

            cout << l[find(x)] << endl;
        } else {

            int u, v;
            cin >> u >> v;

            if (find(u) == find(v)) {
                continue;
            }

            int tmp = ((l[find(v)] + 1) >> 1) + ((l[find(u)] + 1) >> 1) + 1;

            tmp = max(tmp, max(l[find(v)], l[find(u)]));

            merge(u, v);
            l[find(u)] = tmp;
        }
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}