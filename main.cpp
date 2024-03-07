#include <iostream>
#include <algorithm>
#include <cmath>
#include <utility>
#include <string>
#include <cstring>
#include <vector>
#include <tuple>
#include <stack>
#include <queue>
#include <deque>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <climits>

#define endl "\n"
#define INF 987654321
#define INF2 2147483647
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

class Tree {
public:
    int N, LOG_MXN; // node: 1 ~ N
    vector<vector<int>> adj, parent;
    vector<int> depth;

    Tree() {}
    Tree(int _N) : N(_N), adj(N+1), depth(N+1, -1) {
        LOG_MXN = ceil(log(N)) + 1;
        parent = vector<vector<int>>(N+1, vector<int>(LOG_MXN+1));
    }
    void add_edge(int u, int v) {
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    void set_tree(int root, int lv=1) {
        queue<int> q;
        depth[root] = lv;
        parent[root][0] = root;
        q.emplace(root);
        while(!q.empty()) {
            int sz = q.size();
            lv++;
            while(sz--) {
                int u = q.front(); q.pop();
                for(int v : adj[u]) {
                    if(depth[v] != -1) continue;
                    depth[v] = lv;
                    parent[v][0] = u;
                    q.emplace(v);
                }
            }
        }
    }
    void link_ancestor() {
        for(int i=1; i<=LOG_MXN; i++) {
            for(int u=1; u<=N; u++) {
                parent[u][i] = parent[parent[u][i-1]][i-1];
            }
        }
    }
    int find_lca(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        int d = depth[a] - depth[b];
        for (int i = 0; d; i++) {
            if (d & 1) a = parent[a][i];
            d >>= 1;
        }
        if (a == b) return a;
        for (int i = LOG_MXN; i >= 0; i--)
            if (parent[a][i] != parent[b][i]) a = parent[a][i], b = parent[b][i];
        return parent[a][0];
    }
    void print_route(int u, int v) {
        int lca = find_lca(u,v);
        while(u != lca) {
            cout << u << ' ';
            u = parent[u][0];
        }
        cout << lca << ' ';
        vector<int> path;
        while(v != lca) {
            path.emplace_back(v);
            v = parent[v][0];
        }
        reverse(all(path));
        for(int x : path) cout << x << ' ';
        cout << endl;
    }
};

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n; cin >> n;
    Tree tree(n);
    vector<pii> edges;
    vector<vector<pii>> route(n+1);
    for(int i=0; i<2*n-3; i++) {
        int u, v; cin >> u >> v;
        edges.emplace_back(u,v);
        tree.add_edge(u,v);
    }
    for(int i=1; i<=n; i++) {
        if(tree.depth[i] != -1) continue;
        tree.set_tree(i);
    }
//    tree.set_tree(1);
    tree.link_ancestor();
    for(pii e : edges) {
        int u = e.first, v = e.second;
        int lca = tree.find_lca(u,v);
        int len = tree.depth[u] + tree.depth[v] - 2*tree.depth[lca] + 1;
        if(len >= 3) route[len].emplace_back(u,v);
    }
    for(int i=3; i<=n; i++) {
        if(route[i].size() < 2) continue;
        cout << i << endl;
        for(int j=0; j<2; j++) {
            pii e = route[i][j];
            tree.print_route(e.first, e.second);
        }
        return 0;
    }
    cout << -1;
    return 0;
}