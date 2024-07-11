#include <bits/stdc++.h>
using namespace std;

struct line {
    int       to;
    long long w;
};

int          n, m;
long long    dist[5][200005], ans;
vector<line> mp[200005];

pair<long long, int> dfs(int u, int f, long long len) {

    if (mp[u].size() == 1 && f != 0) {
        return {len, u};
    }

    long long mx = 0;
    int       id = 0;

    for (auto [i, w] : mp[u]) {
        if (i != f) {
            auto j = dfs(i, u, len + w);
            if (j.first > mx) {
                mx = j.first, id = j.second;
            }
        }
    }

    return {mx, id};
}

void dis(int x, int f, long long len, long long *d) {
    d[x] = len;

    for (auto [i, w] : mp[x]) {
        if (i != f) {
            dis(i, x, len + w, d);
        }
    }
}

int main() {

    // freopen("P4408.in", "r", stdin);
    // freopen("P4408.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        mp[u].emplace_back(v, w);
        mp[v].emplace_back(u, w);
    }

    auto [_, a]   = dfs(1, 0, 0);
    auto [len, b] = dfs(a, 0, 0);

    dis(a, 0, 0, dist[1]);
    dis(b, 0, 0, dist[2]);

    for (int i = 1; i <= n; i++) {
        if (i != a && i != b) {
            ans = max(ans, min(dist[1][i], dist[2][i]));
        }
    }

    cout << ans + len << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}