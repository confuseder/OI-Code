#include <bits/stdc++.h>
using namespace std;

struct node {
    int data;
    int fa;
    int back;
    unordered_map<int, int> nxt;
    node() {
        data = fa = back = 0;
        nxt.clear();
    }
};

int T;
int n;
// vector<int> num;

int cnt, last;
long long ans;
node trie[300005];

int main() {

    // freopen("CF1223F.in", "r", stdin);
    // freopen("CF1223F.out", "w", stdout);

    cin >> T;

    while (T--) {
        cin >> n;

        cnt = last = ans = 0;
        for (int i = 0; i <= n + 2; i++) {
            trie[i] = *(new node());
        }
        trie[0].data = -1;
        trie[0].back = 1;

        for (int i = 1; i <= n; i++) {
            int a;
            cin >> a;

            if (trie[last].data == a) {
                last = trie[last].fa;
            } else {
                if (trie[last].nxt.count(a) == 0) {
                    trie[last].nxt[a] = ++cnt;
                    trie[cnt].fa      = last;
                    trie[cnt].data    = a;
                }
                last = trie[last].nxt[a];
            }

            ans += trie[last].back++;
        }

        cout << ans << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}