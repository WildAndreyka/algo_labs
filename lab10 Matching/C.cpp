#include <bits/stdc++.h>

using namespace std;



signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int m, n;
    cin >> m >> n;
    vector<vector<int>> g(m);
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        while (k--) {
            int v;
            cin >> v;
            v--;
            g[i].push_back(v);
        }
    }
    int ans = 0;
    vector<int> p(n, -1);
    vector<bool> used(m, false);
    for (int i = 0; i < m; i++) {
        int v;
        cin >> v;
        v--;
        if (v != -1) {
            ans++;
            p[v] = i;
            used[i] = true;
        }
    }
    vector<bool> uL(m, false);
    vector<bool> uR(n, false);
    for (int i = 0; i < m; i++) {
        if (!used[i]) {
            queue<int> q;
            q.push(i);
            while (!q.empty()) {
                int v = q.front(); q.pop();
                uL[v] = true;
                for (int u : g[v]) {
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
        if (!uL[i]) {
            ans1++;
        }
    }
    cout << ans1 <<  ' ';
    for (int i = 0; i < m; i++) {
        if (!uL[i]) {
            cout << i + 1 << ' ';
        }
    }
    cout << '\n';
    int ans2 = 0;
    for (int i = 0; i < n; i++) {
        if (uR[i]) {
            ans2++;
        }
    }
    cout << ans2 << ' ';
    for (int i = 0; i < n; i++) {
        if (uR[i]) {
            cout << i + 1 << ' ';
        }
    }
    return 0;
}
