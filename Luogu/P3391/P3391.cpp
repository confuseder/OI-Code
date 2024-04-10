#include <bits/stdc++.h>
#include <ext/rope>

using namespace std;

int                  n, m;
__gnu_cxx::rope<int> rp, srp;

inline void rev(int st, int ed) {
    if (st >= ed + 1) return;
    ed++;
    __gnu_cxx::rope<int> tmp = rp.substr(st + rp.begin(), ed + rp.begin());
    rp                       = rp.substr(0 + rp.begin(), st + rp.begin()) + srp.substr(n - ed + srp.begin(), n - st + srp.begin()) + rp.substr(ed + rp.begin(), rp.length() + rp.begin());
    srp                      = srp.substr(srp.begin(), n - ed + srp.begin()) + tmp + srp.substr(n - st + srp.begin(), srp.length() + srp.begin());
}

int main() {

    // freopen("P3391.in", "r", stdin);
    // freopen("P3391.out", "w", stdout);

    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++) {
        rp.append(i);
        srp.append(n - i + 1);
    }

    for (int i = 1; i <= m; i++) {
        int l, r;
        scanf("%d %d", &l, &r);

        rev(l - 1, r - 1);
    }

    for (int i = 0; i < rp.length(); ++i) {
        printf("%d ", rp[i]);
    }

    printf("\n");

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}