#include <bits/stdc++.h>
using namespace std;

struct BC {
    int         len;
    vector<int> fa;

    BC() {}

    BC(int _n)
        : len(_n) {
        for (int i = 0; i <= _n + 2; i++) {
            fa.emplace_back(i);
        }
    }

    void clear() {
        for (int i = 0; i <= len + 2; i++) {
            fa[i] = i;
        }
    }

    int find(int x) {
        return (x == fa[x]) ? (x) : (fa[x] = find(fa[x]));
    }

    void merge(int x, int y) {
        fa[find(x)] = find(y);
    }
};

struct edge {
    int u, v, w;
    edge(){};
    edge(int _u, int _v, int _w)
        : u(_u), v(_v), w(_w){};
};

int n, m, s;
BC  bc(3000);

int stable_cnt, in_cnt[3000];

int main() {

    // freopen("P6628.in", "r", stdin);
    // freopen("P6628.out", "w", stdout);

    cin >> n >> m >> s;

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        in_cnt[u]++, in_cnt[v]++;
        stable_cnt += abs(u - v);
        bc.merge(u, v);
    }

    BC tmp = bc;

    for (int i = 1; i <= n; i++) {
        bc.clear();
        in_cnt[s]++, in_cnt[i]++;

        bc.merge(tmp.find(s), tmp.find(i));
        int ans = stable_cnt, pre = 0;

        for (int j = 1; j <= n; j++) {
            if (in_cnt[j] & 1) {
                if (pre) {
                    ans += j - pre;
                    for (int k = pre; k < j; k++) {
                        bc.merge(tmp.find(k), tmp.find(j));
                    }
                    pre = 0;
                } else {
                    pre = j;
                }
            }
        }

        vector<edge> g;
        for (int j = 1; j <= n; j++) {
            if (in_cnt[j]) {
                if (pre && bc.find(tmp.fa[j]) != bc.find(tmp.fa[pre]))
                    g.push_back({tmp.find(j), tmp.find(pre), abs(j - pre)});
                pre = j;
            }
        }

        sort(g.begin(), g.end(), [](edge a, edge b) {
            return a.w < b.w;
        });

        for (int sz = g.size(), j = 0; j < sz; j++) {
            if (bc.find(g[j].u) != bc.find(g[j].v)) {
                bc.fa[bc.find(g[j].u)] = bc.find(g[j].v);
                ans += g[j].w * 2;
            }
        }

        in_cnt[s]--, in_cnt[i]--;

        printf("%lld ", ans);
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}