#include <bits/stdc++.h>
using namespace std;

#define lowbit(x) (x & -x)

int         n, m;
vector<int> mp[200005];
int         v[200005], dfn[200005], dep[200005], siz[200005];
int         cnt;
int         bitree[200005];

void dfs(int u, int fa) {
    dfn[u] = ++cnt;
    dep[u] = dep[fa] + 1;
    siz[u] = 1;

    for (auto i : mp[u]) {
        dfs(i, u);
        siz[u] += siz[i];
    }
}

void add(int x, int v) {
    for (int i = x; i <= n; i += lowbit(i)) {
        bitree[i] += v;
    }
}

int query(int x) {
    int ans = 0;
    for (int i = x; i; i -= lowbit(i)) {
        ans += bitree[i];
    }
    return ans;
}

int main() {

    // freopen("CF383C.in", "r", stdin);
    // freopen("CF383C.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> v[i];
    }

    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        mp[u].push_back(v);
    }

    dfs(1, 0);

    while (m--) {
        int op;
        cin >> op;

        switch (op) {
            case 1: {
                int x, val;
                cin >> x >> val;

                add(dfn[x], val * (dep[x] & 1 ? 1 : -1));
                add(dfn[x] + siz[x], -val * (dep[x] & 1 ? 1 : -1));

                break;
            }
            case 2: {
                int x;
                cin >> x;

                cout << v[x] + (dep[x] & 1 ? 1 : -1) * query(dfn[x]) << endl;
            }
        }
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}