#include <bits/stdc++.h>
using namespace std;

struct Point {
    double x, y;
    double k;

    double operator+(Point p) {
        return sqrt(pow(this->x - p.x, 2) + pow(this->y - p.y, 2));
    }

    double operator*(Point p) {
        return this->x * p.y - this->y * p.x;
    }

    Point operator-(Point p) {
        return {x - p.x, y - p.y, 0};
    }
};

int           n;
vector<Point> p;
int           st[100005], top;

int main() {

    // freopen("2742.in", "r", stdin);
    // freopen("2742.out", "w", stdout);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        double x, y;
        cin >> x >> y;
        p.push_back({x, y, 0});

        if (i > 1 && (p[i - 1].y < p[0].y || (p[i - 1].y == p[0].y && p[i - 1].x < p[0].x))) {
            swap(p[i - 1], p[0]);
        }
    }

    for (int i = 1; i < n; i++) {
        p[i].k = atan2(p[i].y - p[0].y, p[i].x - p[0].x);
    }

    sort(p.begin() + 1, p.end(), [](Point a, Point b) -> bool {
        return (a.k == b.k) ? (a + *p.begin()) < (b + *p.begin()) : (a.k < b.k);
    });

    st[++top] = 0;

    for (int i = 1; i < n; i++) {
        while (top >= 2 && (p[st[top]] - p[st[top - 1]]) * (p[i] - p[st[top]]) < 0) {
            top--;
        }
        st[++top] = i;
    }

    st[++top] = 0;

    double ans = 0;
    for (int i = 1; i < top; i++) {
        ans += p[st[i]] + p[st[i + 1]];
    }

    printf("%.2lf\n", ans);

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}