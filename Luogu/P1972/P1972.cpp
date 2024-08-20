#include <bits/stdc++.h>
using namespace std;

#define lowbit(x) (x & -x)

int n, m;
int num[1000005];
int vis[1000005];
int tr[1000005];
int ans[1000005];

struct Q {
    int l, r, id;
} q[1000005];

void add(int p, int v) {

    while (p <= n) {
        tr[p] += v;
        p += lowbit(p);
    }
}

int query(int p) {
    int res = 0;

    while (p != 0) {
        res += tr[p];
        p -= lowbit(p);
    }

    return res;
}

int main() {

    // freopen("P1972.in", "r", stdin);
    // freopen("P1972.out", "w", stdout);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> num[i];
    }

    cin >> m;

    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;

        q[i] = {l, r, i};
    }

    sort(q + 1, q + m + 1, [](auto a, auto b) -> bool {
        return a.r < b.r;
    });

    for (int i = 1, r = 1; i <= m; i++) {
        for (; r <= q[i].r; r++) {
            if (vis[num[r]]) {
                add(vis[num[r]], -1);
            }

            add(r, 1);
            vis[num[r]] = r;
        }

        ans[q[i].id] = query(q[i].r) - query(q[i].l - 1);
    }

    for (int i = 1; i <= m; i++) {
        cout << ans[i] << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}