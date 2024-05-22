#include <bits/stdc++.h>
using namespace std;

long long n, m;
long long num[50005];

struct sub_query {
    long long r1, r2, id;

    sub_query() {}

    sub_query(long long _r1, long long _r2, long long _id)
        : r1(min(_r1, _r2)), r2(max(_r1, _r2)), id(_id) {}
};

vector<sub_query> sub_q;

struct query {

    long long l1, r1, l2, r2;
    long long q1, q2, q3, q4;

    query() {}

    query(long long _l1, long long _r1, long long _l2, long long _r2)
        : l1(_l1), r1(_r1), l2(_l2), r2(_r2) {
        q1 = sub_q.size(), sub_q.emplace_back(r1, r2, q1);
        q2 = sub_q.size(), sub_q.emplace_back(r1, l2 - 1, q2);
        q3 = sub_q.size(), sub_q.emplace_back(l1 - 1, r2, q3);
        q4 = sub_q.size(), sub_q.emplace_back(l1 - 1, l2 - 1, q4);
    }
};

vector<query> q;

long long now, siz;
long long cnt_l[50005], cnt_r[50005];
long long ans[200005];

void add_l(long long x) {
    ++cnt_l[num[x]];
    now += cnt_r[num[x]];
}

void del_l(long long x) {
    --cnt_l[num[x]];
    now -= cnt_r[num[x]];
}

void add_r(long long x) {
    ++cnt_r[num[x]];
    now += cnt_l[num[x]];
}

void del_r(long long x) {
    --cnt_r[num[x]];
    now -= cnt_l[num[x]];
}

int main() {

    // freopen("P5268.in", "r", stdin);
    // freopen("P5268.out", "w", stdout);

    scanf("%lld", &n);

    siz = sqrt(n);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &num[i]);
    }

    scanf("%lld", &m);

    for (int i = 1; i <= m; i++) {
        long long x, y, z, k;
        scanf("%lld %lld %lld %lld", &x, &y, &z, &k);

        q.push_back(query(x, y, z, k));
    }

    sort(sub_q.begin(), sub_q.end(), [](sub_query a, sub_query b) {
        return ((a.r1 - 1) / siz == (b.r1 - 1) / siz) ? a.r2 < b.r2 : a.r1 < b.r1;
    });

    long long l = 0, r = 0;

    for (auto i : sub_q) {
        while (l < i.r1) { add_l(++l); }
        while (l > i.r1) { del_l(l--); }
        while (r < i.r2) { add_r(++r); }
        while (r > i.r2) { del_r(r--); }

        ans[i.id] = now;
    }

    for (auto i : q) {
        printf("%lld\n", ans[i.q1] - ans[i.q2] - ans[i.q3] + ans[i.q4]);
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}