#include <bits/stdc++.h>

using namespace std;

bool dfs_kuhn(int v, vector<vector<int>> &g, vector<int> &p, vector<bool> &used) {
    if (used[v]) {
        return false;
    }
    used[v] = true;
    for (int u : g[v]) {
        if (p[u] == -1 || dfs_kuhn(p[u], g, p, used)) {
            p[u] = v;
            return true;
        }
    }
    return false;
}

vector<int> max_matching(int n, int m, vector<vector<int>> &g) {
    vector<int> p(m, -1);
    for (int v = 0; v < n; v++) {
        vector<bool> used(n, false);
        dfs_kuhn(v, g, p, used);
    }
    return p;
}

pair<vector<bool>, vector<bool>> min_vertex_covering(int m,
                                                     int n,
                                                     vector<int> &p,
                                                     vector<vector<int>> &g) {
    vector<bool> used(m, false);
    for (int i = 0; i < n; i++) {
        if (p[i] != -1) {
            used[p[i]] = true;
        }
    }
    vector<bool> uL(m, false);
    vector<bool> uR(n, false);
    for (int i = 0; i < m; i++) {
        if (!used[i]) {
            queue<int> q;
            q.push(i);
            while (!q.empty()) {
                int v = q.front(); q.pop();
                uL[v] = true;
                for (int u : g[v]) {
                    if (!uR[u]) {
                        uR[u] = true;
                        if (p[u] != -1) {
                            q.push(p[u]);
                        }
                    }
                }
            }
        }
    }
    return make_pair(uL, uR);
}




signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<bool>> board(n, vector<bool>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c;
            cin >> c;
            board[i][j] = c == 'B';
        }
    }

    bool f = false;
    int current_change_diagonal = 1e9;
    vector<vector<int>> diagonal;

    for (int WWW = 0; WWW < 2; WWW++) {
        vector<vector<int>> g(n + m);
        for (int s = 0; s < n + m; s++) {
            for (int i = 0; i <= s; i++) {
                int j = s - i;
                if (i < n && j < m && board[i][j] != f) {
                    g[s].push_back(n - i - 1 + j);
                }
            }
            f ^= true;
        }
        vector<int> p = max_matching(n + m, n + m, g);
        auto ans = min_vertex_covering(n + m, n + m, p, g);
        int t = 0;
        for (bool i : ans.first) {
            if (!i) {
                t++;
            }
        }
        for (bool i : ans.second) {
            if (i) {
                t++;
            }
        }
        if (current_change_diagonal > t) {
            current_change_diagonal = t;
            diagonal.clear();
            for (int i = 0; i < n + m; i++) {
                if (!ans.first[i]) {
                    pair<int, int> point = {i, 0};
                    while (point.first >= n) {
                        point.first--;
                        point.second++;
                    }
                    vector<int> new_vec(4);
                    new_vec[0] = 1;
                    new_vec[1] = point.first + 1;
                    new_vec[2] = point.second + 1;
                    new_vec[3] = (WWW + i) % 2;
                    diagonal.push_back(new_vec);
                }
            }
            for (int i = 0; i < n + m; i++) {
                if (ans.second[i]) {
                    pair<int, int> point = {n - i - 1, 0};
                    while (point.first < 0) {
                        point.first++;
                        point.second++;
                    }
                    vector<int> new_vec(4);
                    new_vec[0] = 2;
                    new_vec[1] = point.first + 1;
                    new_vec[2] = point.second + 1;
                    new_vec[3] = (WWW + n - i - 1) % 2;
                    diagonal.push_back(new_vec);
                }
            }
        }
        f = true;
    }

    cout << diagonal.size() << '\n';

    for (auto i : diagonal) {
        cout << i[0] << ' ' << i[1] <<  ' ' << i[2] << ' ' << (i[3] == 0 ? 'W' : 'B');
        cout << '\n';
    }






    return 0;
}
