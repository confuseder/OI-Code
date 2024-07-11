#include <bits/stdc++.h>
using namespace std;

int         n, k;
vector<int> mp[300005];
int         c[300005];
bool        record = false, vis[300005];

pair<int, int> dfs(int u, int f, long long len) {

    if (mp[u].size() == 1 && f != 0) {
        return {len, u};
    }

    long long mx    = 0;
    int       id    = 0;
    int       child = 0;

    for (auto i : mp[u]) {
        if (i != f) {
            auto j = dfs(i, u, len + 1);
            if (j.first > mx) {
                mx = j.first, id = j.second, child = i;
            }
        }
    }

    if (record) {
        c[u] = child;
    }

    return {mx, id};
}

int ans, f[300005];

void dp(int x, int pre) {
    for (auto i : mp[x]) {
        if (i == pre) {
            continue;
        }
        dp(i, x);
        ans  = max(ans, f[x] + f[i] + (vis[x] && vis[i] ? -1 : 1));
        f[x] = max(f[x], f[i] + (vis[x] && vis[i] ? -1 : 1));
    }
}

int main() {

    // freopen("P3269.in", "r", stdin);
    // freopen("P3269.out", "w", stdout);

    cin >> n >> k;

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;

        mp[u].emplace_back(v);
        mp[v].emplace_back(u);
    }

    auto [_, a]   = dfs(1, 0, 0);
    record        = true;
    auto [len, b] = dfs(a, 0, 0);

    if (k == 1) {
        cout << 2 * (n - 1) - len + 1 << endl;
    } else {
        for (int i = a; i != 0; i = c[i]) {
            vis[i] = true;
        }
        dp(1, 0);
        cout << n * 2 - len - ans << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}