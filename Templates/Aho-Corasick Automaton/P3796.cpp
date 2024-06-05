#include <bits/stdc++.h>
using namespace std;

int         n, cnt;
vector<int> ans;

struct node {
    node *fail;
    node *child[26];
    int   end;

    node()
        : fail(nullptr), end(0) {
        for (int i = 0; i < 26; i++) {
            child[i] = nullptr;
        }
    }
} *root;

void insert(const string &s) {
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

    now->end = ++cnt;
}

void build_fail() {
    queue<node *> q;

    for (int i = 0; i < 26; i++) {
        if (root->child[i] != nullptr) {
            root->child[i]->fail = root;
            q.push(root->child[i]);
        } else {
            root->child[i] = root;
        }
    }

    while (!q.empty()) {
        node *now = q.front();
        q.pop();

        for (int i = 0; i < 26; i++) {
            if (now->child[i] != nullptr) {
                now->child[i]->fail = (now->fail->child[i] != nullptr) ? now->fail->child[i] : root;
                q.push(now->child[i]);
            } else {
                now->child[i] = (now->fail->child[i] != nullptr) ? now->fail->child[i] : root;
            }
        }
    }
}

void query(const string &s) {
    node *now = root;

    for (char i : s) {
        now = now->child[i - 'a'];
        if (now == nullptr) {
            now = root;
        }

        for (node *j = now; j != root && j != nullptr && j->end != -1; j = j->fail) {
            if (j->end) {
                ans[j->end]++;
            }
        }
    }
}

int main() {

    // freopen("P3796.in", "r", stdin);
    // freopen("P3796.out", "w", stdout);

    while (true) {
        cin >> n;
        if (n == 0) { break; }

        delete root;
        root = new node();
        cnt  = 0;
        ans.assign(n + 1, 0);

        vector<string> patterns(n + 1);

        for (int i = 1; i <= n; i++) {
            cin >> patterns[i];
            insert(patterns[i]);
        }

        root->fail = root;
        build_fail();

        string text;
        cin >> text;

        query(text);

        int max_count = *max_element(ans.begin(), ans.end());
        cout << max_count << endl;

        for (int i = 1; i <= n; i++) {
            if (ans[i] == max_count) {
                cout << patterns[i] << endl;
            }
        }
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}