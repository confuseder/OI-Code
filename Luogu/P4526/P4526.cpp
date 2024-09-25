#include <bits/stdc++.h>
using namespace std;

double a;

double f(double x) {
    return pow(x, (a / x) - x);
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

    // freopen("P4526.in", "r", stdin);
    // freopen("P4526.out", "w", stdout);

    cin >> a;

    if (a < 0) {
        cout << "orz" << endl;
    } else {
        printf("%.5lf\n", run((1e-8), 15, run((1e-8), 15)));
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}