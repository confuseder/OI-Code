#include <bits/stdc++.h>
using namespace std;

string           ptt;
int              n;
map<int, string> reg;

struct Trie {
    int  cnt = 0, ans = 0;
    int  data[60005][200];
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
    }  // 简单的字典树插入操作

    /*
     *  u：字典树节点号 l：现在匹配到的模式串的下标
     */
    void solve(int u, int l) {

        if (l == ptt.length()) {
            if (end[u]) {
                ans++;
                end[u] = false;
            }
            return;
        }

        if (isupper(ptt[l])) {  // 模式串中是大写字母则是普通的匹配
            if (data[u][int(ptt[l])] != 0) {
                solve(data[u][int(ptt[l])], l + 1);
            }
        } else if (isdigit(ptt[l])) {  // 是数字则是一个选择匹配符
            string buffer;
            buffer.push_back(ptt[l]);

            while (ptt[l + 1] != '|') {  // 循环到分隔符代表一个选择匹配符的结束
                ++l;
                buffer.push_back(ptt[l]);
            }
            ++l;  // 无论是否有多位数字，分隔符都占一个字符位，记得下标加一

            for (auto i : reg[stoi(buffer)]) {
                if (data[u][int(i)] != 0) {
                    solve(data[u][int(i)], l + 1);
                }
            }
        } else {  // 如果是 + / ?，则搜索所有子树。
            for (int i = int('A'); i <= int('Z'); i++) {
                if (data[u][i] != 0) {
                    solve(data[u][i], l + 1);
                    if (ptt[l] == '+') {
                        solve(data[u][i], l);
                    }
                }
            }
            /*
             * 如果是 +，那么他可以匹配多个字符，所以这里有两种情况。
             * 1. 现在是被 + 匹配的最后一个字符。那么 l + 1。
             * 2. 下一个字符还是被 + 匹配，那么下一次还是 l。
             */
        }
    }

} trie;

int main() {

    // freopen("std.in", "r", stdin);
    // freopen("std.out", "w", stdout);

    {
        bool   in = false;
        string buffer, x;
        cin >> x;

        for (auto i : x) {
            if (i == '[') {
                in = true;
            } else if (i == ']') {
                ptt += to_string(reg.size());
                ptt += "|";
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

    /*
     * 将 [] 替换为在 map 中的 key。
     */

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