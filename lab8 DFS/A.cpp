#include <bits/stdc++.h>

using namespace std;

// #define int long long

const int N = 100010;

vector<int> g[N];
vector<bool> used;
vector<int> s;
vector<int> color;
bool f;

void dfs1(int v) {
    color[v] = 1;
    for (int u : g[v]) {
        if (color[u] == 1) {
            f = true;
        } else if (color[u] == 0) {
            dfs1(u);
        }
    }
    color[v] = 2;
}

void dfs(int v) {
    used[v] = true;
    for (int u : g[v]) {
        if (!used[u]) {
            dfs(u);
        }
    }
    s.push_back(v);
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;
    used.resize(n, false);
    color.resize(n, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
    }

    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs1(i);
            if (f) {
                cout << -1;
                return 0;
            }
            dfs(i);
        }
    }

    reverse(s.begin(), s.end());
    for (int v : s) {
        ++v;
        cout << v << ' ';
    }

    return 0;
}
