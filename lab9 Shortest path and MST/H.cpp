#include <bits/stdc++.h>

using namespace std;

struct edge {
    int u, v, w;
};

vector<int> a;

int Find(int v) {
    if (v == a[v]) return v;
    return a[v] = Find(a[v]);
}

void merge(int u, int v) {
    v = Find(v);
    u = Find(u);
    if (u != v) {
        a[u] = v;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) a[i] = i;

    vector<edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }
    sort(edges.begin(), edges.end(), [&](edge l, edge r) {
        return l.w < r.w;
    });

    int k = n;
    int ans = 0;
    for (edge e : edges) {
        if (Find(e.u) != Find(e.v)) {
            k--;
            merge(e.u, e.v);
            ans += e.w;
            if (k == 1) {
                break;
            }
        }
    }
    cout << ans;


    return 0;
}