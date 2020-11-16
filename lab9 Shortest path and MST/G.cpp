#include <bits/stdc++.h>

using namespace std;

struct point {
    int x, y;
};

struct edge {
    int u, v, w;
};

int len2(point a, point b) {
    int dx = abs(a.x - b.x);
    int dy = abs(a.y - b.y);
    return dx * dx + dy * dy;
}

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
    int n;
    cin >> n;
    vector<point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }
    sort(points.begin(), points.end(), [](point a, point b) {
        return (a.x < b.x) || (a.x == b.x && a.y < b.y);
    });

    vector<edge> edges;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edge e;
            e.u = i;
            e.v = j;
            e.w = len2(points[i], points[j]);
            edges.push_back(e);
        }
    }

    sort(edges.begin(), edges.end(), [&](edge l, edge r) {
        return l.w < r.w;
    });
    a.resize(n);
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
    int k = n;
    double ans = 0.;
    for (edge e : edges) {
        if (Find(e.u) != Find(e.v)) {
            k--;
            merge(e.u, e.v);
            ans += sqrt(e.w);
            if (k == 1) {
                break;
            }
        }
    }
    cout << setprecision(20) << ans;



    return 0;
}
