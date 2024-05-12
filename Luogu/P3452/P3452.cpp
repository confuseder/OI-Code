#include <bits/stdc++.h>
using namespace std;

long long p, m, n;
string    str;
long long sum[200005];
long long ans[200005];

// moe queue

long long siz, now;
long long block_num[200005];
long long cnt[200005];
long long tmp[200005];

struct query {
    long long id, l, r;
} q[200005];

void add(long long x) {
    now += cnt[sum[x]];
    cnt[sum[x]]++;
}

void del(long long x) {
    cnt[sum[x]]--;
    now -= cnt[sum[x]];
}

void solve() {

    struct date {
        long long d, id;
    } s[200005];

    long long i, l, r, tot, mus;
    for (i = 1; i <= n; i++) {
        s[i] = s[i - 1];
        if ((str[i - 1] - '0') % p == 0) {
            s[i].d += i;
            s[i].id++;
        }
    }
    while (m--) {
        cin >> l >> r;
        tot = s[r].d - s[l - 1].d;
        mus = (l - 1) * (s[r].id - s[l - 1].id);
        printf("%lld\n", tot - mus);
    }

    exit(0);
}

int main() {

    // freopen("P3452.in", "r", stdin);
    // freopen("P3452.out", "w", stdout);

    cin >> p >> str >> m;

    n = str.length();

    if (p == 2 || p == 5) {
        solve();
    }

    for (int i = 1; i <= m; i++) {
        cin >> q[i].l >> q[i].r;
        q[i].r += 1;
        q[i].id = i;
    }

    long long pp = 1;

    for (int i = n - 1; i >= 0; i--) {
        sum[i + 1] = (sum[i + 2] % p) + (str[i] - '0') * pp % p;
        pp *= 10;
        pp %= p;
        sum[i + 1] %= p;
    }

    // init
    {
        siz = sqrt(n);

        for (int i = 1; i <= n + 1; i++) {
            block_num[i] = (i - 1) / siz + 1;
        }

        sort(q + 1, q + m + 1, [&](query &a, query &b) {
            return ((block_num[a.l] == block_num[b.l]) ? (a.r < b.r) : (block_num[a.l] < block_num[b.l]));
        });

        memcpy(tmp, sum, sizeof(sum));
        sort(tmp + 1, tmp + n + 2);
        long long len = unique(tmp + 1, tmp + n + 2) - (tmp + 1);
        for (int i = 1; i <= n + 1; i++) {
            sum[i] = lower_bound(tmp + 1, tmp + len + 2, sum[i]) - tmp;
        }
    }

    long long l = 1, r = 0;

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
        ans[q[i].id] = now;
    }

    for (long long i = 1; i <= m; i++) { cout << ans[i] << endl; }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}