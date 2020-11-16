#include <bits/stdc++.h>

using namespace std;

// #define int long long

const int N = 20010;
const int inf = 1e9 + 1;

vector<pair<int, int>> g[N];
vector<char> used;
vector<int> t_in;
vector<int> d;
int T;
set<int> ans;
void dfs(int v, int p = -1) {
    used[v] = true;
    t_in[v] = d[v] = T++;
    for (auto P : g[v]) {
        int u = P.first;
        if (u == p) continue;
        if (used[u]) {
            d[v] = min(d[v], t_in[u]);
        } else {
            dfs(u, v);
            d[v] = min(d[v], d[u]);
            if (d[u] > t_in[v]) {
                ans.insert(P.second);
            }
        }
    }
}


signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;
    used.resize(n, false);
    t_in.resize(n, inf);
    d.resize(n, inf);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].emplace_back(v, i + 1);
        g[v].emplace_back(u, i + 1);
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }
    cout << ans.size() << '\n';
    for (int i : ans) {
        cout << i << ' ';
    }

    return 0;
}