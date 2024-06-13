#include <bits/stdc++.h>
using namespace std;

int n, m;
int dp[15][35000];
int status[35000], cnt;
int mp[15];

int main() {

    // freopen("P1879.in", "r", stdin);
    // freopen("P1879.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = m - 1; j >= 0; j--) {
            int x;
            cin >> x;
            mp[i] += (x << j);
        }
    }

    for (int i = 0; i < (1 << m); i++) {
        if (i & (i << 1)) {
            continue;
        }

        status[++cnt] = i;
    }

    for (int i = 1; i <= cnt; i++) {
        if (!((status[i] | mp[1]) == mp[1])) {
            continue;
        }

        dp[1][status[i]] = 1;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= cnt; j++) {
            if (!((status[j] | mp[i]) == mp[i])) {
                continue;
            }

            for (int k = 1; k <= cnt; k++) {
                if (!((status[k] | mp[i - 1]) == mp[i - 1])) {
                    continue;
                }
                if (status[j] & status[k]) {
                    continue;
                }
                dp[i][status[j]] += dp[i - 1][status[k]];
                dp[i][status[j]] %= 100000000;
            }
        }
    }

    int ans = 0;

    for (int j = 1; j <= cnt; j++) {
        ans += dp[n][status[j]];
        ans %= 100000000;
    }

    cout << ans << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}