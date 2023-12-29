#include <bits/stdc++.h>
using namespace std;

struct line {
    long long to, w, cos, fb;
};

int n, m, s, t;
vector<line> mp[5005];
int cb[5005][5005];

bool inq[5005];
struct Pre {
    int from, edge;
};

Pre pre[5005];
long long dist[5005];

bool zg() {
    queue<int> q;
    memset(inq, false, sizeof(inq));
    memset(dist, 127, sizeof(dist));
    fill(pre, pre + n + 2, Pre{0, 0});

    inq[s]  = 1;
    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int now  = q.front();
        inq[now] = false;
        q.pop();

        for (int i = 0; i < mp[now].size(); i++) {
            int v    = mp[now][i].to;
            int cost = mp[now][i].cos;

            if (mp[now][i].w > 0 && dist[v] > dist[now] + cost) {
                dist[v]     = dist[now] + cost;
                pre[v].from = now;
                pre[v].edge = i;
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = true;
                }
            }
        }
    }

    return !(dist[t] > 1e17);
}

pair<long long, long long> ek() {
    long long ans = 0, cost = 0;
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
        cost += mi * dist[t];
    }
    return {ans, cost};
}

int main() {

    // freopen("P3381.in", "r", stdin);
    // freopen("P3381.out", "w", stdout);

    memset(cb, -1, sizeof(cb));

    cin >> n >> m >> s >> t;

    for (int i = 1; i <= m; i++) {
        long long u, v, w, h;
        scanf("%lld %lld %lld %lld", &u, &v, &w, &h);

        mp[v].push_back({u, 0, -h, int(mp[u].size())});
        mp[u].push_back({v, w, h, int(mp[v].size() - 1)});
    }

    auto ans = ek();

    cout << ans.first << " " << ans.second << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}
