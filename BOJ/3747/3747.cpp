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

class SCC {
private:
    int N, _id, _scc;
    vector<int> id, scc, cnt, dp; //scc[x] := x번 노드의 scc 번호, cnt[scc_x] := scc_x번의 scc의 집합 크기, dp[x] := src->x 의 최대 개수(bfs)
    vector<vector<int>> g, scc_g;
    stack<int> st;

    int dfs(int u) {
        id[u] = _id++;
        st.push(u);

        int parent = id[u];
        for(int v : g[u]) {
            if(id[v] == -1) parent = min(parent, dfs(v));
            else if(scc[v] == -1) parent = min(parent, id[v]);
        }

        if(parent == id[u]) {
            while(true) {
                int t = st.top(); st.pop();
                scc[t] = _scc;
                cnt[_scc]++;
                if(t == u) break;
            }
            _scc++;
        }

        return parent;
    }
    int bfs(int src, int sink) {
        dp = vector<int>(_scc, 0);
        queue<int> q;

        q.push(src); dp[src] = cnt[src];
        while(!q.empty()) {
            int here = q.front(); q.pop();
            for(int there : scc_g[here]) {
                if(dp[there] >= dp[here] + cnt[there]) continue;
                dp[there] = dp[here] + cnt[there];
                q.push(there);
            }
        }
        return dp[sink];
    }

public:
    SCC(int _N) : N(_N), _id(1), _scc(1), id(N+1, -1), scc(N+1, -1), cnt(N+1,0), g(N+1) {}

    void add_edge(int u, int v) { g[u].emplace_back(v); }
    void find_scc() {
        for(int i=1; i<=N; i++)
            if(id[i] == -1) dfs(i);
        scc_g.resize(_scc);
        for(int u=1; u<=N; u++) {
            for(int v : g[u]) {
                if(scc[u] != scc[v]) scc_g[scc[u]].emplace_back(scc[v]);
            }
        }
    }
    bool solve(int n) {
        find_scc();
        for(int i=1; i<=n; i++) {
            if(scc[2*i] == scc[2*i+1]) return false;
        }
        return true;
    }
};

inline int nodeNum(int i) { return (i<0 ? -2*i : 2*i+1); }
inline int oppositeNodeNum(int i) { return i + (i%2==0 ? 1 : -1); }

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int N, M;
    while(cin >> N >> M) {
        SCC scc(2*N+1);
        while(M--) {
            int i, j; cin >> i >> j;
            i = nodeNum(i), j = nodeNum(j);
            int ni = oppositeNodeNum(i), nj = oppositeNodeNum(j);
            scc.add_edge(ni, j);
            scc.add_edge(nj, i);
        }
        cout << scc.solve(N) << endl;
    }

    return 0;
}