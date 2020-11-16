#include <bits/stdc++.h>

using namespace std;

bool dfs(int v, vector<vector<int>> &g, vector<int> &p, vector<bool> &used) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (int u : g[v]) {
        if (p[u] == -1 || dfs(p[u], g, p, used)) {
            p[u] = v;
            return true;
        }
    }
    return false;
}




signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> g(n);
    vector<int> p(m, -1);
    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
    }
    int ans = 0;
    for (int v = 0; v < n; v++) {
        vector<bool> used(n, false);
        dfs(v, g, p, used);
    }
    for (int i : p) {
        if (i != -1) {
            ans++;
        }
    }
    cout << ans << '\n';
//    for (int i = 0; i < p.size(); i++) {
//        if (p[i] != -1) {
//            cout << p[i] + 1<< ' ' << i + 1 << '\n';
//        }
//    }

    return 0;
}
