#include <bits/stdc++.h>
using namespace std;

struct node {
    int to, w;
};

struct dij {
    int dis, u;

    bool operator>(const dij& a) const {
        return dis > a.dis;
    }
};

int n, m;

vector<node> mp[5005];
int          dist[5005][5], ans = 1e9, again = 1e9;

void Dijkstra(int s, int t) {
    priority_queue<dij, vector<dij>, greater<dij> > q;
    for (int i = 1; i <= n; i++) {
        dist[i][t] = 1e9;
    }

    dist[s][t] = 0;
    q.push({0, s});

    while (q.size()) {
        auto [d, u] = q.top();
        q.pop();

        if (dist[u][t] != d) {
            continue;
        }

        for (auto i : mp[u]) {
            if (dist[i.to][t] <= d + i.w) {
                continue;
            }

            dist[i.to][t] = d + i.w;

            q.push({dist[i.to][t], i.to});
        }
    }
}

int main() {

    // freopen("P2865.in", "r", stdin);
    // freopen("P2865.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        mp[u].emplace_back(v, w);
        mp[v].emplace_back(u, w);
    }

    Dijkstra(1, 1);
    Dijkstra(n, 2);

    for (int i = 1; i <= n; i++) {
        for (auto [j, w] : mp[i]) {
            int u = i, v = j;

            if (dist[u][1] + dist[v][2] > dist[v][1] + dist[u][2]) {
                swap(u, v);
            }

            if (dist[u][1] + w + dist[v][2] != dist[n][1]) {
                ans = min(ans, dist[u][1] + w + dist[v][2]);
            } else {
                again = min(again, w);
            }
        }
    }

    cout << min(ans, dist[n][1] + again * 2) << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}