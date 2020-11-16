#include <bits/stdc++.h>

using namespace std;



int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    const int inf = 1e9;
    int n, m;
    cin >> n >> m;

    vector<vector<int>> dist(n, vector<int>(n, inf));
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        dist[u][v] = w;
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    for (auto v : dist) {
        for (auto i : v) {
            cout << i << ' ';
        }
        cout << '\n';
    }


    return 0;
}
