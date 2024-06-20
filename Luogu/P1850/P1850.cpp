#include <bits/stdc++.h>
using namespace std;

int n, m, v, e;

int    c[2005], d[2005], dis[305][305];
double k[2005], f[2005][2005][2];

int main() {

    // freopen("P1850.in", "r", stdin);
    // freopen("P1850.out", "w", stdout);

    cin >> n >> m >> v >> e;

    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }

    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }

    for (int i = 1; i <= n; i++) {
        cin >> k[i];
    }

    for (int i = 1; i <= v; i++) {
        for (int j = 1; j < i; j++) {
            dis[j][i] = dis[i][j] = 1e9;
        }
    }

    for (int i = 1; i <= e; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        dis[b][a] = dis[a][b] = min(dis[a][b], w);
    }

    for (int k = 1; k <= v; k++) {
        for (int i = 1; i <= v; i++) {
            for (int j = 1; j < i; j++) {
                if (dis[i][j] > dis[i][k] + dis[k][j]) {
                    dis[j][i] = dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            f[i][j][0] = f[i][j][1] = 1e9;
        }
    }

    f[1][0][0] = 0;
    f[1][1][1] = 0;

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            f[i][j][0] = min(f[i - 1][j][1] + k[i - 1] * dis[d[i - 1]][c[i]] + (1 - k[i - 1]) * dis[c[i - 1]][c[i]],
                             f[i - 1][j][0] + dis[c[i - 1]][c[i]]);

            if (j != 0) {
                f[i][j][1] = min(f[i - 1][j - 1][1] + k[i - 1] * k[i] * dis[d[i - 1]][d[i]] + k[i - 1] * (1 - k[i]) * dis[d[i - 1]][c[i]] + (1 - k[i - 1]) * k[i] * dis[c[i - 1]][d[i]] + (1 - k[i - 1]) * (1 - k[i]) * dis[c[i - 1]][c[i]],
                                 f[i - 1][j - 1][0] + k[i] * dis[c[i - 1]][d[i]] + (1 - k[i]) * dis[c[i - 1]][c[i]]);
            }
        }
    }

    double ans = 1e9;

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= 1; j++) {
            ans = min(ans, f[n][i][j]);
        }
    }

    printf("%.2lf", ans);

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}