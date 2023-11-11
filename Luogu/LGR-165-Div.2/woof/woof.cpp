#include <bits/stdc++.h>
using namespace std;

int n, t;

int main() {

    // freopen("woof.in", "r", stdin);
    // freopen("woof.out", "w", stdout);

    cin >> n >> t;

    for (int i = 1; i <= n; i++) {
        int start = ((i % 2) ? (2 * n - i + 1) >> 1 : i / 2);
        for (int j = 1, len = 1; j <= i; j++, len++) {
            cout << start << ' ';
            if (j % 2) {
                start += len;
            } else {
                start -= len;
            }
        }
        cout << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}