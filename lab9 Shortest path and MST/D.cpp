#include <bits/stdc++.h>

using namespace std;



int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    const int inf = 1e9;
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }

    vector<int> dist(n, inf);
    vector<bool> used(n, false);
    dist[0] = 0;
    priority_queue<pair<int, int>> q;
    q.push({0, 0});
    while (!q.empty()) {
        int v = q.top().second;
        q.pop();
        if (used[v]) {
            continue;
        }
        used[v] = true;
        for (auto p : g[v]) {
            int u = p.first;
            int w = p.second;
            if (dist[v] + w < dist[u]) {
                dist[u] = dist[v] + w;
                q.push({-dist[u], u});
            }
        }
    }

    for (int i : dist) {
        cout << i << ' ';
    }




    return 0;
}
