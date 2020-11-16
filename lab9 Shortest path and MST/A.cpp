#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> g;
vector<int> dist;


int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    g.resize(n);
    dist.resize(n, -1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dist[0] = 0;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int u : g[v]) {
            if (dist[u] == -1) {
                q.push(u);
                dist[u] = dist[v] + 1;
            }
        }
    }

    for (int j : dist) {
        cout << j << ' ';
    }


    return 0;
}
