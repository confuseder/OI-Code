#include <bits/stdc++.h>
using namespace std;

struct element {
    char c;
    bool tag;
    int  child[26];
    int  dp;
    int  cnt;
};

int     id;
element tire[3000005];

void insert(string s) {
    int now = 0;

    for (auto i : s) {
        if (tire[now].child[i - 'a'] == 0) {
            tire[now].child[i - 'a'] = ++id;
        }
        now = tire[now].child[i - 'a'];
    }

    tire[now].tag = true;
    tire[now].cnt++;
}

int n;
int ans;

void dfs(int u) {
    int siz = 0, mx1 = 0, mx2 = 0;

    for (int d = 0; d < 26; d++) {
        int v = tire[u].child[d];

        if (v) {
            dfs(v);
            siz += tire[v].cnt;
            if (mx1 < tire[v].dp) {
                mx2 = mx1;
                mx1 = tire[v].dp;
            } else if (mx2 < tire[v].dp) {
                mx2 = tire[v].dp;
            }
        }
    }

    if (tire[u].cnt) {
        tire[u].dp = mx1 + max(siz, 1);
    }

    ans = max(ans, mx1 + mx2 + tire[u].cnt + max(siz - 2, 0));
}

int main() {

    // freopen("P7537.in", "r", stdin);
    // freopen("P7537.out", "w", stdout);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;
        reverse(s.begin(), s.end());
        insert(s);
    }

    dfs(0);

    cout << ans << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}