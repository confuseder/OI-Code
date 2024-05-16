#include <bits/stdc++.h>
#include <cmath>
using namespace std;

int n, m;
int num[200005];
int cnt[200005];
int appr[200005];

int siz, block[200005];
int mx, now, ans[200005];

struct query {
    int id, l, r;
} q[200005];

void add(int x) {
    appr[cnt[num[x]]]--;
    cnt[num[x]]++;
    appr[cnt[num[x]]]++;
    now = max(now, cnt[num[x]]);
}

void del(int x) {
    appr[cnt[num[x]]]--;
    if (cnt[num[x]] == now && appr[cnt[num[x]]] == 0) {
        now--;
    }
    appr[--cnt[num[x]]]++;
}

int main() {

    // freopen("P3709.in", "r", stdin);
    // freopen("P3709.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> num[i];
    }

    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        q[i] = {i, l, r};
    }

    {
        siz = sqrt(n);

        for (int i = 1; i <= n + 1; i++) {
            block[i] = (i - 1) / siz + 1;
        }

        int tmp[200005];

        memcpy(tmp, num, sizeof(num));
        sort(tmp + 1, tmp + n + 2);
        long long len = unique(tmp + 1, tmp + n + 2) - (tmp + 1);
        for (int i = 1; i <= n + 1; i++) {
            num[i] = lower_bound(tmp + 1, tmp + len + 2, num[i]) - tmp;
        }

        sort(q + 1, q + m + 1, [&](query a, query b) {
            return ((block[a.l] == block[b.l]) ? (a.r < b.r) : (block[a.l] < block[b.l]));
        });
    }

    int l = 1, r = 0;

    for (int i = 1; i <= m; i++) {
        while (l < q[i].l) {
            del(l++);
        }
        while (l > q[i].l) {
            add(--l);
        }
        while (r < q[i].r) {
            add(++r);
        }
        while (r > q[i].r) {
            del(r--);
        }
        ans[q[i].id] = -now;
    }

    for (int i = 1; i <= m; i++) { cout << ans[i] << endl; }
    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}