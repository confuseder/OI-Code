#include <bits/stdc++.h>
using namespace std;

int dp[20][10], ans[20];
int l, r;

int cnt(int x) {
    if (x <= 0) {
        return 0;
    }

    int num[20];
    int len = 0;

    while (x) {
        num[++len] = x % 10;
        x /= 10;
    }

    int sum = 0;

    for (int i = len; i >= 1; i--) {
        if (i == len) {
            for (int j = 0; j < num[i]; j++) {
                sum += dp[i][j];
            }
            if (num[i] >= 1) {
                sum += ans[i];
            }
            continue;
        }
        for (int j = 0; j <= min(num[i] - 1, num[i + 1] - 2); j++) {
            sum += dp[i][j];
        }
        for (int j = num[i + 1] + 2; j < num[i]; j++) {
            sum += dp[i][j];
        }
        if (i < len && abs(num[i] - num[i + 1]) < 2) {
            break;
        }
    }

    return sum;
}

int main() {

    // freopen("P2657.in", "r", stdin);
    // freopen("P2657.out", "w", stdout);

    for (int i = 0; i <= 9; i++) {
        dp[1][i] = 1;
    }

    ans[1] = 2;

    for (int i = 2; i <= 15; i++) {
        ans[i] += dp[i - 1][1] + dp[i - 1][0] + ans[i - 1];

        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k <= j - 2; k++) {
                dp[i][j] += dp[i - 1][k];
            }
            for (int k = j + 2; k <= 9; k++) {
                dp[i][j] += dp[i - 1][k];
            }
        }
    }

    while (cin >> l >> r) {
        cout << cnt(r + 1) - cnt(l) << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}