#include <bits/stdc++.h>
using namespace std;

struct node {
    int l, r, flag, ans;

    bool operator<(const node &a) const {
        return l < a.l;
    }

    bool operator>(const node &a) const {
        return l > a.l;
    }
};

int       n;
int       a[200005];
set<node> s;

int main() {

    // freopen("P7988.in", "r", stdin);
    // freopen("P7988.out", "w", stdout);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    s.insert({0, n + 1, int(1e9), 0});

    for (int i = 1; i <= n; i++) {
        auto it = s.upper_bound({a[i], a[i], 0, 0});
        it--;
        node now = *it;
        s.erase(it);

        if (now.flag == 1) {
            s.insert({a[i], now.r, 0, now.ans + 1});
        } else {
            s.insert({a[i], now.r, 0, now.ans});
        }
        s.insert({now.l, a[i], 1, now.ans});
    }

    for (auto it : s) { cout << it.ans << endl; }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}