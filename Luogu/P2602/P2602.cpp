#include <bits/stdc++.h>
using namespace std;

long long l, r;
long long dp[15][10][10], ans[10][2], a[15];

long long quick_pow(long long a, long long b) {
    long long s = 1;
    while (b) {
        if (b & 1) s *= a;
        b >>= 1;
        a *= a;
    }
    return s;
}

void solve(long long x, int query) {

    long long num = 0;
    memset(dp, 0, sizeof(dp));
    memset(a, 0, sizeof(a));

    while (x) {
        a[++num] = x % 10;
        x /= 10;
    }

    for (int i = 0; i <= 9; i++) {
        dp[1][i][i] = 1;
    }

    for (int i = 2; i <= num; i++) {
        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k <= 9; k++) {
                for (int p = 0; p <= 9; p++)
                    dp[i][j][p] += dp[i - 1][k][p];
            }
            dp[i][j][j] += quick_pow(10, i - 1);
        }
    }

    for (int i = 1; i < num; i++) {
        for (int j = 1; j <= 9; j++) {
            for (int k = 0; k <= 9; k++) {
                ans[k][query] += dp[i][j][k];
            }
        }
    }

    for (int i = 1; i < a[num]; i++) {
        for (int k = 0; k <= 9; k++) {
            ans[k][query] += dp[num][i][k];
        }
    }

    for (int i = num - 1; i >= 1; i--) {
        for (int j = 0; j < a[i]; j++) {
            for (int k = 0; k <= 9; k++) {
                ans[k][query] += dp[i][j][k];
            }
        }

        for (int p = num; p > i; p--) {
            ans[a[p]][query] += a[i] * quick_pow(10, i - 1);
        }
    }
}

int main() {

    // freopen("P2602.in", "r", stdin);
    // freopen("P2602.out", "w", stdout);

    cin >> l >> r;

    solve(r + 1, 0), solve(l, 1);

    for (int i = 0; i <= 9; i++) {
        cout << ans[i][0] - ans[i][1] << ' ';
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}