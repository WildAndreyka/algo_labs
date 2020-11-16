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

vector<int> s;
vector<int> color;
bool f;

void dfs1(int v, vector<vector<int>> &g) {
    color[v] = 1;
    for (int u : g[v]) {
        if (color[u] == 1) {
            f = true;
        } else if (color[u] == 0) {
            dfs1(u, g);
        }
    }
    color[v] = 2;
}

void dfs(int v, vector<vector<int>> &g, vector<bool> &used) {
    used[v] = true;
    for (int u : g[v]) {
        if (!used[u]) {
            dfs(u, g, used);
        }
    }
    s.push_back(v);
}


signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> p(n, -1);
    color.resize(n, 0);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        g[a].push_back(b);
    }
    int ans = 0;
    for (int v = 0; v < n; v++) {
        vector<bool> used(n, false);
        dfs_kuhn(v, g, p, used);
    }
    vector<bool> used(n, false);
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs1(i, g);
            if (f) {
                cout << -1;
                return 0;
            }
            dfs(i, g, used);
        }
    }
    fill(used.begin(), used.end(), false);
    for (int v : s) {
        if (!used[v]) {
            ans++;
            used[v] = true;
            while (p[v] != -1) {
                v = p[v];
                used[v] = true;
            }
        }
    }
    cout << ans;
    return 0;
}
