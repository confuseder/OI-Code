#include <bits/stdc++.h>
using namespace std;

int         n;
int         ans;
vector<int> mp[10005];

int dfs(int u, int fa) {
    int build = -1;
    for (auto val : mp[u]) {
        if (val != fa) {
            int tmp = dfs(val, u);

            if (tmp == -1) {
                build = 1;
            } else if (tmp == 1 && build != 1) {
                build = 0;
            }
        }
    }
    if (build == 1) {
        ans++;
    }
    return build;
}

int main() {

    // freopen("P2899.in", "r", stdin);
    // freopen("P2899.out", "w", stdout);

    cin >> n;

    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;

        mp[u].emplace_back(v);
        mp[v].emplace_back(u);
    }

    if (dfs(1, 0) == -1) {
        ans++;
    }

    cout << ans << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}