#include <bits/stdc++.h>
using namespace std;

struct node {
    bool x;
    int  child[5];

    node() {}

    node(bool _x)
        : x(_x) {}
};

int                    n;
int                    xorf[100005];
int                    cnt = 1, ans;
node                   tire[3200005];
vector<pair<int, int>> mp[100005];

string itos(int x) {
    bitset<32> bit(x);
    return bit.to_string();
}

void len(int u, int d, int f) {
    xorf[u] = d;
    for (auto [v, w] : mp[u]) {
        if (v == f) {
            continue;
        }
        len(v, d ^ w, u);
    }
}

void insert(int val) {
    int x = 1;
    for (int i = (1 << 30); i; i >>= 1) {
        bool c = val & i;
        if (!tire[x].child[c]) {
            tire[x].child[c] = ++cnt;
        }
        x = tire[x].child[c];
    }
}

int query(int val) {
    int now = 1, tot = 0;

    for (int i = (1 << 30); i; i >>= 1) {
        bool c = val & i;
        if (tire[now].child[!c]) {
            tot += i;
            now = tire[now].child[!c];
        } else {
            now = tire[now].child[c];
        }
    }

    return tot;
}

int main() {

    // freopen("P4551.in", "r", stdin);
    // freopen("P4551.out", "w", stdout);

    cin >> n;

    for (int i = 1; i <= n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        mp[u].emplace_back(v, w);
        mp[v].emplace_back(u, w);
    }

    len(1, 0, 0);

    for (int i = 1; i <= n; i++) {
        insert(xorf[i]);
    }

    for (int i = 1; i <= n; ++i) {
        ans = max(ans, query(xorf[i]));
    }

    cout << ans << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}