#include <bits/stdc++.h>

using namespace std;

const long long inf = 1e18;

struct edge {
    int u, v;
    long long w;
};


signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n;
    cin >> n;
    int s = 0;
    vector<edge> edges;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            long long w;
            cin >> w;
            if (w != 1000000000) {
                edge e;
                e.u = i;
                e.v = j;
                e.w = w;
                edges.push_back(e);
            }
        }
    }

    vector<long long> dist(n, inf);
    dist[s] = 0ll;
    vector<int> p(n, -1);
    int x = -1;
    for (int i = 0; i < n; i++) {
        x = -1;
        for (int j = 0; j < (int) edges.size(); j++) {
           // if (dist[edges[j].u] < inf) {
                if (dist[edges[j].v] > dist[edges[j].u] + edges[j].w) {
                    dist[edges[j].v] = dist[edges[j].u] + edges[j].w;
                    dist[edges[j].v] = max(-inf, dist[edges[j].v]);
                    p[edges[j].v] = edges[j].u;
                    x = edges[j].v;
                }
           // }
        }
    }
    if (x == -1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        int y = x;
        for (int i = 0; i < n; i++) {
            y = p[y];
        }
        vector<int> cycle;
        for (int i = y; ; i = p[i]) {
            cycle.push_back(i);
            if (i == y && cycle.size() > 1) {
                break;
            }
        }
        reverse(cycle.begin(), cycle.end());
        cout << cycle.size() << '\n';
        for (int i : cycle) {
            cout << i + 1 << ' ';
        }
    }

    return 0;
}
