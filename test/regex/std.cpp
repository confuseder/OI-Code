#include <bits/stdc++.h>
using namespace std;

string ptt;
int n;
map<int, string> reg;

struct Trie {
    int cnt = 0, ans = 0;
    int data[60005][200];
    bool end[60005];

    void insert(string str) {
        int now = 0;

        for (auto i : str) {
            if (data[now][int(i)] == 0) {
                data[now][int(i)] = ++cnt;
            }
            now = data[now][int(i)];
        }

        end[now] = true;
    }

    void solve(int u, int l) {

        if (l == ptt.length()) {
            if (end[u]) {
                ans++;
                end[u] = false;
            }
            return;
        }

        if (isupper(ptt[l])) {
            if (data[u][int(ptt[l])] != 0) {
                solve(data[u][int(ptt[l])], l + 1);
            }
        } else if (isdigit(ptt[l])) {
            for (auto i : reg[ptt[l] - '0']) {
                if (data[u][int(i)] != 0) {
                    solve(data[u][int(i)], l + 1);
                }
            }
        } else {
            for (int i = int('A'); i <= int('Z'); i++) {
                if (data[u][i] != 0) {
                    solve(data[u][i], l + 1);
                    if (ptt[l] == '+') {
                        solve(data[u][i], l);
                    }
                }
            }
        }
    }

} trie;

int main() {

    // freopen("std.in", "r", stdin);
    // freopen("std.out", "w", stdout);

    {
        bool in = false;
        string buffer, x;
        cin >> x;

        for (auto i : x) {
            if (i == '[') {
                in = true;
            } else if (i == ']') {
                ptt.push_back(reg.size() + '0');
                buffer.erase(unique(buffer.begin(), buffer.end()), buffer.end());
                reg[reg.size()] = buffer;
                buffer.clear();
                in = false;
            } else if (in) {
                buffer.push_back(i);
            } else {
                ptt.push_back(i);
            }
        }
    }

    cin >> n;

    for (int i = 0; i < n; ++i) {
        string x;
        cin >> x;
        trie.insert(x);
    }

    trie.solve(0, 0);

    cout << trie.ans << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}