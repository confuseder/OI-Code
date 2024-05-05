#include <bits/stdc++.h>
using namespace std;

struct q {
    int       id, l, r;
    long long a, b;
};

int       n, m;
int       color[50005];
long long s[50005], ans, pos[50005];
q         query[50005];

void update(int p, int add) {
    ans -= s[color[p]] * s[color[p]];
    s[color[p]] += add;
    ans += s[color[p]] * s[color[p]];
}

void solve() {
    for (int i = 1, l = 1, r = 0; i <= m; i++) {
        for (; r < query[i].r; r++) {
            update(r + 1, 1);
        }
        for (; r > query[i].r; r--) {
            update(r, -1);
        }
        for (; l < query[i].l; l++) {
            update(l, -1);
        }
        for (; l > query[i].l; l--) {
            update(l - 1, 1);
        }

        if (query[i].l == query[i].r) {
            query[i].a = 0;
            query[i].b = 1;
            continue;
        }

        query[i].a  = ans - (query[i].r - query[i].l + 1);
        query[i].b  = (query[i].r - query[i].l + 1) * 1LL * (query[i].r - query[i].l);
        long long g = __gcd(query[i].a, query[i].b);
        query[i].a /= g;
        query[i].b /= g;
    }
}

int main() {

    // freopen("P1494.in", "r", stdin);
    // freopen("P1494.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> color[i];
    }

    int block = sqrt(n);

    for (int i = 1; i <= n; i++) {
        pos[i] = (i - 1) / block + 1;
    }

    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;

        query[i] = {i, x, y, 0, 0};
    }

    sort(query + 1, query + m + 1, [&](q a, q b) {
        if (pos[a.l] == pos[b.l]) {
            return a.r < b.r;
        }
        return a.l < b.l;
    });

    solve();

    sort(query + 1, query + m + 1, [&](q a, q b) {
        return a.id < b.id;
    });

    for (int i = 1; i <= m; i++) {
        cout << query[i].a << '/' << query[i].b << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}