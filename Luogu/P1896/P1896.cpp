#include <bits/stdc++.h>
using namespace std;

int       n, m, sum;
long long cnt[2000], line[2000];
long long dp[10][100][2000];

int main() {

    // freopen("P1896.in", "r", stdin);
    // freopen("P1896.out", "w", stdout);

    cin >> n >> m;

    for (int i = 0; i < (1 << n); i++) {
        int tot = 0, x = i;

        while (x) {
            if (x & 1) {
                tot++;
            }

            x >>= 1;
        }

        cnt[i] = tot;

        if ((((i << 1) | (i >> 1)) & i) == 0) {
            line[++sum] = i;
        }
    }

    dp[0][0][0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sum; j++) {
            int x = line[j];

            for (int k = 1; k <= sum; k++) {
                int y = line[k];

                if (((y | (y << 1) | (y >> 1)) & x) == 0) {
                    for (int l = 0; l <= m; l++) {
                        if (l - cnt[x] >= 0) {
                            dp[i][l][x] += dp[i - 1][l - cnt[x]][y];
                        }
                    }
                }
            }
        }
    }

    long long ans = 0;

    for (int i = 1; i <= sum; i++) {
        ans += dp[n][m][line[i]];
    }

    cout << ans << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}