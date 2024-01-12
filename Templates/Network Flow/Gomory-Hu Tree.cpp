#include <bits/stdc++.h>
using namespace std;

int n, m, q;

struct Dinic {
    struct line {
        int to;
        int w;
        int fb;
        bool type;
    };

    int n, s, t;
    vector<vector<line>> mp;
    vector<int> cur;
    vector<int> dep;
    vector<bool> inq;
    vector<bool> block;

    Dinic(int _n, int _s, int _t) : n(_n), s(_s), t(_t) {
        mp.resize(n + 10, {});
        cur.resize(n + 10, 0);
    }

    Dinic() {}

    void add(int u, int v, int w) {
        mp[v].push_back({u, 0, int(mp[u].size()), false});
        mp[u].push_back({v, w, int(mp[v].size() - 1), true});
    }

    bool fc() {
        dep.clear();
        inq.clear();
        block.clear();
        dep.resize(n + 10, 1e9);
        inq.resize(n + 10, false);
        block.resize(n + 10, false);
        queue<int> q;

        dep[s]   = 0;
        block[s] = true;
        q.push(s);

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u]   = false;
            block[u] = true;
            cur[u]   = 0;

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

    int dfs(int u, int flow) {
        int ans = 0;
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

    int work() {
        for (int i = 1; i <= n; i++) {
            for (auto &j : mp[i]) {
                if (j.type) {
                    j.w += mp[j.to][j.fb].w;
                    mp[j.to][j.fb].w = 0;
                }
            }
        }

        int low = 0, mx = 0;
        while (fc()) {
            while ((low = dfs(s, 1e9))) {
                mx += low;
            }
        }
        return mx;
    }
} dinic;

struct GHT {

    struct line {
        int to, w;
    };

    int n;
    vector<vector<line>> tree;
    vector<vector<int>> ans;
    vector<int> node;
    Dinic dinic;

    GHT(int _n) : n(_n) {
        dinic = Dinic(4 * n + 10, 0, 0);
        tree.resize(n + 10, {});
        node.resize(n + 10);
        ans.resize(n + 10, vector<int>(n + 10, 0));
    }

    GHT() {}

    void work(int l, int r) {

        if (l == r) {
            return;
        }

        dinic.s = node[l], dinic.t = node[l + 1];
        int ts = dinic.s, tt = dinic.t;
        int num = dinic.work();

        vector<int> bufferA, bufferB;

        for (int i = l; i <= r; i++) {
            if (dinic.block[node[i]]) {
                bufferA.push_back(node[i]);
            } else {
                bufferB.push_back(node[i]);
            }
        }

        for (int i = 0; i < bufferA.size(); i++) {
            node[l + i] = bufferA[i];
        }
        for (int i = 0; i < bufferB.size(); i++) {
            node[l + bufferA.size() + i] = bufferB[i];
        }

        work(l, l + bufferA.size() - 1);
        work(l + bufferA.size(), r);

        tree[ts].emplace_back(tt, num);
        tree[tt].emplace_back(ts, num);

        return;
    }

    void get(int now, int fa, int gen, int dis) {
        ans[now][gen] = dis;
        for (auto i : tree[now]) {
            if (i.to != fa) {
                get(i.to, now, gen, min(dis, i.w));
            }
        }
    }

    int ask(int x, int y) { return ans[x][y]; }

    void solve() {
        work(1, n);
        for (int i = 1; i <= n; i++)
            get(i, 0, i, 1e9);
    }

} ght;

int main() {

    // freopen("Gomory-Hu Tree.in", "r", stdin);
    // freopen("Gomory-Hu Tree.out", "w", stdout);

    cin >> n >> m;

    ght = GHT(n);

    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;

        ght.dinic.add(u, v, w);
        ght.dinic.add(v, u, w);
    }

    for (int i = 1; i <= n; i++) {
        ght.node[i] = i;
    }

    ght.solve();

    cin >> q;

    while (q--) {
        int u, v;
        cin >> u >> v;

        cout << ght.ask(u, v) << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}