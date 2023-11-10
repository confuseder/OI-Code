#include <bits/stdc++.h>
using namespace std;

bool isnp[100000]; // is not prime: 不是素数
void init(int n) {
    for (int i = 2; i * i <= n; i++)
        if (!isnp[i])
            for (int j = i * i; j <= n; j += i)
                isnp[j] = 1;
}

int n;

int main() {

    // freopen("T4.in", "r", stdin);
    // freopen("T4.out", "w", stdout);

    init(10000);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        int cnt  = 1;
        int line = 0;
        int last = 'A' + i - 2;
        while (cnt <= i * i) {
            ++line;
            if (isnp[last + 1 + line]) {
                cout << ' ';
            } else {
                cout << (char)(last + 1);
                last++;
                if (last - 'A' == 25) {
                    last = 'A' - 1;
                }
                cnt++;
            }
        }
        cout << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}