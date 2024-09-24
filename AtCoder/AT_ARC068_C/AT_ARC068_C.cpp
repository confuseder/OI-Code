#include <bits/stdc++.h>
using namespace std;

#define lowbit(x) (x & -x)

int n, m;

pair<int, int> d[300005];

int tr[300005];

void add(int i, int v) {
    for (; i < 300005; i += lowbit(i)) {
        tr[i] += v;
    }
}

int query(int i) {
    int res = 0;
    for (; i; i ^= lowbit(i)) {
        res += tr[i];
    }
    return res;
}

void _add(int l, int r) {
    add(l, 1);
    add(r + 1, -1);
}

int main() {

    // freopen("AT_ARC068_C.in", "r", stdin);
    // freopen("AT_ARC068_C.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        int l, r;
        cin >> l >> r;

        d[i] = {l, r};
    }

    sort(d + 1, d + n + 1, [](pair<int, int> a, pair<int, int> b) {
        return (a.second - a.first) > (b.second - b.first);
    });

    int now = n;

    for (int i = 1; i <= m; i++) {
        while (now && d[now].second - d[now].first + 1 < i) {
            _add(d[now].first, d[now].second);
            now--;
        }
        int ans = now;
        for (int j = 0; j <= m; j += i) {
            ans += query(j);
        }
        cout << ans << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}
