#include <bits/stdc++.h>
using namespace std;

long long qpow(long long a, long long b) {
    long long res = 1;
    while (b) {
        if (1 & b) {
            res *= a;
        }
        a *= a;
        b >>= 1;
    }

    return res;
}

int t;
long long n;
long long v[55];
long long f[55];

int main() {

    // freopen("P111188.in", "r", stdin);
    // freopen("P111188.out", "w", stdout);

    cin >> t;

    cin >> t;

    while (t--) {
        string s;
        cin >> s;
        n = s.size();

        long long ans = 0;

        for (int i = 1; i <= 9; i++) { cin >> v[i]; }
        for (int i = 0; i < n; i++) { ans += v[s[i] - '0']; }

        long long sum = ans;

        for (int i = 6; i >= 1; i--) {
            memset(f, 0x3f, sizeof f);
            f[i] = sum;

            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= i; k++) {
                    f[k] = min(f[k], f[k + 1] + qpow(10, k - 1) * (s[j - 1] - '0') - v[s[j - 1] - '0']);
                }
            }

            ans = min(ans, f[1]);
        }
        
        cout << ans << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}