#include <bits/stdc++.h>

using namespace std;

// #define int long long

const long long inf = 1e18;

pair<vector<int>, int> find_strongly_connected(vector<vector<int>> & g) {
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
    return make_pair(strongly_connected, k);
}


long long findMST(vector<vector<pair<int, long long>>> & g, int root = 0) {
    long long res = 0;
    int n = (int) g.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (int) g[i].size(); j++) {
            while (j != (int) g[i].size() - 1 && g[i][j].first == root) {
                swap(g[i][j], g[i][g[i].size() - 1]);
                g[i].pop_back();
            }
            if (j == (int) g[i].size() - 1 && g[i][j].first == root) {
                g[i].pop_back();
            }
        }
    }
    vector<long long> minEdges(n, inf);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (int) g[i].size(); j++) {
            minEdges[g[i][j].first] = min(minEdges[g[i][j].first], g[i][j].second);
        }
    }
    for (int i = 0; i < n; i++) {
        if (minEdges[i] != inf) {
            res += minEdges[i];
        }
    }
    vector<vector<int>> zeroEdges(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (int) g[i].size(); j++) {
            if (minEdges[g[i][j].first] == g[i][j].second) {
                zeroEdges[i].push_back(g[i][j].first);
            }
        }
    }

    queue<int> q;
    q.push(root);
    vector<int> used(n);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        used[v] = true;
        for (int u : zeroEdges[v]) {
            if (!used[u]) {
                q.push(u);
            }
        }
    }
    bool f = true;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            f = false;
            break;
        }
    }
    if (f) {
        return res;
    }

    pair<vector<int>, int> sc = find_strongly_connected(zeroEdges);
    vector<vector<pair<int, long long>>> new_g(sc.second);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (int) g[i].size(); j++) {
            if (sc.first[g[i][j].first] != sc.first[i]) {
                new_g[sc.first[i]].emplace_back(sc.first[g[i][j].first],
                                                g[i][j].second - minEdges[g[i][j].first]);
            }
        }
    }
    res += findMST(new_g, sc.first[root]);
    return res;
}



signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, long long>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        u--, v--;
        g[u].emplace_back(v, w);
    }
    vector<bool> used(n, false);
    function<void(int)> dfs = [&](int v) {
        used[v] = true;
        for (int i = 0; i < (int) g[v].size(); i++) {
            if (!used[g[v][i].first]) {
                dfs(g[v][i].first);
            }
        }
    };
    dfs(0);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    cout << findMST(g);

    return 0;
}
