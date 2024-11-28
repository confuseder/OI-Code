#include <bits/stdc++.h>
using namespace std;

#define T 100001
#define F -100001
#define U 0

int ans;
int c, t;
int n, m;

int  f[100005];
bool vis[200005];

int find(int x) {
    if (x == T || x == F) {
        return x;
    }

    if (vis[n - x] || x == U) {
        return U;
    }

    if (vis[n + x]) {
        return T;
    }

    int re = 0;

    if (x < 0) {
        if (x == -f[-x]) return x;
        else {
            vis[x + n] = 1;
            re         = find(-f[-x]);
            vis[x + n] = 0;
        }
    } else {
        if (x == f[x]) return x;
        else {
            vis[x + n] = 1;
            re = f[x]  = find(f[x]);
            vis[x + n] = 0;
        }
    }

    return re;
}

int main() {

    // freopen("P9869.in", "r", stdin);
    // freopen("P9869.out", "w", stdout);

    cin >> c >> t;

    while (t--) {
        cin >> n >> m;

        ans = 0;
        for (int i = 1; i <= n; i++) {
            f[i] = i;
        }
        memset(vis, false, sizeof(vis));

        for (int i = 1; i <= m; i++) {
            char op;
            cin >> op;

            if (op == 'T') {
                int a;
                cin >> a;

                f[a] = T;
            } else if (op == 'F') {
                int a;
                cin >> a;

                f[a] = F;
            } else if (op == 'U') {
                int a;
                cin >> a;

                f[a] = U;
            } else {
                int a, b;
                cin >> a >> b;

                if (op == '+') {
                    f[a] = f[b];
                } else {
                    f[a] = -f[b];
                }
            }
        }

        for (int i = 1; i <= n; i++) {
            if (find(i) == U) {
                ans++;
            }
        }

        cout << ans << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}