#include <bits/stdc++.h>
using namespace std;

int n, m, ans;
bool cut[20005];
int dfn[20005], low[20005], ti;
vector<int> mp[20005];
stack<int> st;

void tarjan(int u, int anc) {
    dfn[u] = low[u] = ++ti;
    int child       = 0;

    for (int v : mp[u]) {
        if (!dfn[v]) {
            tarjan(v, anc);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u] && u != anc) {
                cut[u] = true;
            }
            if (u == anc) {
                child++;
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (child >= 2 && u == anc) {
        cut[u] = true;
    }
}

int main() {

    // freopen("P3388.in", "r", stdin);
    // freopen("P3388.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        mp[u].push_back(v);
        mp[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            tarjan(i, i);
        }
    }

    for (int i = 1; i <= n; i++) {
        if (cut[i]) {
            ans++;
        }
    }

    cout << ans << endl;

    for (int i = 1; i <= n; i++) {
        if (cut[i]) {
            cout << i << ' ';
        }
    }

    cout << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}