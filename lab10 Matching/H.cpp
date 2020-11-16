#include <bits/stdc++.h>

using namespace std;



void euler(int v, vector<multiset<int>> &g, deque<int> &ans) {
    while (!g[v].empty()) {
        auto a = g[v].begin();
        int u = *a;
        g[v].erase(a);
        g[u].erase(find(g[u].begin(), g[u].end(), v));
        euler(u, g, ans);
    }
    ans.push_back(v);
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    int m;
    cin >> m;
//    vector<vector<int>> f(n, vector<int>(n, 0));
    vector<multiset<int>> g(n);
    vector<int> odd_v;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].insert(b);
        g[b].insert(a);
    }
    for (int i = 0; i < n; i++) {
        if ((int)g[i].size() % 2) {
            odd_v.push_back(i);
        }
    }
    bool flag = (int)odd_v.size() >= 2;
    int new_v = n;
    if (flag) {
        g.push_back(multiset<int>());
        for (int i = 0; i < (int)odd_v.size(); i++) {
            g[odd_v[i]].insert(new_v);
            g[new_v].insert(odd_v[i]);
        }
    }
    deque<int> euler_cycle;
    euler(0, g, euler_cycle);
    if (odd_v.empty()) {
        cout << "1\n";
        for (int i : euler_cycle) {
            cout << i + 1 << ' ';
        }
        return 0;
    }
    vector<vector<int>> ans;
    ans.push_back(vector<int>());

    while (true) {
        if (euler_cycle.front() != new_v) {
            if (euler_cycle.front() != euler_cycle.back()) {
                euler_cycle.push_back(euler_cycle.front());
            }
            euler_cycle.pop_front();
        } else {
            euler_cycle.pop_front();
            break;
        }
    }

    for (int i = 0; i < (int)euler_cycle.size(); i++) {
        if (euler_cycle[i] == new_v) {
            ans.push_back(vector<int>());
            continue;
        }
        ans.back().push_back(euler_cycle[i]);
    }

    cout << ans.size() << '\n';
    for (auto i : ans) {
        for (int j : i) {
            cout << j + 1 <<  ' ';
        }
        cout << '\n';
    }
    return 0;
}
