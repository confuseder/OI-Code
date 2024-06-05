#include <bits/stdc++.h>
using namespace std;

int n, m;

map<string, set<int>> cnt;

int main() {

    // freopen("P3879.in", "r", stdin);
    // freopen("P3879.out", "w", stdout);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        int l;
        cin >> l;

        while (l--) {
            string a;
            cin >> a;

            cnt[a].insert(i);
        }
    }

    cin >> m;

    for (int i = 1; i <= m; i++) {
        string a;
        cin >> a;

        for (int j : cnt[a]) {
            cout << j << ' ';
        }

        cout << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}