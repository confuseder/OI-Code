#include <bits/stdc++.h>
using namespace std;

int n, ti;
vector<int> mp[105];

bool in[105];
int dfn[105];
int low[105];
int dist[105];
stack<int> st;

int scc;
int scc_id[105];
vector<int> scc_mp[105];
int cntr[105];
int cntc[105];

int ansA, ansB;

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
        scc++;
        while (true) {
            int v = st.top();
            st.pop();
            in[v]     = false;
            scc_id[v] = scc;
            if (v == u) {
                break;
            }
        }
    }
}

int main() {

    // freopen("P2746.in", "r", stdin);
    // freopen("P2746.out", "w", stdout);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        int u;
        while (cin >> u && u != 0) {
            mp[i].emplace_back(u);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    for (int i = 1; i <= n; i++) {
        for (auto v : mp[i]) {
            if (scc_id[i] != scc_id[v]) {
                cntr[scc_id[v]]++;
                cntc[scc_id[i]]++;
                scc_mp[scc_id[i]].emplace_back(scc_id[v]);
            }
        }
    }

    for (int i = 1; i <= scc; i++) {
        if (cntr[i] == 0) {
            ansA++;
        }
        if (cntc[i] == 0) {
            ansB++;
        }
    }

    cout << ansA << endl;
    cout << (scc != 1 ? max(ansA, ansB) : 0) << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}