#include <bits/stdc++.h>

using namespace std;

void euler(int v, vector<multiset<int>> &g, deque<int> &ans) {
    while (!g[v].empty()) {
        auto a = g[v].begin();
        int u = *a;
        g[v].erase(a);
        euler(u, g, ans);
    }
    ans.push_back(v);
}


signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int d, k;
    cin >> d >> k;
    if (k == 1) {
        for (int i = 0; i < d; i++) {
            cout << i;
        }
        return 0;
    }
    int q = (int)pow(d, k - 1);
    vector<multiset<int>> g(q);
    for (int l = 0; l < q; l++) {
        for (int j = 0; j < d; j++) {
            int v = (l * d + j) % q;
            g[l].insert(v);
        }
    }
    deque<int> euler_cycle;
    euler(0, g, euler_cycle);
    reverse(euler_cycle.begin(), euler_cycle.end());

    for (int i = 0; i < k - 2; i++) {
        cout << 0;
    }

    for (int i : euler_cycle) {
        cout << i % d;
    }
    return 0;
}
