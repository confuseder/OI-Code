#include <bits/stdc++.h>
using namespace std;

struct line {
    int to, w, fb;
};

int n, m, s, t;
vector<line> mp[500];

bool inq[500];
struct Pre {
    int from, edge;
} pre[500];

void add(int u, int v, int w) {
    mp[v].push_back({u, 0, int(mp[u].size())});
    mp[u].push_back({v, w, int(mp[v].size() - 1)});
}

bool zg() {

    queue<int> q;
    memset(inq, false, sizeof(inq));
    fill(pre, pre + n + 2, Pre{0, 0});

    inq[s] = 1;
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

long long ek() {
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

    // freopen("P2756.in", "r", stdin);
    // freopen("P2756.out", "w", stdout);

    int n, m;

    cin >> m >> n;

    s = 200, t = 201;

    for (int i = m + 1; i <= n; i++) {
        add(s, i, 1);
    }

    for (int i = 1; i <= m; i++) {
        add(i, t, 1);
    }

    while (true) {
        int u, v;
        cin >> u >> v;

        if (u == -1 && v == -1) {
            break;
        }

        add(v, u, 1);
    }

    cout << ek() << endl;

    for (int i = 1; i <= m; i++) {
        for (auto j : mp[i]) {
            if (j.to >= m + 1 && j.to <= n && mp[j.to][j.fb].w == 0) {
                cout << i << ' ' << j.to << endl;
                break;
            }
        }
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}