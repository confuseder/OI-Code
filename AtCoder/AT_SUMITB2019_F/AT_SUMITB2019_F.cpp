#include <bits/stdc++.h>
using namespace std;

long long t1, t2, a1, a2, b1, b2;

int main() {

    // freopen("AT_SUMITB2019_F.in", "r", stdin);
    // freopen("AT_SUMITB2019_F.out", "w", stdout);

    cin >> t1 >> t2;
    cin >> a1 >> a2;
    cin >> b1 >> b2;

    long long s1 = (a1 - b1) * t1;
    long long s2 = (a2 - b2) * t2;

    if (s1 + s2 == 0) {
        printf("infinity\n");
    } else if ((s1 < 0 && s2 < 0) || (s1 > 0 && s2 > 0) || abs(s1) > (s1 < 0 ? s2 : -s2)) {
        printf("0\n");
    } else {
        printf("%lld\n", abs(s1) % abs(s1 + s2) == 0 ? abs(s1) / abs(s1 + s2) * 2 : abs(s1) / abs(s1 + s2) * 2 + 1);
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}