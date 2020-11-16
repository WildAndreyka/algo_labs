#include <bits/stdc++.h>

using namespace std;

// #define int long long

const int N = 20010;
const int inf = 1e9;

vector<pair<int, int>> g[N];
vector<int> tim;
vector<int> up;
vector<bool> cutpoint;
int T;

void dfs(int v, int p = -1) {
    up[v] = tim[v] = T++;
    int k = 0;
    for (auto P : g[v]) {
        int u = P.first;
        if (u == p) {
            continue;
        }
        if (tim[u] != -1) {
            up[v] = min(up[v], tim[u]);
        } else {
            dfs(u, v);
            k++;
            up[v] = min(up[v], up[u]);
            if (p != -1 && up[u] >= tim[v]) {
                cutpoint[v] = true;
            }
        }
    }
    if (p == -1 && k >= 2) {
        cutpoint[v] = true;
    }
}

vector<int> vertex_component;
vector<char> used;
int col;
void dfs1(int v, int cur_comp, int p = -1) {
    used[v] = true;
    for (auto[u, id] : g[v]) {
        if (u == p) {
            continue;
        }
        if (!used[u]) {
            if (up[u] >= tim[v]) {
                vertex_component[id] = ++col;
                dfs1(u, vertex_component[id], v);
            } else {
                vertex_component[id] = cur_comp;
                dfs1(u, cur_comp, v);
            }
        } else if (tim[u] < tim[v]) {
            vertex_component[id] = cur_comp;
        }
    }
}


signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;
    tim.resize(n, -1);
    up.resize(n, inf);
    cutpoint.resize(n);
    vertex_component.resize(m, -1);
    used.resize(n, false);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }

    for (int i = 0; i < n; ++i) {
        if (tim[i] == -1) {
            dfs(i);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs1(i, col);
        }
    }
    cout << col << '\n';
    for (int i = 0; i < m; ++i) {
        cout << vertex_component[i] << ' ';
    }



    return 0;
}
