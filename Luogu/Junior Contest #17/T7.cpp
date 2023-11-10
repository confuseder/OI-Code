#include <bits/stdc++.h>
using namespace std;

int T;
int n;
string str;

int main() {

    // freopen("T7.in", "r", stdin);
    // freopen("T7.out", "w", stdout);

    cin >> T;

    while (T--) {
        int ans=0;
        cin >> n;
        cin >> str;
        string fz = str;
        reverse(fz.begin(), fz.end());
        // cout << fz << endl;

        for (auto i : str) {
            if (i != 'A' && i != 'T' && i != 'C' && i != 'G') {
                cout << 0 << endl;
                goto nxt;
            }
        }

        for (int i = 0; i < fz.size(); i++) {
            if ((str[i] == 'A' && fz[i] == 'T') ||
                (str[i] == 'T' && fz[i] == 'A')) {
                ans += i + 1;
            } else if ((str[i] == 'C' && fz[i] == 'G') ||
                       (str[i] == 'G' && fz[i] == 'C')) {
                ans += i + 1;
            }
        }

        cout << ans << endl;

    nxt:
        continue;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}