#include <bits/stdc++.h>
using namespace std;

int         n;
int         ans;
int         dp[1505][5], val[1505];
vector<int> mp[1505];

void solve(int u, int fa) {
    int sum  = 0;
    dp[u][2] = val[u];
    for (auto v : mp[u]) {

        if (v == fa) {
            continue;
        }
        solve(v, u);

        sum += min(dp[v][1], dp[v][2]);
        dp[u][2] += min(min(dp[v][0], dp[v][1]), dp[2][v]);
    }

    dp[u][0] = sum;
    dp[u][1] = 1e9;

    for (auto v : mp[u]) {
        if (v == fa) {
            continue;
        }
        dp[u][1] = min(dp[u][1], sum - min(dp[v][1], dp[v][2]) + dp[v][2]);
    }
}

int main() {

    // freopen("P2458.in", "r", stdin);
    // freopen("P2458.out", "w", stdout);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        int id, w, m;
        cin >> id >> w >> m;

        val[id] = w;

        for (int j = 1; j <= m; j++) {
            int x;
            cin >> x;

            mp[id].emplace_back(x);
            mp[x].emplace_back(id);
        }
    }

    solve(1, 0);

    cout << min(dp[1][1], dp[1][2]) << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}