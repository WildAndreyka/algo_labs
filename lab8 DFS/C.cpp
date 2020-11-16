#include <bits/stdc++.h>

using namespace std;

// #define int long long

const int N = 100010;
const int inf = 1'000'000'000;


vector<pair<int, int>> g[N];
vector<char> used;
vector<int> top_sort;
vector<int> color;
bool f;

void dfs1(int v) {
    color[v] = 1;
    for (auto u : g[v]) {
        if (color[u.first] == 1) {
            f = true;
        } else if (color[u.first] == 0) {
            dfs1(u.first);
        }
    }
    color[v] = 2;
}

void dfs(int v) {
    used[v] = true;
    for (auto u : g[v]) {
        if (!used[u.first]) {
            dfs(u.first);
        }
    }
    top_sort.push_back(v);
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, m;
    cin >> n >> m;
    int s, t;
    cin >> s >> t;
    --s, --t;
    used.resize(n, false);
    color.resize(n, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        int w;
        cin >> w;
        --u, --v;
        g[u].emplace_back(v, w);
    }

    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs1(i);
            if (f) {
                cout << -1;
                return 0;
            }
            dfs(i);
        }
    }

    reverse(top_sort.begin(), top_sort.end());
    int s_ = find(top_sort.begin(), top_sort.end(), s) - top_sort.begin();
    vector<int> dp(n, inf);
    dp[s] = 0;
    for (int i = s_; i < n; i++) {
        int v = top_sort[i];
        if (dp[v] == inf) {
            continue;
        }
        for (auto p : g[v]) {
            dp[p.first] = min(dp[p.first], dp[v] + p.second);
        }
    }

    if (dp[t] == inf) {
        cout << "Unreachable";
    } else {
        cout << dp[t];
    }

    return 0;
}
