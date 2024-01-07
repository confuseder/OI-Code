#include <iostream>
#include <iterator>
#include <queue>
#include <string.h>
#include <vector>
using namespace std;

struct line {
    int to, w, fb;
    line(int a, int b, int c) : to(a), w(b), fb(c) {}
};

int n, f, d, s, t;
vector<line> mp[1000];

bool inq[1000];
struct Pre {
    int from, edge;
    Pre(int a, int b) : from(a), edge(b) {}
    Pre() { from = edge = 0; }
} pre[1000];

void add(int u, int v, int w) {
    mp[v].push_back(line(u, 0, int(mp[u].size())));
    mp[u].push_back(line(v, w, int(mp[v].size() - 1)));
}

bool zg() {
    queue<int> q;
    memset(inq, false, sizeof(inq));
    fill(pre, pre + 950 + 2, Pre(0, 0));

    inq[s] = 1;
    q.push(s);

    while (!q.empty()) {
        int now = q.front();
        q.pop();

        for (int i = 0; i < mp[now].size(); i++) {
            int v = mp[now][i].to;

            if (!inq[v] && mp[now][i].w != 0) {
                pre[v].from = now;
                pre[v].edge = i;
                if (v == t) {
                    return true;
                }
                inq[v] = true;
                q.push(v);
            }
        }
    }

    return false;
}

int ek() {
    int ans = 0;
    while (zg()) {
        int mi = 1e9;
        for (int i = t; i != s; i = pre[i].from) {
            mi = min(mi, mp[pre[i].from][pre[i].edge].w);
        }
        for (int i = t; i != s; i = pre[i].from) {
            mp[pre[i].from][pre[i].edge].w -= mi;
            mp[i][mp[pre[i].from][pre[i].edge].fb].w += mi;
        }
        ans += mi;
    }
    return ans;
}

int main() {

    // freopen("Poj 3281.in", "r", stdin);
    // freopen("Poj 3281.out", "w", stdout);

    cin >> n >> f >> d;

    s = 900, t = 901;

    for (int i = 1; i <= n; i++) {
        add(i, n + i, 1);
    }

    for (int i = 1; i <= f; i++) {
        add(s, 2 * n + i, 1);
    }

    for (int i = 1; i <= d; i++) {
        add(2 * n + f + i, t, 1);
    }

    for (int i = 1; i <= n; i++) {
        vector<int> fods;
        int fod, drk;
        cin >> fod >> drk;

        for (int j = 1; j <= fod; j++) {
            int x;
            cin >> x;
            add(2 * n + x, i, 1);
        }

        for (int j = 1; j <= drk; j++) {
            int x;
            cin >> x;
            add(n + i, 2 * n + f + x, 1);
        }
    }

    cout << ek() << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}