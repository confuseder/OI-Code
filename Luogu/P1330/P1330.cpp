#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int n, m, ans;
vector<int> mp[10005];
int color[10005];
int bl, wh;

bool dfs(int u) {
    for (auto i : mp[u]) {
        if (color[i] == 0) {
            color[i] = (color[u] == 1 ? 2 : 1);
            (color[i] % 2 ? wh : bl)++;
            if (!dfs(i)) {
                return false;
            }
        }

        if (color[i] == color[u]) {
            return false;
        }
    }
    return true;
}

int main() {

    // freopen("P1330.in", "r", stdin);
    // freopen("P1330.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v;

        cin >> u >> v;
        mp[u].push_back(v);
        mp[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            bl = wh  = 0;
            color[i] = 1;
            (color[i] % 2 ? wh : bl)++;

            if (!dfs(i)) {
                cout << "Impossible" << endl;
                return 0;
            }

            ans += min(bl, wh);
        }
    }

    cout << ans << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}