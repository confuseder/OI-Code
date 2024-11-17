#include <bits/stdc++.h>
using namespace std;

struct task {
    long long s, t, id;
};

int  n, m;
task tasks[200005];

priority_queue<int, vector<int>, greater<int>>                                  q1;
priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> q2;

vector<int> ans[200005];

int main() {

    // freopen("P11289.in", "r", stdin);
    // freopen("P11289.out", "w", stdout);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> tasks[i].s >> tasks[i].t;
        tasks[i].id = i;
    }

    sort(tasks + 1, tasks + n + 1, [](task a, task b) {
        return a.t < b.t;
    });

    for (int i = 1; i <= m; i++) {
        q1.push(i);
    }

    for (int i = 1; i <= n; i++) {
        auto now = tasks[i];

        while (!q2.empty() && q2.top().first <= now.t) {
            q1.push(q2.top().second);
            q2.pop();
        }

        if (!q1.empty()) {
            ans[q1.top()].push_back(now.id);
            q2.push({now.s + now.t, q1.top()});
            q1.pop();
        } else {
            auto j = q2.top();
            ans[q2.top().second].push_back(now.id);
            q2.pop();
            q2.push({j.first + now.s, j.second});
        }
    }

    for (int i = 1; i <= m; i++) {
        sort(ans[i].begin(), ans[i].end());

        cout << ans[i].size() << ' ';

        for (auto j : ans[i]) {
            cout << j << ' ';
        }
        cout << endl;
    }

    // fclose(stdin);
    // fclose(stdout);

    // system("pause");

    return 0;
}