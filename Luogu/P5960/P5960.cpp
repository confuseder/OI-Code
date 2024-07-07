#include <bits/stdc++.h>
using namespace std;

int n, m;

vector<pair<int, int>> mp[5005];

int        ans, dist[5005], cnt[5005];
bool       vis[5005];
queue<int> q;

int main() {

    // freopen("P5960.in", "r", stdin);
    // freopen("P5960.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        mp[v].emplace_back(u, w);
    }

    for (int i = 1; i <= n; i++) {
        mp[n + 1].emplace_back(i, 0);
    }

    memset(dist, 0x3f, sizeof(dist));
    dist[n + 1] = 0, vis[n + 1] = true, cnt[n + 1]++;
    q.push(n + 1);

    while (!q.empty()) {
        int now = q.front();
        q.pop();
        vis[now] = false;

        for (auto [i, w] : mp[now]) {
            if (dist[now] + w < dist[i]) {
                dist[i] = dist[now] + w;

                if (!vis[i]) {
                    vis[i] = true;
                    q.push(i);

                    cnt[i]++;

                    if (cnt[i] > n) {
                        cout << "NO" << endl;
                        return 0;
                    }
                }
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << dist[i] << ' ';
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}