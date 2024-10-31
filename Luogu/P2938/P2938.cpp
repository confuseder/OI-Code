#include <bits/stdc++.h>
using namespace std;

int s, d, m;
int val[60][20];
int dp[500005];

int mx = -1;

int main() {

    // freopen("P2938.in", "r", stdin);
    // freopen("P2938.out", "w", stdout);

    cin >> s >> d >> m;

    for (int i = 1; i <= s; i++) {
        for (int j = 1; j <= d; j++) {
            cin >> val[i][j];
        }
    }

    for (int i = 2; i <= d; i++) {

        mx = -1;
        memset(dp, 0, sizeof(dp));

        for (int j = 1; j <= s; j++) {
            for (int k = val[j][i - 1]; k <= m; k++) {
                dp[k] = max(dp[k], dp[k - val[j][i - 1]] + val[j][i] - val[j][i - 1]);
                mx    = max(mx, dp[k]);
            }
        }

        m += mx;
    }

    cout << m << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}