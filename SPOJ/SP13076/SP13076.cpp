#include <bits/stdc++.h>
using namespace std;

struct node {
    int x, y;
};

const int tx[5] = {0, 1, -1, 0, 0};
const int ty[5] = {0, 0, 0, 1, -1};

int n, m;
char mp[55][55];
int ti[55][55];
int ans[55][55];
queue<node> q;

int sx, sy, ex, ey;

int main() {

    // freopen("SP13076.in", "r", stdin);
    // freopen("SP13076.out", "w", stdout);

    memset(ti, 0x3f, sizeof(ti));
    memset(ans, 0x3f, sizeof(ans));

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> mp[i][j];
            switch (mp[i][j]) {
            case '*':
                q.push({i, j});
                ti[i][j] = 0;
                break;
            case 'S':
                sx = i, sy = j;
                break;
            case 'D':
                ti[i][j] = -1;
                ex = i, ey = j;
                break;
            case 'X':
                ti[i][j] = -1;
                break;
            }
        }
    }

    while (!q.empty()) {
        const auto check = [](int x, int y) -> bool {
            return ((x >= 1) && (x <= n) && (y >= 1) && (y <= m) &&
                    (mp[x][y] != 'X') && (mp[x][y] != 'D'));
        };
        auto [nx, ny] = q.front();
        q.pop();
        int tt = ti[nx][ny] + 1;

        for (int i = 1; i <= 4; i++) {
            int xx = nx + tx[i];
            int yy = ny + ty[i];
            if (tt < ti[xx][yy] && check(xx, yy)) {
                ti[xx][yy] = tt;
                q.push({xx, yy});
            }
        }
    }

    q.push({sx, sy});
    ans[sx][sy] = 0;

    while (!q.empty()) {
        const auto check = [](int x, int y) -> bool {
            return ((x >= 1) && (x <= n) && (y >= 1) && (y <= m) &&
                    (mp[x][y] != 'X'));
        };

        auto [nx, ny] = q.front();
        q.pop();
        int tt = ans[nx][ny] + 1;

        for (int i = 1; i <= 4; i++) {
            int xx = nx + tx[i];
            int yy = ny + ty[i];
            if ((tt < ti[xx][yy] || ti[xx][yy] == -1) && tt < ans[xx][yy] &&
                check(xx, yy)) {
                ans[xx][yy] = tt;
                q.push({xx, yy});
            }
        }
    }

    cout << (ans[ex][ey] < 1e8 ? to_string(ans[ex][ey]) : "KAKTUS") << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}