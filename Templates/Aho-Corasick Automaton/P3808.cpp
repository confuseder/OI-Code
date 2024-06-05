#include <bits/stdc++.h>
using namespace std;

struct node {
    node *fail      = nullptr;
    node *child[30] = {nullptr};
    int   end       = 0;
} *root;

void insert(string s) {
    if (root == nullptr) {
        root = new node();
    }

    node *now = root;

    for (char i : s) {
        if (now->child[i - 'a'] == nullptr) {
            now->child[i - 'a'] = new node();
        }
        now = now->child[i - 'a'];
    }

    now->end++;
}

void fail() {
    queue<node *> q;

    for (int i = 0; i < 26; i++) {
        if (root->child[i] != nullptr) {
            root->child[i]->fail = root;

            q.push(root->child[i]);
        }
    }

    while (!q.empty()) {
        node *now = q.front();
        q.pop();

        for (int i = 0; i < 26; i++) {
            if (now->child[i] != nullptr) {
                now->child[i]->fail = now->fail->child[i];
                q.push(now->child[i]);
            } else {
                now->child[i] = now->fail->child[i];
            }
        }
    }
}

int query(string s) {
    node *now = root;
    int   ans = 0;

    for (char i : s) {
        now = now->child[i - 'a'];

        for (node *j = now; j != root && j != nullptr && j->end != -1; j = j->fail) {
            ans += j->end;
            j->end = -1;
        }
    }

    return ans;
}

int n;

int main() {

    // freopen("P3808.in", "r", stdin);
    // freopen("P3808.out", "w", stdout);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        string s;
        cin >> s;

        insert(s);
    }

    root->fail = root;

    fail();

    string s;
    cin >> s;

    cout << query(s) << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}