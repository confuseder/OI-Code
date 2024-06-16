#include <bits/stdc++.h>
using namespace std;

int x, y;

int f[15][15], g[15][15];

int dp[1500000];

int dfs(int sta, bool who, int n, int m) {
    if (~dp[sta]) return dp[sta];
    dp[sta] = who ? -1e9 : 1e9;
    int x = n, y = 0;
    for (int i = 0; i < n + m - 1; i++) {
        if (sta >> i & 1) {
            x--;
        } else {
            y++;
        }
        if ((sta >> i & 3) != 1) {
            continue;
        }
        int nxt = sta ^ (3 << i);
        if (who) {
            dp[sta] = max(dp[sta], dfs(nxt, who ^ 1, n, m) + f[x][y]);
        } else {
            dp[sta] = min(dp[sta], dfs(nxt, who ^ 1, n, m) - g[x][y]);
        }
    }
    return dp[sta];
}

int main() {

    // freopen("P4363.in", "r", stdin);
    // freopen("P4363.out", "w", stdout);

    cin >> x >> y;

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            cin >> f[i][j];
        }
    }

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            cin >> g[i][j];
        }
    }

    memset(dp, 0xff, sizeof(dp));

    dp[((1 << x) - 1) << y] = 0;

    cout << dfs((1 << x) - 1, 1, x, y) << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}