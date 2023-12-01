#include <bits/stdc++.h>
using namespace std;

int n, k;
int f[200005];
int val[200005];

int main() {

    // freopen("P2441.in", "r", stdin);
    // freopen("P2441.out", "w", stdout);

    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        cin >> val[i];
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        f[v] = u;
    }

    for (int i = 1; i <= k; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int u;
            cin >> u;
            int now = f[u];
            while (true) {
                if (now == 0) {
                    cout << -1 << endl;
                    goto nxt;
                }
                if (__gcd(val[now], val[u]) != 1) {
                    cout << now << endl;
                    goto nxt;
                }
                now = f[now];
            }
        nxt:
            continue;
        } else {
            int u, v;
            cin >> u >> v;
            val[u] = v;
        }
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}