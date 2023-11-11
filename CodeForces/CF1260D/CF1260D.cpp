#include <bits/stdc++.h>
using namespace std;

int m, n, k, t;
int a[200005];
int l[200005], r[200005], d[200005];
int v[200005];

bool check(int p) {

    memset(v, 0, sizeof(v));

    int mx_df = a[p];
    for (int i = 1; i <= k; i++) {
        if (d[i] > mx_df) {
            v[l[i]]++;
            v[r[i] + 1]--;
        }
    }
    int ti = 0;
    for (int i = 1; i <= n + 1; i++) {
        v[i] += v[i - 1];
        ti += (v[i] == 0 ? 1 : 3);
    }

    return ti <= t ? true : false;
}

int main() {

    // freopen("CF1260D.in", "r", stdin);
    // freopen("CF1260D.out", "w", stdout);

    cin >> m >> n >> k >> t;

    for (int i = 1; i <= m; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= k; i++) {
        cin >> l[i] >> r[i] >> d[i];
    }

    sort(a + 1, a + m + 1, [&](int a, int b) { return a > b; });

    int l = 0, r = m + 1;

    while (l < r) {
        int mid = (l + r) / 2;
        if (check(mid)) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    cout << (r != 0 ? r - 1 : r) << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}