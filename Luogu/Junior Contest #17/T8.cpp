#include <bits/stdc++.h>
using namespace std;

int n, q;
vector<int> j;
int num[200009];

int main() {

    // freopen("T8.in", "r", stdin);
    // freopen("T8.out", "w", stdout);

    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        int fc[4];
        string str, buffer;
        cin >> str;
        bool flag = false;
        for (auto i : str) {
            if (i == '+' || i == '=') {
                fc[++cnt] = stoi(buffer);
                buffer.clear();
            } else if (i == '-') {
                if (buffer.size()) {
                    fc[++cnt] = stoi(buffer);
                    buffer.clear();
                }
                buffer.push_back('-');
            } else {
                buffer.push_back(i);
            }
            flag = true;
        }
        fc[3] = stoi(buffer);

        j.push_back((fc[3] - fc[2]) / fc[1]);
    }

    sort(j.begin(), j.end());
    j.erase(unique(j.begin(), j.end()), j.end());

    for (int i = 1; i <= q; i++) {
        int a, b;
        cin >> a >> b;
        cout << upper_bound(j.begin(), j.end(), b) -
                    lower_bound(j.begin(), j.end(), a)
             << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}