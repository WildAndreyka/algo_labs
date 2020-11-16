#include <bits/stdc++.h>

using namespace std;

const long long inf = LLONG_MAX/2;

struct edge {
    int u, v;
    long long w;
};


signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, m, s;
    cin >> n >> m >> s;
    s--;
    vector<edge> edges(m);
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        u--, v--;
        edges[i].u = u;
        edges[i].v = v;
        edges[i].w = w;
        g[u].push_back(v);
    }

    vector<long long> dist(n, inf);
    dist[s] = 0ll;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m; j++) {
            if (dist[edges[j].u] < inf) {
                dist[edges[j].v] =  max(-inf, min(dist[edges[j].v], dist[edges[j].u] + edges[j].w));
            }
        }
    }

    vector<bool> used(n);
    for (int j = 0; j < m; j++) {
        if (dist[edges[j].u] < inf) {
            if (dist[edges[j].v] > dist[edges[j].u] + edges[j].w) {
                used[edges[j].u] = true;
            }
        }
    }

    function<void(int)> dfs = [&](int v) {
        used[v] = true;
        for (int u : g[v]) {
            if (!used[u]) {
                dfs(u);
            }
        }
    };
    for (int i = 0; i < n; i++) {
        if (used[i]) {
            dfs(i);
        }
    }
    for (int i = 0; i < n; i++) {
        if (dist[i] == inf) {
            cout << "*\n";
            continue;
        }
        if (used[i]) {
            dfs(i);
            cout << "-\n";
            continue;
        }
        cout << 1ll * dist[i] << '\n';
    }

    return 0;
}
