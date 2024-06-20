#include <bits/stdc++.h>
using namespace std;

int         n;
int         color[100005];
int         fa[100005], son[100005], siz[100005];
vector<int> mp[100005];

long long cnt[100005], ans[100005], mx, sum;

void init(int u, int f) {
    fa[u] = f, siz[u] = 1;

    for (auto i : mp[u]) {
        if (i == f) {
            continue;
        }
        init(i, u);
        siz[u] += siz[i];
        if (siz[i] > siz[son[u]]) {
            son[u] = i;
        }
    }
}

void solve(int u, int val, int s) {
    cnt[color[u]] += val;

    if (cnt[color[u]] > mx) {
        mx  = cnt[color[u]];
        sum = color[u];
    } else if (cnt[color[u]] == mx) {
        sum += color[u];
    }

    for (auto i : mp[u]) {
        if (i == fa[u] || i == s) {
            continue;
        }

        solve(i, val, s);
    }
}

void dfs(int u, int type) {
    for (auto i : mp[u]) {
        if (i == fa[u] || i == son[u]) {
            continue;
        }
        dfs(i, 0);
    }

    if (son[u]) {
        dfs(son[u], 1);
    }

    solve(u, 1, son[u]);

    ans[u] = sum;

    if (!type) {
        solve(u, -1, 0);
        sum = mx = 0;
    }
}

int main() {

    // freopen("CF600E.in", "r", stdin);
    // freopen("CF600E.out", "w", stdout);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> color[i];
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;

        mp[u].push_back(v);
        mp[v].push_back(u);
    }

    init(1, 0);

    dfs(1, 0);

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << ' ';
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}