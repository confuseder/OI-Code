#include <bits/stdc++.h>
using namespace std;

struct line {
    int to, w, fb;
};

int n, m, s, t;
vector<line> mp[205];

bool inq[205];
struct Pre {
    int from, edge;
} pre[205];

void add(int u, int v, int w) {
    mp[u].emplace_back(v, w, mp[v].size());
    mp[v].emplace_back(u, 0, mp[u].size() - 1);
}

bool zg() {

    queue<int> q;
    memset(inq, false, sizeof(inq));
    fill(pre, pre + n + 2, Pre{0, 0});

    inq[s] = true;
    q.push(s);

    while (!q.empty()) {
        int now = q.front();
        q.pop();

        for (int i = 0; i < mp[now].size(); i++) {
            int v = mp[now][i].to;

            if (!inq[v] && mp[now][i].w != 0) {
                pre[v].from = now;
                pre[v].edge = i;

                if (v == t) {
                    return true;
                }

                inq[v] = true;
                q.push(v);
            }
        }
    }

    return false;
}

int ek() {
    int ans = 0;
    while (zg()) {
        int mi = 1e9;
        for (int i = t; i != s; i = pre[i].from) {
            mi = min(mi, mp[pre[i].from][pre[i].edge].w);
        }
        for (int i = t; i != s; i = pre[i].from) {
            mp[pre[i].from][pre[i].edge].w -= mi;
            mp[i][mp[pre[i].from][pre[i].edge].fb].w += mi;
        }
        ans += mi;
    }
    return ans;
}

int main() {

    // freopen("P1345.in", "r", stdin);
    // freopen("P1345.out", "w", stdout);

    cin >> n >> m >> s >> t;

    for (int i = 1; i <= n; i++) {
        if (i == s || i == t) {
            add(i, i + n, 1e9);
        } else {
            add(i, i + n, 1);
        }
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;

        add(u + n, v, 1e9);
        add(v + n, u, 1e9);
    }

    cout << ek() << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}