#include <bits/stdc++.h>

using namespace std;

// #define int long long

const int N = 100010;

vector<int> g[N];
vector<int> a;

void dfs(int v, int k) {
    a[v] = k;
    for (int u : g[v]) {
        if (a[u] == -1) {
            dfs(u, k);
        }
    }
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;
    a.resize(n, -1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int k = 0;
    for (int v = 0; v < n; v++) {
        if (a[v] == -1) {
            dfs(v, k++);
        }
    }

    for (int i : a) {
        cout << i + 1 << ' ';
    }


    return 0;
}
