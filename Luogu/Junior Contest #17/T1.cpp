#include <bits/stdc++.h>
using namespace std;

long long r, v, m;
long long mf, sc, ro;
long long a, b;

int main() {

    // freopen("T1.in", "r", stdin);
    // freopen("T1.out", "w", stdout);

    cin >> a >> b;
    cin >> r >> v >> m;

    mf = 4 * a * r + b * r;
    sc = 6 * a * v + b * v;
    ro = 6 * a * m + b * m;

    cout << mf << ' ' << sc << ' ' << ro << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}