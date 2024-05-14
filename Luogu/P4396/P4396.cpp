#include <bits/stdc++.h>
using namespace std;

#define lowbit(x) (x & -x)

int n, m, v = 100005;

int num[200010];

int            cnt_tree[200010], appr_tree[200010];
int            appr[200010];
int            siz, block[200010];
pair<int, int> ans[200010];

struct query {
    int id, l, r, a, b;
} q[200010];

void add_cnt(int x, int n) {
    for (; x <= v; x += lowbit(x)) {
        cnt_tree[x] += n;
    }
}

int query_cnt(int x) {
    int as = 0;
    for (; x > 0; x -= lowbit(x)) {
        as += cnt_tree[x];
    }
    return as;
}

void add_appr(int x, int n) {
    if ((n == 1 && appr[x] != 0) || (n == -1 && appr[x] != 1)) {
        return;
    }

    for (; x <= v; x += lowbit(x)) {
        appr_tree[x] += n;
    }
}

int query_appr(int x) {
    int ans = 0;
    for (; x > 0; x -= lowbit(x)) {
        ans += appr_tree[x];
    }
    return ans;
}

void add(int x) {
    add_cnt(x, 1);
    add_appr(x, 1);
    appr[x]++;
}

void del(int x) {
    add_cnt(x, -1);
    add_appr(x, -1);
    appr[x]--;
}

int main() {

    // freopen("P4396.in", "r", stdin);
    // freopen("P4396.out", "w", stdout);

    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &num[i]);
    }

    for (int i = 1; i <= m; i++) {
        int l, r, a, b;

        scanf("%d %d %d %d", &l, &r, &a, &b);
        q[i] = {i, l, r, a, b};
    }

    {

        siz = sqrt(n);

        for (int i = 1; i <= n + 1; i++) {
            block[i] = (i - 1) / siz + 1;
        }

        sort(q + 1, q + m + 1, [&](query &a, query &b) {
            return ((block[a.l] == block[b.l]) ? (a.r < b.r) : (block[a.l] < block[b.l]));
        });
    }

    for (int i = q[1].l; i <= q[1].r; i++) { add(num[i]); }
    ans[q[1].id] = {query_cnt(q[1].b) - query_cnt(q[1].a - 1),
                    query_appr(q[1].b) - query_appr(q[1].a - 1)};

    for (int i = 2; i <= m; i++) {
        if (q[i - 1].l < q[i].l) {
            for (int j = q[i - 1].l; j < q[i].l; j++) { del(num[j]); }
        } else {
            for (int j = q[i].l; j < q[i - 1].l; j++) { add(num[j]); }
        }
        if (q[i - 1].r < q[i].r) {
            for (int j = q[i - 1].r + 1; j <= q[i].r; j++) { add(num[j]); }
        } else {
            for (int j = q[i].r + 1; j <= q[i - 1].r; j++) { del(num[j]); }
        }

        ans[q[i].id] = {(query_cnt(q[i].b) - query_cnt(q[i].a - 1)),
                        (query_appr(q[i].b) - query_appr(q[i].a - 1))};
    }

    for (int i = 1; i <= m; i++) {
        printf("%d %d\n", ans[i].first, ans[i].second);
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}