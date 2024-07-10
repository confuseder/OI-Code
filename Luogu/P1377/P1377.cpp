#include <bits/stdc++.h>
using namespace std;

struct node {
    int val, id;
} nodes[100005];

struct tr {
    int val, l, r;
};

int n;

int st[100005], top;
tr  tree[100005];

void print(int i) {
    if (i == 0) {
        return;
    }
    cout << tree[i].val << ' ';
    print(tree[i].l);
    print(tree[i].r);
}

int main() {

    // freopen("P1377.in", "r", stdin);
    // freopen("P1377.out", "w", stdout);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        int val;
        cin >> val;

        nodes[i] = {val, i};
    }

    sort(nodes + 1, nodes + n + 1, [](node a, node b) {
        return a.val < b.val;
    });

    for (int i = 1; i <= n; i++) {
        while (top && nodes[st[top]].id > nodes[i].id) {
            top--;
        }

        tree[i].val     = nodes[i].val;
        tree[i].l       = tree[st[top]].r;
        tree[st[top]].r = i;
        st[++top]       = i;
    }

    print(tree[0].r);

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}