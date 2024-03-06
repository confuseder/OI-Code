#include <bits/stdc++.h>
using namespace std;

int            n, m, cnt;
vector<int>    mp[100005], scc_mp[100005];
bitset<100005> uniq[100005];
int            inv[100005];

/* tarjan define start */
bool       in[100005];
int        scc, ti, dfn[100005], low[100005], scc_id[100005], scc_size[100005];
stack<int> st;

void tarjan(int u) {
    st.push(u);
    in[u]  = true;
    dfn[u] = low[u] = ++ti;

    for (auto v : mp[u]) {
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
            int t = st.top();
            st.pop();
            in[t]     = false;
            scc_id[t] = scc;
            scc_size[scc]++;
            if (t == u) {
                break;
            }
        }
    }
}

/* tarjan define end */

int main() {

    // freopen("P4819.in", "r", stdin);
    // freopen("P4819.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        mp[u].push_back(v);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (auto j : mp[i]) {
            if (scc_id[i] != scc_id[j] && !uniq[scc_id[i]][scc_id[j]]) {
                scc_mp[scc_id[i]].push_back(scc_id[j]);
                uniq[scc_id[i]][scc_id[j]] = true;
                inv[scc_id[j]]++;
            }
        }
    }

    bool flag = true;
    for (int i = 1; i <= scc; i++) {
        if (!inv[i]) { cnt++; }
        if (inv[i] || scc_size[i] > 1) { continue; }
        if (flag) {
            bool pp = true;
            for (auto j : scc_mp[i]) {
                if (inv[j] <= 1) {
                    pp = false;
                    break;
                }
            }
            if (pp) {
                cnt--;
                flag = false;
            }
        }
    }

    printf("%.6lf", (double)(n - cnt) / n);

    // fclose(stdin);
    // fcl ose(stdout);

    // system("pause");

    return 0;
}