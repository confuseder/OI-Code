#include <bits/stdc++.h>
using namespace std;

int n;
int ans;
int f[15][15][15][15][15];

int main() {

    // freopen("P9752.in", "r", stdin);
    // freopen("P9752.out", "w", stdout);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        int a, b, c, d, e;
        cin >> a >> b >> c >> d >> e;

        for (int j = 1; j <= 9; j++) {
            f[(a + j) % 10][b][c][d][e]++;
            f[a][(b + j) % 10][c][d][e]++;
            f[a][b][(c + j) % 10][d][e]++;
            f[a][b][c][(d + j) % 10][e]++;
            f[a][b][c][d][(e + j) % 10]++;
            f[(a + j) % 10][(b + j) % 10][c][d][e]++;
            f[a][(b + j) % 10][(c + j) % 10][d][e]++;
            f[a][b][(c + j) % 10][(d + j) % 10][e]++;
            f[a][b][c][(d + j) % 10][(e + j) % 10]++;
        }
    }

    for (int a = 0; a <= 9; a++) {
        for (int b = 0; b <= 9; b++) {
            for (int c = 0; c <= 9; c++) {
                for (int d = 0; d <= 9; d++) {
                    for (int e = 0; e <= 9; e++) {
                        if (f[a][b][c][d][e] == n) {
                            ans++;
                        }
                    }
                }
            }
        }
    }

    cout << ans << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}