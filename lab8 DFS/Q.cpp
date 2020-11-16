#include <bits/stdc++.h>

using namespace std;

// #define int long long


vector<int> find_strongly_connected(vector<vector<int>> &g) {
    vector<int> strongly_connected;
    vector<int> a;
    vector<bool> used;
    int n = g.size();
    vector<vector<int>> g_inv(n);
    strongly_connected.resize(n, -1);
    used.resize(n, false);

    function<void(int)> dfs = [&](int v) {
        used[v] = true;
        for (int u : g[v]) {
            if (!used[u]) {
                dfs(u);
            }
        }
        a.push_back(v);
    };

    function<void(int, int)> dfs_inv = [&] (int v, int k) {
        strongly_connected[v] = k;
        for (int u : g_inv[v]) {
            if (strongly_connected[u] == -1) {
                dfs_inv(u, k);
            }
        }
    };

    for (int i = 0; i < n; i++) {
        for (int j : g[i]) {
            g_inv[j].push_back(i);
        }
    }

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i);
        }
    }
    reverse(a.begin(), a.end());
    int k = 0;
    for (int v : a) {
        if (strongly_connected[v] == -1) {
            dfs_inv(v, k++);
        }
    }
    return strongly_connected;
}







signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n;
    cin >> n;
    int m;
    cin >> m;
    if (m == 1) {
        cout << 1;
        return 0;
    }
    vector<pair<vector<int>, vector<int>>> cow_edges;
    for (int i = 0; i < m; ++i) {
        int a, b;
        char t;
        cin >> a >> b >> t;
        vector<int> u, v;
        if (t == 'T') {
            u = {a + n, -b + n, -a + n, b + n};
            v = {b + n, -a + n, -b + n, a + n};
        } else {
            u = {a + n, -b + n, -a + n, b + n};
            v = {-b + n, a + n, b + n, -a + n};
        }
        cow_edges.push_back(make_pair(u, v));
    }

    int l = 0;
    int r = m;
    while (r - l > 1) {
        int h = (r + l) / 2;
        vector<vector<int>> g(2 * n + 2);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < 4; j++) {
                g[cow_edges[i].first[j]].push_back(cow_edges[i].second[j]);
            }
        }
        vector<int> sc = find_strongly_connected(g);
        bool f = false;
        for (int i = 1; i <= n; i++) {
            if (sc[i + n] == sc[-i + n]) {
                f = true;
                break;
            }
        }
        if (f) {
            r = h;
        } else {
            l = h;
        }
    }

    for (int R = max(0, r - 3); R <= m; R++) {
        vector<vector<int>> g(2 * n + 2);
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < 4; j++) {
                g[cow_edges[i].first[j]].push_back(cow_edges[i].second[j]);
            }
        }
        vector<int> sc = find_strongly_connected(g);
        bool f = false;
        for (int i = 1; i <= n; i++) {
            if (sc[i + n] == sc[-i + n]) {
                f = true;
                break;
            }
        }
        if (!f) {
            r = R;
        } else {
            break;
        }
    }
    cout << r;


    return 0;
}
