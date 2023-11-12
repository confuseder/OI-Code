#include <bits/stdc++.h>
using namespace std;

const uint64_t base = 1145141919810;

int n;
vector<uint64_t> ha;

uint64_t __hash(string str) {
    uint64_t ans = 0;
    for (int i = 0; i < str.length(); i++) {
        ans = ans * base + str[i];
    }
    return ans;
}

int main() {

    // freopen("P3370.in", "r", stdin);
    // freopen("P3370.out", "w", stdout);

    cin >> n;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        ha.push_back(__hash(s));
    }

    sort(ha.begin(), ha.end());
    ha.erase(unique(ha.begin(), ha.end()), ha.end());

    cout << ha.size() << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}