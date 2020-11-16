#include <bits/stdc++.h>

using namespace std;

bool dfs_kuhn(int v, vector<vector<int>> &g, vector<int> &p, vector<bool> &used) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (int u : g[v]) {
        if (p[u] == -1 || dfs_kuhn(p[u], g, p, used)) {
            p[u] = v;
            return true;
        }
    }
    return false;
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int WWW;
    cin >> WWW;
    while (WWW--) {
        int m, n;
        cin >> m >> n;
        vector<vector<int>> uu(m, vector<int>(n, false));
        for (int i = 0; i < m; i++) {
            while (true) {
                int v;
                cin >> v;
                v--;
                if (v == -1) {
                    break;
                }
                uu[i][v] = true;
            }
        }
        vector<vector<int>> g_(m);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!uu[i][j]) {
                    g_[i].push_back(j);
                }
            }
        }
        vector<int> p(n, -1);
        for (int v = 0; v < m; v++) {
            vector<bool> used(m, false);
            dfs_kuhn(v, g_, p, used);
        }
        int ans = 0;
        vector<bool> used(m, false);
        for (int i = 0; i < n; i++) {
            if (p[i] != -1) {
                used[p[i]] = true;
                ans++;
            }
        }
        ans = n + m - ans;
        vector<bool> uL(m, false);
        vector<bool> uR(n, false);
        for (int i = 0; i < m; i++) {
            if (!used[i]) {
                queue<int> q;
                q.push(i);
                while (!q.empty()) {
                    int v = q.front(); q.pop();
                    uL[v] = true;
                    for (int u : g_[v]) {
                        if (!uR[u]) {
                            uR[u] = true;
                            if (p[u] != -1) {
                                q.push(p[u]);
                            }
                        }
                    }
                }
            }
        }
        cout << ans;
        cout << '\n';
        int ans1 = 0;
        for (int i = 0; i < m; i++) {
            if (uL[i]) {
                ans1++;
            }
        }
        cout << ans1 <<  ' ';
        int ans2 = 0;
        for (int i = 0; i < n; i++) {
            if (!uR[i]) {
                ans2++;
            }
        }
        cout << ans2 << '\n';
        for (int i = 0; i < m; i++) {
            if (uL[i]) {
                cout << i + 1 << ' ';
            }
        }
        cout << '\n';
        for (int i = 0; i < n; i++) {
            if (!uR[i]) {
                cout << i + 1 << ' ';
            }
        }
        cout << '\n';
        cout << '\n';
    }
    return 0;
}
