#include <bits/stdc++.h>
using namespace std;

int                           n;
map<pair<int, int>, set<int>> dt;

vector<int> mp[200005];

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

int main() {

    // freopen("P2610.in", "r", stdin);
    // freopen("P2610.out", "w", stdout);

    cin >> n;

    for (int i = 1; i <= n - 2; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dt[{min(u, v), max(u, v)}].insert(i);
        dt[{min(v, w), max(v, w)}].insert(i);
        dt[{min(u, w), max(u, w)}].insert(i);
    }

    for (auto [_, st] : dt) {
        for (auto i : st) {
            for (auto j : st) {
                if (i != j) {
                    mp[i].emplace_back(j);
                }
            }
        }
    }

    cout << dfs(dfs(1, 0, 0).second, 0, 0).first + 1 << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}