#include <bits/stdc++.h>
using namespace std;

struct line {
    int to;
    long long w;
    int fb;
};

int n, m, s, t;
vector<line> mp[205];
int cb[205][205];

bool inq[100005];
struct Pre {
    int from, edge;
};

Pre pre[100005];

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
    long long ans = 0;
    while (zg()) {
        long long mi = 1e9;
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

    // freopen("P3376.in", "r", stdin);
    // freopen("P3376.out", "w", stdout);

    memset(cb, -1, sizeof(cb));

    cin >> n >> m >> s >> t;

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);

        if (cb[u][v] == -1) {
            mp[v].push_back({u, 0, int(mp[u].size())});
            mp[u].push_back({v, w, int(mp[v].size() - 1)});
            cb[u][v] = mp[u].size() - 1;
        } else {
            mp[u][cb[u][v]].w += w;
        }
    }

    cout << ek() << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}