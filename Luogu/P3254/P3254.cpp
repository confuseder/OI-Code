#include <bits/stdc++.h>
using namespace std;

struct line {
    int to;
    long long w;
    int fb;
};

int n, m, s, t, sum;
vector<line> mp[500];

bool inq[500];
struct Pre {
    int from, edge;
};

Pre pre[500];

void add(int u, int v, int w) {
    mp[v].push_back({u, 0, int(mp[u].size())});
    mp[u].push_back({v, w, int(mp[v].size() - 1)});
}

bool zg() {

    queue<int> q;
    memset(inq, false, sizeof(inq));
    fill(pre, pre + n + 2, Pre{0, 0});

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

long long ek() {
    long long ans = 0;
    while (zg()) {
        long long mi = 1e9;
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

    // freopen("P3254.in", "r", stdin);
    // freopen("P3254.out", "w", stdout);

    cin >> n >> m;

    s = 1, t = n + m + 10;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        sum += x;

        add(s, i + 1, x);

        for (int j = n + 2; j <= n + m + 1; j++) {
            add(i + 1, j, 1);
        }
    }

    for (int i = n + 2; i <= n + m + 1; i++) {
        int x;
        cin >> x;
        add(i, t, x);
    }

    if (ek() == sum) {
        cout << 1 << endl;

        for (int i = 2; i <= n + 1; i++) {
            for (auto j : mp[i]) {
                if (j.to >= n + 2 && j.to <= n + m + 1 && j.w == 0) {
                    cout << j.to - n - 1 << ' ';
                }
            }
            cout << endl;
        }

    } else {
        cout << 0 << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}