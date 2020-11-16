#include <bits/stdc++.h>

using namespace std;


signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    const long long inf = 1e18;
    int n, s, f;
    cin >> n >> s >> f;
    s--, f--;
    vector<vector<long long>> g(n, vector<long long>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> g[i][j];
        }
    }

    vector<long long> dist(n, inf);
    vector<bool> used(n, false);
    dist[s] = 0;
    for (int i = 0; i < n; i++) {
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!used[j] && (v == -1 || dist[j] < dist[v])) {
                v = j;
            }
        }
        if (dist[v] == inf) {
            break;
        }
        used[v] = true;
        for (int j = 0; j < n; j++) {
            if (j != v && g[v][j] != -1) {
                if (dist[v] + g[v][j] < dist[j]) {
                    dist[j] = dist[v] + g[v][j];
                }
            }
        }
    }
    if (dist[f] == inf) {
        cout << -1;
    } else {
        cout << dist[f];
    }




    return 0;
}
