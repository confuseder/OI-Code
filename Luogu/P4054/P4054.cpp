#include <bits/stdc++.h>
using namespace std;

#define lowbit(x) (x & -x)

int q, n, m;

int color[305][305];
int tree[305][305][105];

void add(int x, int y, int k, int c) {
    for (int i = x; i <= n; i += lowbit(i)) {
        for (int j = y; j <= m; j += lowbit(j)) {
            tree[i][j][c] += k;
        }
    }
}

int query(int x, int y, int c) {
    int tot = 0;

    for (int i = x; i > 0; i -= lowbit(i)) {
        for (int j = y; j > 0; j -= lowbit(j)) {
            tot += tree[i][j][c];
        }
    }

    return tot;
}

int main() {

    // freopen("P4054.in", "r", stdin);
    // freopen("P4054.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int c;
            cin >> c;
            add(i, j, 1, c);
            color[i][j] = c;
        }
    }

    cin >> q;

    while (q--) {
        int op;
        cin >> op;

        switch (op) {
            case 1: {
                int x, y, c;
                cin >> x >> y >> c;

                add(x, y, -1, color[x][y]);
                color[x][y] = c;
                add(x, y, 1, c);
            } break;
            case 2: {
                int x1, y1, x2, y2, c;
                cin >> x1 >> x2 >> y1 >> y2 >> c;

                cout << (query(x2, y2, c) - query(x1 - 1, y2, c) - query(x2, y1 - 1, c) + query(x1 - 1, y1 - 1, c)) << endl;
            } break;
        }
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}