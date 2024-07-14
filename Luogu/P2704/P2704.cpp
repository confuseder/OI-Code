#include <bits/stdc++.h>
using namespace std;

int n, m, ans;
int dp[2000][2000][5];
int mp[105];
int sta[2000];

int main() {
    // freopen("P2704.in", "r", stdin);
    // freopen("P2704.out", "w", stdout);

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char x;
            cin >> x;
            mp[i] <<= 1;
            mp[i] += (x == 'H' ? 1 : 0);
        }
    }

    for (int i = 0; i < (1 << m); i++) {
        sta[i] = __builtin_popcount(i);
    }

    for (int i = 0; i < (1 << m); i++) {
        if (!(i & mp[0] || (i & (i << 1)) || (i & (i << 2)))) {
            dp[0][i][0] = sta[i];
        }
    }

    for (int L = 0; L < (1 << m); L++) {
        for (int S = 0; S < (1 << m); S++) {
            if (!(L & S || L & mp[0] || S & mp[1] || (L & (L << 1)) || (L & (L << 2)) || (S & (S << 1)) || (S & (S << 2)))) {
                dp[L][S][1] = sta[L] + sta[S];
            }
        }
    }

    for (int i = 2; i < n; i++) {
        for (int L = 0; L < (1 << m); L++) {
            if (L & mp[i - 1] || (L & (L << 1)) || (L & (L << 2))) {
                continue;
            }
            for (int S = 0; S < (1 << m); S++) {
                if (S & mp[i] || L & S || (S & (S << 1)) || (S & (S << 2))) {
                    continue;
                }
                for (int FL = 0; FL < (1 << m); FL++) {
                    if (FL & L || FL & S || FL & mp[i - 2] || (FL & (FL << 1)) || (FL & (FL << 2))) {
                        continue;
                    }
                    dp[L][S][i % 3] = max(dp[L][S][i % 3], dp[FL][L][(i - 1) % 3] + sta[S]);
                }
            }
        }
    }

    for (int L = 0; L < (1 << m); L++) {
        for (int S = 0; S < (1 << m); S++) {
            ans = max(ans, dp[L][S][(n - 1) % 3]);
        }
    }

    cout << ans;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}