#include <bits/stdc++.h>

using namespace std;

// #define int long long

const int N = 100010;

vector<int> g[N];
vector<int> wins;

void dfs(int v) {
    if (g[v].empty())  {
        wins[v] = 0;
    }
    int k = 0;
    for (int u : g[v]) {
        if (wins[u] == -1) {
            dfs(u);
        }
        k += wins[u];
    }
    wins[v] = (int) (k != (int) g[v].size());
}


signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, m, s;
    cin >> n >> m >> s;
    --s;
    wins.resize(n, -1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
    }
    dfs(s);
    if (wins[s] == 0) {
        cout << "Second player wins";
    } else {
        cout << "First player wins";
    }

    return 0;
}
