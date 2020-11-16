#include <bits/stdc++.h>

using namespace std;

// #define int long long

const int N = 20010;
const int inf = 1e9;

vector<int> g[N];
vector<int> tim;
vector<int> up;
vector<bool> cutpoint;
int T;

void dfs(int v, int p = -1) {
    up[v] = tim[v] = T++;
    int k = 0;
    for (int u : g[v]) {
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


signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;
    tim.resize(n, -1);
    up.resize(n, inf);
    cutpoint.resize(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 0; i < n; ++i) {
        if (tim[i] == -1) {
            dfs(i);
        }
    }

    int k = 0;
    for (int i = 0; i < n; ++i) {
        if (cutpoint[i]) {
            k++;
        }
    }
    cout << k << '\n';
    for (int i = 0; i < n; ++i) {
        if (cutpoint[i]) {
            cout << i + 1<< '\n';
        }
    }


    return 0;
}
