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

int N, M;
vector<vector<int>> G;
vector<pii> E, path;
vector<int> dist;

int bfs(int src=1, int sink=N, int notToUse=-1) {
    queue<int> q;
    dist = vector<int>(N+1, -1); // dist[u] := src -> u dist
    dist[src] = 0;
    q.emplace(src);

    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int v=1; v<=N; v++) {
            if(G[u][v] == -1 || dist[v] != -1) continue;
            if(G[u][v] == notToUse) continue;
            dist[v] = dist[u] + 1;
            path[v] = {u,G[u][v]};
            q.emplace(v);
        }
    }
    return dist[sink];
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    G = vector<vector<int>>(N+1, vector<int>(N+1, -1));
    E = vector<pii>(M+1);
    for(int i=1; i<=M; i++) {
        int a, b; cin >> a >> b;
        G[a][b] = i;
        E[i] = {a,b};
    }

    path = vector<pii>(N+1); // path[v] = (u, e) := u -(e)-> v
    dist = vector<int>(N+1, -1); // dist[u] := src -> u dist
    if(bfs() == -1) {
        for(int i=1; i<=M; i++) cout << "-1\n";
        return 0;
    }

    vector<int> shortest_path;
    for(int u=N; u!=1; u=path[u].first) {
        shortest_path.emplace_back(path[u].second);
    }

    vector<int> ans(M+1, dist[N]);
    for(int e : shortest_path) {
        ans[e] = bfs(1,N,e);
    }

    for(int i=1; i<=M; i++) cout << ans[i] << endl;

    return 0;
}