#include <bits/stdc++.h>

using namespace std;

// #define int long long

const int N = 100010;

vector<int> g[N];
vector<int> s;
vector<int> color;
bool f;

void dfs(int v) {
    color[v] = 1;
    if (f) return;
    for (int u : g[v]) {
        if (f) break;
        if (color[u] == 1) {
            f = true;
            int S = u;
            do {
                s.push_back(S);
                for (int V : g[S]) {
                    if (color[V] == 1) {
                        S = V;
                        break;
                    }
                }
            } while (S != u);
            return;
        } else if (color[u] == 0) {
            dfs(u);
        }
    }
    color[v] = 2;
}


signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;
    color.resize(n, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
    }

    for (int i = 0; i < n; ++i) {
        if (f) break;
        if (color[i] == 0) {
            dfs(i);
        }
    }

    if (f) {
        cout << "YES\n";
        for (int v : s) {
            cout << v + 1 << ' ';
        }
    } else {
        cout << "NO";
    }
    return 0;
}
