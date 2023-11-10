#include <bits/stdc++.h>
using namespace std;

int a10, a8, a3, a1;

int main() {

    // freopen("T3.in", "r", stdin);
    // freopen("T3.out", "w", stdout);

    for (int i = 1; i <= 8; i++) {
        int a;
        cin >> a;
        a1++;
        if (a >= 41) {
            a3++;
        }
        if (a >= 63) {
            a8++;
        }
        if (a >= 118) {
            a10++;
        }
    }

    if (a10 >= 1) {
        cout << 10 << endl;
    } else if (a8 >= 4) {
        cout << 8 << endl;
    } else if (a3 >= 4) {
        cout << 3 << endl;
    } else {
        cout << 1 << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}