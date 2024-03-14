#include <bits/stdc++.h>
using namespace std;

int n;

int cnt, vc, version[100005];

struct node {
    int  l, r, sum;
    char c;
} tree[40000005];

int clone(int node) {
    tree[++cnt] = tree[node];
    return cnt;
}

void push_up(int x) {
    tree[x].sum = tree[tree[x].l].sum + tree[tree[x].r].sum;
}

int update(int node, char c, int l, int r) {
    node = clone(node);

    if (l > r) {
        return 0;
    }
    if (l == r) {
        tree[node].sum = 1;
        tree[node].c   = c;
        return node;
    }

    int mid = (l + r) / 2;

    if (tree[tree[node].l].sum == (mid - l + 1)) {
        tree[node].r = update(tree[node].r, c, mid + 1, r);
    } else {
        tree[node].l = update(tree[node].l, c, l, mid);
    }

    push_up(node);
    return node;
}

char query(int node, int x, int l, int r) {
    if (l >= r) {
        return tree[node].c;
    } else {
        int mid = (l + r) >> 1;
        if (x <= tree[tree[node].l].sum) {
            return query(tree[node].l, x, l, mid);
        } else {
            return query(tree[node].r, x - tree[tree[node].l].sum, mid + 1, r);
        }
    }
}

int main() {

    // freopen("P1383.in", "r", stdin);
    // freopen("P1383.out", "w", stdout);

    version[0] = ++cnt;

    cin >> n;

    for (int i = 1; i <= n; i++) {
        char op;
        cin >> op;

        switch (op) {
            case 'T':
                char c;
                cin >> c;
                ++vc;
                version[vc] = update(version[vc - 1], c, 1, n);
                break;
            case 'U':
                int x;
                cin >> x;
                ++vc;
                version[vc] = version[vc - x - 1];
                break;
            case 'Q':
                int y;
                cin >> y;
                cout << query(version[vc], y, 1, n) << endl;
        }
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}