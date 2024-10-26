#include <bits/stdc++.h>
using namespace std;

int n;

int cnt;
int num[100005];
int tmp[100005];

int main() {

    // freopen("P11231.in", "r", stdin);
    // freopen("P11231.out", "w", stdout);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> num[i];
    }

    sort(num + 1, num + n + 1, [](int a, int b) { return a < b; });

    for (int i = 2, c = 1; i <= n + 1; i++) {
        if (num[i] != num[i - 1]) {
            tmp[++cnt] = c;
            c          = 1;
        } else {
            c++;
        }
    }

    sort(tmp + 1, tmp + cnt + 1, [](int a, int b) { return a > b; });

    cout << tmp[1] << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}