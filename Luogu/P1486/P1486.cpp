#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

struct node {
    int val, id;

    node() {}

    node(int _val, int _id)
        : val(_val), id(_id) {}

    bool operator>(const node x) const {
        return (val == x.val) ? (id > x.id) : (val > x.val);
    }
};

tree<node, null_type, greater<node>, rb_tree_tag, tree_order_statistics_node_update> T, TE;

int n, mi;
int chg, ans;

int main() {

    // freopen("P1486.in", "r", stdin);
    // freopen("P1486.out", "w", stdout);

    cin >> n >> mi;

    while (n--) {
        char op;
        int  x;
        cin >> op >> x;

        switch (op) {
            case 'I': {
                x += chg;
                if (x >= mi) {
                    T.insert({x, n});
                }
            } break;
            case 'A': {
                mi -= x;
                chg -= x;
            } break;
            case 'S': {
                mi += x;
                chg += x;
                T.split({mi, -1}, TE);
                ans += TE.size();
            } break;
            case 'F': {
                printf((x > T.size()
                                ? "-1\n"
                                : "%d\n"),
                       T.find_by_order(x - 1)->val - chg);
            } break;
        }
    }

    cout << ans << endl;

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}