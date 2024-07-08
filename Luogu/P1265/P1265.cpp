#include <bits/stdc++.h>
using namespace std;

int n;

pair<int, int> point[5005];
bool           vis[5005];
double         ans, dist[5005];

double len(pair<int, int> a, pair<int, int> b) {
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

int main() {

    // freopen("P1265.in", "r", stdin);
    // freopen("P1265.out", "w", stdout);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;

        point[i] = {x, y};
        dist[i]  = 1e9;
    }

    dist[1] = 0;

    for (int k = 1; k <= n; k++) {

        double w = (double)1e9;

        int pos;

        for (int j = 1; j <= n; j++) {
            if (!vis[j] && w > dist[j]) {
                pos = j, w = dist[j];
            }
        }

        vis[pos] = true;

        ans += dist[pos];

        for (int j = 1; j <= n; j++) {
            if (!vis[j]) {
                dist[j] = min(dist[j], len(point[pos], point[j]));
            }
        }
    }

    printf("%.2lf\n", ans);

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}