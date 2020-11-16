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
//    vector<vector<int>> f(n, vector<int>(n, 0));
    vector<multiset<int>> g(n);
    deque<int> ans;
    vector<int> odd_v;
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        if (m % 2) {
            odd_v.push_back(i);
        }
        for (int j = 0; j < m; j++) {
            int v;
            cin >> v;
            v--;
            g[i].insert(v);
        }
    }
    if ((int)odd_v.size() > 2) {
        cout << -1;
        return 0;
    }
    bool flag = (int)odd_v.size() == 2;
    if (flag) {
        g[odd_v[0]].insert(odd_v[1]);
        g[odd_v[1]].insert(odd_v[0]);
    }

    euler(0, g, ans);
    if (flag) {
        while (true) {
            int a = ans[0];
            int b = ans[1];
            ans.pop_front();
            if (ans.back() != a) {
                ans.push_back(a);
            }
            if ((a == odd_v[0] && b == odd_v[1]) || (a == odd_v[1] && b == odd_v[0])) {
                break;
            }
        }
    }
    cout << ans.size() - 1 << '\n';
    for (int i : ans) {
        cout << i + 1 << ' ';
    }



    return 0;
}
