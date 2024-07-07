#include <bits/stdc++.h>
using namespace std;

struct node {
    int x, y;

    double operator+(node a) {
        return sqrt(pow(a.x - x, 2) + pow(a.y - y, 2));
    }
};

struct line {
    int    to;
    double w;
};

struct dijNode {
    double dis;
    int    u;

    bool operator>(const dijNode& a) const {
        return dis > a.dis;
    }
};

int n, m;

node          nodes[205];
map<int, int> del;
vector<line>  mp[10005];

double dist[205], ans = 1e9;
bool   vis[205];

void Dijkstra(int x, int y) {

    priority_queue<dijNode, vector<dijNode>, greater<dijNode> > q;
    fill(dist, dist + 202, 0x3f3f3f3f);

    dist[1] = 0;
    q.push({0, 1});

    while (q.size()) {
        auto [d, u] = q.top();
        q.pop();

        if (dist[u] != d) {
            continue;
        }

        for (auto i : mp[u]) {
            if ((u == x && i.to == y) || (u == y && i.to == x)) {
                continue;
            }

            if (dist[i.to] <= d + i.w) {
                continue;
            }

            if (x == -1 && y == -1) {
                del[i.to] = u;
            }

            dist[i.to] = d + i.w;

            q.push({dist[i.to], i.to});
        }
    }
}

int main() {

    // freopen("P1491.in", "r", stdin);
    // freopen("P1491.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;

        nodes[i] = {x, y};
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;

        mp[u].emplace_back(v, nodes[u] + nodes[v]);
        mp[v].emplace_back(u, nodes[u] + nodes[v]);
    }

    Dijkstra(-1, -1);

    for (int i = n; i != 1; i = del[i]) {
        if (i == 1) {
            continue;
        }

        Dijkstra(i, del[i]);
        ans = min(ans, dist[n]);
    }

    if (ans >= 0x3f3f3f3f) {
        cout << -1 << endl;
    } else {
        printf("%.2lf\n", ans);
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}