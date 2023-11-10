#include <bits/stdc++.h>
using namespace std;

int T;
int n;
char op;
int f[20005];
int dist[20005];

int find(int x) {
    if (f[x] == x) {
        return x;
    } else {
        int ___old = f[x];
        f[x]       = find(f[x]);
        dist[x] += dist[___old];
        return f[x];
    }
}

int main() {

    // freopen("SP264.in", "r", stdin);
    // freopen("SP264.out", "w", stdout);

    cin >> T;

    while (T--) {
        cin >> n;

        for (int i = 1; i <= n; i++) {
            f[i] = i;
        }
        memset(dist, 0, sizeof(dist));

        while (cin >> op && op != 'O') {
            if (op == 'I') {
                int x, y;
                cin >> x >> y;
                f[x] = y;
                dist[x] += abs(x - y) % 1000;
            } else if (op == 'E') {
                int x;
                cin >> x;
                find(x);
                cout << dist[x] << endl;
            }
        }
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}