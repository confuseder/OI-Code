#include <bits/stdc++.h>
#include <vector>
using namespace std;

struct t {
    int begin, end, num;
};

int       n, h, ans;
bool      vis[30005];
vector<t> tree;

int main() {

    // freopen("P1250.in", "r", stdin);
    // freopen("P1250.out", "w", stdout);

    cin >> n >> h;

    for (int i = 1; i <= h; i++) {
        int b, e, u;
        cin >> b >> e >> u;

        tree.emplace_back(b, e, u);
    }

    sort(tree.begin(), tree.end(), [](t a, t b) {
        return a.end < b.end;
    });

    for (auto [b, e, u] : tree) {
        int cnt = 0;

        for (int j = b; j <= e; j++) {
            cnt += vis[j];
        }

        if (cnt < u) {
            for (int j = e; j >= b && cnt < u; j--) {
                if (!vis[j]) {
                    vis[j] = true;
                    cnt++;
                    ans++;
                }
            }
        }
    }

    cout << ans << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}