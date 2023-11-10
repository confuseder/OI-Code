#include <bits/stdc++.h>
using namespace std;

int n, m;
long long num1[2005][2005];
long long num[2005][2005];

int main() {

    // freopen("T6.in", "r", stdin);
    // freopen("T6.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= 2 * n; i++) {
        for (int j = 1; j <= 2 * m; j++) {
            cin >> num1[i][j];
        }
    }

    for (int i = 1; i <= 2 * m; i++) {
        for (int j = 1; j <= 2 * n; j++) {
            num[i][j] = num1[j][i];
        }
    }

    for (int i = 1; i <= 2 * m; i += 2) {
        for (int j = 1; j <= 2 * n; j += 2) {
            printf("%lld ", num[i][j] + num[i + 1][j] + num[i][j + 1] +
                                num[i + 1][j + 1]);
        }
        puts("");
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}
