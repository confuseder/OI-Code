#include <bits/stdc++.h>
using namespace std;

int n, m;

int                    f[2000005][30];
int                    ans = 1e9;
vector<pair<int, int>> line;

int main() {

    // freopen("P6902.in", "r", stdin);
    // freopen("P6902.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;

        line.emplace_back(l, (l > r) ? (r + n) : (r));
    }

    sort(line.begin(), line.end());

    int now = 0, r = 0;

    for (int i = 1; i <= 2 * n; i++) {
        while (now < m && line[now].first <= i) {
            r = max(r, line[now].second + 1);
            now++;
        }

        f[i][0] = r;
    }

    for (int i = 1; i <= 20; i++) {
        for (int j = 1; j <= 2 * n; j++) {
            f[j][i] = f[f[j][i - 1]][i - 1];
        }
    }

    for (int i = 1; i <= 2 * n; i++) {
        int x = i, ret = 0;

        for (int j = 20; j >= 0; j--) {
            if (f[x][j] - i < n) {
                x = f[x][j];
                ret += 1 << j;
            }
        }

        x = f[x][0];
        ret++;

        if (x - i >= n) { ans = min(ans, ret); }
    }

    if (ans == 1e9) {
        cout << "impossible" << endl;
    } else {
        cout << ans << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}