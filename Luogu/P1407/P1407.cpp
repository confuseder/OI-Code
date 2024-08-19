#include <bits/stdc++.h>
using namespace std;

int                    n, m;
map<string, int>       people;
vector<pair<int, int>> fq;

vector<int> mp[10005];

int        ti;
bool       in[10005];
int        dfn[10005];
int        low[10005];
int        scc;
int        scc_id[10005];
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
            if (t == u) {
                break;
            }
        }
    }
}

int main() {

    // freopen("P1407.in", "r", stdin);
    // freopen("P1407.out", "w", stdout);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        string u, v;
        cin >> u >> v;
        people[u] = 2 * i;
        people[v] = 2 * i - 1;

        mp[people[u]].push_back(people[v]);
        fq.push_back({people[u], people[v]});
    }

    cin >> m;

    for (int i = 1; i <= m; i++) {
        string u, v;
        cin >> u >> v;

        mp[people[v]].push_back(people[u]);
    }

    for (int i = 1; i <= 2 * n; i++) {
        if (!dfn[i]) {
            tarjan(i);
        }
    }

    for (auto [u, v] : fq) {
        if (scc_id[u] == scc_id[v]) {
            cout << "Unsafe" << endl;
        } else {
            cout << "Safe" << endl;
        }
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}