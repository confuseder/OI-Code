#include <bits/stdc++.h>
using namespace std;

int  n, m;
bool mp[55][55];
int  dist[55][55];

int direct(char a) {
    switch (a) {
        case 'N':
            return 1;
            break;
        case 'E':
            return 2;
            break;
        case 'S':
            return 3;
            break;
        case 'W':
            return 4;
            break;
    }
    return 0;
}

bool check(int x, int y) {
    if (x <= 0 || x >= n || y <= 0 || y >= m) {
        return false;
    }

    if (mp[x][y] || mp[x - 1][y] || mp[x][y - 1] || mp[x - 1][y - 1]) {
        return false;
    }

    return true;
}

struct p {
    int x, y;
    int step;
    int to;
};

queue<p> q;

int  sx, sy, ex, ey;
char st;

int to_x[] = {0, -1, 0, 1, 0};
int to_y[] = {0, 0, 1, 0, -1};

int main() {

    // freopen("P1126.in", "r", stdin);
    // freopen("P1126.out", "w", stdout);

    cin >> n >> m;

    memset(dist, 0x3f, sizeof(dist));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mp[i][j];
        }
    }

    cin >> sx >> sy >> ex >> ey >> st;

    q.push({sx, sy, 0, direct(st)});

    while (!q.empty()) {
        auto [x, y, step, to] = q.front();
        q.pop();

        if (dist[x][y] < step) {
            continue;
        }
        dist[x][y] = step;

        for (int i = -3; i <= 3; i++) {
            int t_d = 1 + (to + i + 3) % 4;

            for (int j = 1; j <= 3; j++) {
                int tx = x + (to_x[t_d] * j);
                int ty = y + (to_y[t_d] * j);

                if (check(tx, ty)) {
                    if (step + abs(i) + 1 <= dist[tx][ty])
                        q.push({tx, ty, step + abs(i) + 1, t_d});
                } else {
                    break;
                }
            }
        }
    }

    cout << (dist[ex][ey] == 0x3f3f3f3f ? -1 : dist[ex][ey]) << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}