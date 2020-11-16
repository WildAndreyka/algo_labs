#include <bits/stdc++.h>

using namespace std;


struct edge {
    int u, v, w;
};

vector<int> a;
vector<int> rang;


int find(int v) {
    return v == a[v] ? v : a[v] = find(a[v]);
}

void Union(int v, int u) {
    v = find(v);
    u = find(u);
    if (u != v) {
        if (rang[u] < rang[v]) {
            swap(u, v);
        }
        a[v] = u;
        if (rang[u] == rang[v]) {
            rang[u]++;
        }
    }
}




signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    const int inf = 2e9;

    int n, m;
    cin >> n >> m;
    a.resize(n);
    rang.resize(n, 0);
    vector<edge> edges(m);
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        edges[i].u--, edges[i].v--;
        g[edges[i].u].push_back(edges[i].v);
        g[edges[i].v].push_back(edges[i].u);
    }
    vector<bool> used(n, false);
    function<void(int)> dfs = [&](int v) {
        used[v] = true;
        for (int u : g[v]) {
            if (!used[u]) {
                dfs(u);
            }
        }
    };
    dfs(0);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            cout << "NO\n";
            return 0;
        }
    }
    cout << "YES\n";
    sort(edges.begin(), edges.end(), [](edge l, edge r) {
       return l.w < r.w;
    });
    int ans = inf;
    for (int k = 0; k < m; k++) {
        for (int i = 0; i < n; i++) {
            a[i] = i;
            rang[i] = 0;
        }
        int l = n;
        int j = k;
        int ans1 = edges[j].w;
        int ans2 = edges[j].w;
        while (j < m && l > 1) {
            if (find(edges[j].v) != find(edges[j].u)) {
                Union(edges[j].v, edges[j].u);
                l--;
                ans2 = edges[j].w;
            }
            j++;
        }
        if (l == 1) {
            ans = min(ans, ans2 - ans1);
        }
    }
    cout << ans;
    return 0;
}
