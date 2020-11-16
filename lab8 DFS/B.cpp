#include <bits/stdc++.h>

using namespace std;

// #define int long long

const int N = 20010;

vector<int> g[N];
vector<int> g_inv[N];
vector<int> strongly_connected;
vector<int> a;
vector<bool> used;

void dfs(int v) {
    used[v] = true;
    for (int u : g[v]) {
        if (!used[u]) {
            dfs(u);
        }
    }
    a.push_back(v);
}

void dfs_inv(int v, int k) {
    strongly_connected[v] = k;
    for (int u : g_inv[v]) {
        if (strongly_connected[u] == -1) {
            dfs_inv(u, k);
        }
    }
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;
    strongly_connected.resize(n, -1);
    used.resize(n, false);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g_inv[v].push_back(u);
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
    cout << k << '\n';
    for (int v : strongly_connected) {
        cout << v + 1 << ' ';
    }


    return 0;
}
