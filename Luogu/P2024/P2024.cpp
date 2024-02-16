#include <bits/stdc++.h>
using namespace std;

int n, m, ans;
int f[200005], v[200005];

int find(int x) {
    if (f[x] == x) {
        return f[x];
    }

    int fa = f[x];
    f[x]   = find(f[x]);
    v[x]   = (v[x] + v[fa]) % 3;

    return f[x];
}

bool check(int op, int x, int y) {
    int fx = find(x), fy = find(y);

    if (fx == fy) {
        if (op == 1 && v[x] != v[y]) {
            return false;
        }
        if (op == 2 && (3 - v[x] + v[y]) % 3 != 2) {
            return false;
        }
    }

    f[fx] = fy;
    if (op == 1) {
        v[fx] = (3 + v[y] - v[x]) % 3;
    } else {
        v[fx] = (3 + 1 + v[y] - v[x]) % 3;
    }

    return true;
}

int main() {

    // freopen("P2024.in", "r", stdin);
    // freopen("P2024.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        f[i] = i;
    }

    for (int i = 1; i <= m; i++) {
        int op, x, y;
        cin >> op >> x >> y;

        if (x > n || y > n || (op == 2 && x == y)) {
            ans++;
        } else {
            ans += !check(op, x, y);
        }
    }

    cout << ans << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}