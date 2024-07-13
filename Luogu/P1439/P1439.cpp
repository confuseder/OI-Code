#include <bits/stdc++.h>
using namespace std;

int n, len = 0;
int a[100001], b[100001], mp[100001], f[100001];

int main() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);

        mp[a[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", &b[i]);
        f[i] = 1e9;
    }

    f[0] = 0;

    for (int i = 1; i <= n; i++) {
        int l = 0, r = len, mid;
        if (mp[b[i]] > f[len]) {
            f[++len] = mp[b[i]];
        } else {
            while (l < r) {
                mid = (l + r) / 2;
                if (f[mid] > mp[b[i]]) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }
            f[l] = min(mp[b[i]], f[l]);
        }
    }
    cout << len;

    return 0;
}