#include <bits/stdc++.h>
using namespace std;

int n, m;

vector<int> mp[1000005];

// Tarjan Start

int         ti;
int         scc;
bool        in[1000005];
int         dfn[1000005];
int         low[1000005];
int         cnt1[1000005], cnt2[1000005];
int         scc_id[1000005];
int         scc_cnt[1000005];
stack<int>  st;
vector<int> scc_mp1[1000005], scc_mp2[1000005];

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
            scc_cnt[scc]++;
            if (t == u) {
                break;
            }
        }
    }
}

// Tarjan End

int ans;
int ck[1000005];
int uq[1000005];

int main() {

    // freopen("P11073.in", "r", stdin);
    // freopen("P11073.out", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    scanf("%d %d", &n, &m);

    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);

        mp[u].push_back(v);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (auto j : mp[i]) {
            if (scc_id[i] != scc_id[j] && uq[i] != j) {
                uq[i] = j;
                scc_mp1[scc_id[i]].push_back(scc_id[j]);
                scc_mp2[scc_id[j]].push_back(scc_id[i]);
            }
        }
    }

    int now = 0;
    for (int x = 1; x <= scc; x++) {
        now++;
        for (int y : scc_mp1[x]) {
            if (y < x) {
                if (cnt1[y] == 0) now--;
                cnt1[y]++;
            }
        }
        if (now >= 2) { ck[x]++; }
    }

    now = 0;
    for (int x = scc; x >= 1; x--) {
        now++;
        for (int y : scc_mp2[x]) {
            if (y > x) {
                if (cnt2[y] == 0) now--;
                cnt2[y]++;
            }
        }
        if (now >= 2) { ck[x]++; }
    }

    for (int i = 1; i <= scc; i++) {
        if (!ck[i]) ans += scc_cnt[i];
    }

    printf("%d", ans);

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}