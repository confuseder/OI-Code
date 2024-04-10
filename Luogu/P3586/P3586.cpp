#include <bits/stdc++.h>
using namespace std;

#define lowbit(x) ((~(x) + 1) & x)

int       n, m;
long long tr1[1000005], tr2[1000005];

void add(long long *tr, int p, int num) {
    while (p <= m + 1) {
        tr[p] += num;
        p += lowbit(p);
    }
}

long long query(long long *tr, int p) {
    long long sum = 0;
    while (p) {
        sum += tr[p];
        p ^= lowbit(p);
    }
    return sum;
}

char op[1000005];
int  t1[1000005], t2[1000005], lsh[1000005];
int  arr[1000005];

int bsearch(int num) {
    int l = 1, r = m + 1, mid;
    while (l < r) {
        mid = (l + r) >> 1;
        if (lsh[mid] < num)
            l = mid + 1;
        else if (lsh[mid] > num)
            r = mid - 1;
        else
            return mid;
    }
    return l;
}

int main() {

    // freopen("P3586.in", "r", stdin);
    // freopen("P3586.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        cin >> op[i] >> t1[i] >> t2[i];
        lsh[i] = t2[i];
    }

    lsh[m + 1] = 0;
    sort(lsh + 1, lsh + m + 2);

    for (int i = 1; i <= m + 1; ++i) {
        arr[i] = 1;
    }

    int tbs = bsearch(0);
    add(tr2, tbs, n);
    add(tr2, tbs + 1, -n);

    for (int i = 1; i <= m; ++i) {
        if (op[i] == 'U') {
            tbs = bsearch(t2[i]);
            add(tr1, arr[t1[i]], -lsh[arr[t1[i]]]);
            add(tr1, tbs, lsh[tbs]);
            add(tr2, arr[t1[i]] + 1, 1);
            add(tr2, tbs + 1, -1);
            arr[t1[i]] = tbs;
        } else {
            tbs           = bsearch(t2[i]);
            long long tmp = (t1[i] - query(tr2, tbs)) * t2[i];
            cout << (query(tr1, tbs - 1) >= tmp ? "TAK" : "NIE") << endl;
        }
    }

    return 0;

    // fclose(stdin);
    // fclose(stdout);
    // system("pause");
}
