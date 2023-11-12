#include <bits/stdc++.h>
using namespace std;

int ans;
int n, m, t;
int mach[1005], dfn[1005];
vector<int> mp[1005];

bool dfs(int u, int ti) {
    if (dfn[u] == ti) {
        return false;
    }
    dfn[u] = ti;

    for (auto i : mp[u]) {
        if (mach[i] == 0 || dfs(mach[i], ti)) {
            mach[i] = u;
            return true;
        }
    }
    return false;
}

int main() {

    // freopen("P3386.in", "r", stdin);
    // freopen("P3386.out", "w", stdout);

    cin >> n >> m >> t;

    for (int i = 1; i <= t; i++) {
        int u, v;
        cin >> u >> v;
        mp[u].emplace_back(v);
    }

    for (int i = 1; i <= n; ++i) {
        ans += dfs(i, i);
    }

    cout << ans << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}