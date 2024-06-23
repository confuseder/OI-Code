#include <bits/stdc++.h>
using namespace std;

#define INF (0x3f3f3f3f)

const int tx[] = {0, 0, 0, -1, 1};
const int ty[] = {0, -1, 1, 0, 0};

int n, m, sx, sy, k;

struct Time {
    int begin, end, direct;
} ti[205];

bool mti[205][205];
int  f[205][205];

int ans;

struct Node {
    int pos, val;
};

deque<Node> q;

void work(int x, int y, int direct, int len) {
    q.clear();
    int displace = 0;

    while (x >= 1 && x <= m && y >= 1 && y <= n) {
        if (mti[y][x]) {
            q.clear();
        } else {
            while (!q.empty() && q.back().val <= f[y][x] - displace) {
                q.pop_back();
            }
            q.push_back({displace, f[y][x] - displace});

            if (displace - q.front().pos > len) {
                q.pop_front();
            }

            f[y][x] = q.front().val + displace;

            ans = max(ans, f[y][x]);
        }

        x += tx[direct];
        y += ty[direct];

        displace++;
    }
}

int main() {

    // freopen("P2254.in", "r", stdin);
    // freopen("P2254.out", "w", stdout);

    cin >> n >> m >> sx >> sy >> k;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c;
            cin >> c;
            mti[i][j] = c == 'x' ? true : false;
            f[i][j]   = -INF;
        }
    }

    for (int i = 1; i <= k; i++) {
        cin >> ti[i].begin >> ti[i].end >> ti[i].direct;
    }

    f[sx][sy] = 0;

    for (int i = 1; i <= k; i++) {
        int len = ti[i].end - ti[i].begin + 1;

        switch (ti[i].direct) {
            case 1:
                for (int j = 1; j <= m; j++) {
                    work(j, n, 1, len);
                }
                break;
            case 2:
                for (int j = 1; j <= m; j++) {
                    work(j, 1, 2, len);
                }
                break;
            case 3:
                for (int j = 1; j <= n; j++) {
                    work(m, j, 3, len);
                }
                break;
            case 4:
                for (int j = 1; j <= n; j++) {
                    work(1, j, 4, len);
                }
                break;
        }
    }

    cout << ans;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}