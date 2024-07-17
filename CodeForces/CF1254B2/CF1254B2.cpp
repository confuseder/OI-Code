#include <bits/stdc++.h>
using namespace std;

int       n;
long long sum, ans = 1e18;
long long num[1000005];
long long tmp[1000005];

vector<long long> p;

inline long long calc(long long x) {
    memset(tmp, 0, sizeof(tmp));
    long long res = 0;

    for (int i = 1; i <= n; ++i) {
        tmp[i] = tmp[i - 1] + num[i] % x;
        tmp[i] %= x;
        res += min(tmp[i], x - tmp[i]);
    }

    return res;
};

int main() {

    // freopen("CF1254B2.in", "r", stdin);
    // freopen("CF1254B2.out", "w", stdout);

    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", &num[i]);
        sum += num[i];
    }

    if (sum == 1) {
        printf("-1\n");
        return 0;
    }

    for (long long i = 2; i * i <= sum; i++) {
        if (sum % i == 0) {
            p.emplace_back(i);
            while (sum % i == 0) {
                sum /= i;
            }
        }
    }
    if (sum > 1) {
        p.emplace_back(sum);
    }

    for (long long x : p) {
        ans = min(ans, calc(x));
    }

    printf("%lld\n", (ans == 1e18 ? -1 : ans));

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}