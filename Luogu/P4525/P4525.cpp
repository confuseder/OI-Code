#include <bits/stdc++.h>
using namespace std;

double a, b, c, d, l, r;

double f(double x) {
    return (c * x + d) / (a * x + b);
}

double simp(double x, double y) {
    double mid = (x + y) / 2;
    return (y - x) * (f(x) + 4 * f(mid) + f(y)) / 6;
}

double run(double x, double y, double ans) {
    double mid  = (x + y) / 2;
    double tmp1 = simp(x, mid), tmp2 = simp(mid, y);
    if (fabs(tmp1 + tmp2 - ans) <= (1e-8)) {
        return tmp1 + tmp2;
    }
    return run(x, mid, tmp1) + run(mid, y, tmp2);
}

double run(double x, double y) {
    return run(x, y, simp(x, y));
}

int main() {

    // freopen("P4525.in", "r", stdin);
    // freopen("P4525.out", "w", stdout);

    cin >> a >> b >> c >> d >> l >> r;

    printf("%.6lf\n", run(l, r));

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}