#include <bits/stdc++.h>
using namespace std;

struct node {
    int dist, id;
};

struct cmp {
    bool operator()(node a, node b) { return a.dist > b.dist; }
};

int n, m, ti;
vector<pair<int, int>> mp[200005];
stack<int> st;
bool in[200005];
int dfn[200005];
int low[200005];

int scc;
int cnt[200005];
int scc_id[200005];
vector<pair<int, int>> scc_mp[200005];

int dist[200005];
int vis[200005];
priority_queue<node, vector<node>, cmp> q;

void tarjan(int u) {
    st.push(u);
    in[u]  = true;
    dfn[u] = low[u] = ++ti;

    for (auto [v, dist] : mp[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (in[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        ++scc;
        while (true) {
            int now = st.top();
            st.pop();
            in[now]     = false;
            scc_id[now] = scc;
            if (now == u) {
                break;
            }
        }
    }
}

void dij(int s) {
    memset(dist, 0x3f, sizeof(dist));
    dist[s] = 0;
    q.push({0, s});

    while (q.size()) {
        auto [dis, u] = q.top();
        q.pop();

        if (vis[u]) {
            continue;
        }

        vis[u] = true;

        for (auto [v, w] : scc_mp[u]) {
            dist[v] = min(dist[v], w + dis);
            if (!vis[v]) {
                q.push({dist[v], v});
            }
        }
    }
}

int main() {

    // freopen("P2169.in", "r", stdin);
    // freopen("P2169.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        mp[u].push_back({v, w});
    }

    tarjan(1);

    for (int i = 1; i <= n; i++) {
        for (auto [v, d] : mp[i]) {
            if (scc_id[i] != scc_id[v]) {
                scc_mp[scc_id[i]].push_back({scc_id[v], d});
            }
        }
    }

    dij(scc_id[1]);

    cout << dist[scc_id[n]] << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}