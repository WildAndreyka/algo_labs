#include <bits/stdc++.h>

using namespace std;

// #define int long long

const int N = 100010;

vector<int> g[N];
vector<int> color;
bool f;

void dfs(int v, int k) {
    color[v] = k;
    for (int u : g[v]) {
        if (color[u] == -1) {
            dfs(u, 1 - k);
        } else if (color[u] == k) {
            f = true;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;
    color.resize(n, -1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int v = 0; v < n; v++) {
        if (color[v] == -1) {
            dfs(v, 0);
        }
    }

    if (f) {
        cout << "NO";
    } else {
        cout << "YES";
    }

    return 0;
}