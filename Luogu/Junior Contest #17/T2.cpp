#include <bits/stdc++.h>
using namespace std;

long long f;
long long a, b, c, d, M;

int main() {

    // freopen("T2.in", "r", stdin);
    // freopen("T2.out", "w", stdout);

    cin >> a >> b >> c >> d >> M;

    f = 5 * c;

    if (f <= M) {
        f -= (b - d) * 20;
    } else {
        f += (d - (b - d)) * 20;
    }

    cout << max((long long)(0), f) << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}