#include <bits/stdc++.h>
using namespace std;

struct line {
    int to, w;
};

int          n, ans = 1e9;
vector<line> mp[5005];
bool         record;
int          r[5005], val[5005];

int dis_u, dis_v;
int dist[5005];

void dis(int u, int f, int len) {
    dist[u] = len;

    for (auto [i, w] : mp[u]) {
        if (i != f && !(dis_u == i && dis_v == u) && !(dis_u == u && dis_v == i)) {
            dis(i, u, len + w);
        }
    }
}

pair<int, int> dfs(int u, int f, int len) {

    if (mp[u].size() == 1 && f != 0) {
        return {len, u};
    }

    int cnt   = 0;
    int mx    = 0;
    int id    = 0;
    int child = 0;
    int v     = 0;

    for (auto [i, w] : mp[u]) {
        if (i != f && !(dis_u == i && dis_v == u) && !(dis_u == u && dis_v == i)) {
            cnt++;
            auto j = dfs(i, u, len + w);
            if (j.first > mx) {
                mx = j.first, id = j.second, child = i, v = w;
            }
        }
    }

    if (cnt == 0) {
        return {len, u};
    }

    if (record) {
        r[u] = child, val[u] = v;
    }

    return {mx, id};
}

int main() {

    // freopen("P3761.in", "r", stdin);
    // freopen("P3761.out", "w", stdout);

    cin >> n;

    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        mp[u].emplace_back(v, w);
        mp[v].emplace_back(u, w);
    }

    for (int u = 1; u <= n; u++) {
        for (auto [v, w] : mp[u]) {
            dis_u = u, dis_v = v;

            auto [_, a_u]     = dfs(u, 0, 0);
            record            = true;
            auto [len_a, a_v] = dfs(a_u, 0, 0);

            int half_len_a = 0;
            int mi         = 1e9;

            for (int i = a_u, tmp = 0; i != 0; i = r[i]) {
                tmp += val[i];
                if (abs(len_a - 2 * tmp) < mi) {
                    half_len_a = max(tmp, len_a - tmp);
                    mi         = abs(len_a - 2 * tmp);
                }
            }

            record = false;
            memset(r, 0, sizeof(r));
            memset(val, 0, sizeof(val));

            auto [m, b_u]     = dfs(v, 0, 0);
            record            = true;
            auto [len_b, b_v] = dfs(b_u, 0, 0);

            int half_len_b = 0;
            mi             = 1e9;

            for (int i = b_u, tmp = 0; i != 0; i = r[i]) {
                tmp += val[i];
                if (abs(len_b - 2 * tmp) < mi) {
                    half_len_b = max(tmp, len_b - tmp);
                    mi         = abs(len_b - 2 * tmp);
                }
            }

            record = false;
            memset(r, 0, sizeof(r));
            memset(val, 0, sizeof(val));

            ans = min(ans, max({len_a, len_b, half_len_a + half_len_b + w}));
        }
    }

    cout << ans << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}