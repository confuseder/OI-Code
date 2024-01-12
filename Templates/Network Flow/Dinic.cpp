#include <bits/stdc++.h>
using namespace std;

int n, m, s, t;

struct Dinic {
    struct line {
        int to;
        long long w;
        int fb;
    };

    int n, s, t;
    vector<vector<line>> mp;
    vector<int> cur;
    vector<long long> dep;
    vector<bool> inq;

    Dinic(int _n, int _s, int _t) : n(_n), s(_s), t(_t) {
        mp.resize(n + 10, {});
        cur.resize(n + 10, 0);
    }

    Dinic() {}

    void add(int u, int v, long long w) {
        mp[v].push_back({u, 0, int(mp[u].size())});
        mp[u].push_back({v, w, int(mp[v].size() - 1)});
    }

    bool fc() {
        dep.clear();
        inq.clear();
        dep.resize(n + 10, 1e9);
        inq.resize(n + 10, false);
        queue<int> q;

        dep[s] = 0;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = false;
            cur[u] = 0;

            for (auto &i : mp[u]) {
                if (dep[i.to] > dep[u] + 1 && i.w > 0) {
                    dep[i.to] = dep[u] + 1;
                    if (!inq[i.to]) {
                        q.push(i.to);
                        inq[i.to] = true;
                    }
                }
            }
        }

        return !(dep[t] == 1e9);
    }

    long long dfs(int u, long long flow) {
        // cout << u << endl;
        long long ans = 0;
        if (u == t) {
            return flow;
        }

        for (; cur[u] < mp[u].size(); cur[u]++) {
            int v = mp[u][cur[u]].to;

            if (mp[u][cur[u]].w > 0 && dep[v] == dep[u] + 1) {
                if ((ans = dfs(v, min(flow, mp[u][cur[u]].w)))) {
                    mp[u][cur[u]].w -= ans;
                    mp[mp[u][cur[u]].to][mp[u][cur[u]].fb].w += ans;
                    return ans;
                }
            }
        }

        return 0;
    }

    long long work() {
        long long low = 0, mx = 0;
        while (fc()) {
            while ((low = dfs(s, 1e9))) {
                mx += low;
            }
        }
        return mx;
    }
} dinic;

int main() {

    // freopen("Dinic.in", "r", stdin);
    // freopen("Dinic.out", "w", stdout);

    cin >> n >> m >> s >> t;

    dinic = Dinic(n, s, t);

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        dinic.add(u, v, w);
    }

    cout << dinic.work();

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}