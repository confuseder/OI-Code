#include <bits/stdc++.h>
using namespace std;

struct Node {
    int d, u, mod;

    bool operator>(const Node &rhs) const {
        return d > rhs.d;
    }
};

vector<pair<int, int>> G[1000005];
int                    dist[10005][105];
bool                   vis[10005][105];

priority_queue<Node, vector<Node>, greater<Node>> q;

int main() {

    // freopen("P9751.in", "r", stdin);
    // freopen("P9751.out", "w", stdout);

    int n, m, k;
    cin >> n >> m >> k;

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].push_back({v, w});
    }

    memset(dist, 0x3f, sizeof(dist));
    dist[1][0] = 0;
    q.push({0, 1, 0});

    while (!q.empty()) {
        auto [d, u, mod] = q.top();
        q.pop();

        if (vis[u][mod]) continue;
        vis[u][mod] = true;

        for (auto [v, w] : G[u]) {
            int t = d;
            if (t < w) {
                t += (w - t + k - 1) / k * k;
            }

            int next_mod = (t + 1) % k;
            if (dist[v][next_mod] > t + 1) {
                dist[v][next_mod] = t + 1;
                q.push({dist[v][next_mod], v, next_mod});
            }
        }
    }

    if (dist[n][0] >= 1e8) {
        cout << -1 << endl;
    } else {
        cout << dist[n][0] << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}