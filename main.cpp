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

const int mxn = 2e5 + 1, p = 998244353;
int N, M;
vector<int> be[mxn]; // blocked edges
vector<int> vd[mxn]; // vd[d] := vertices in d
vector<int> dis(mxn, 0); // dis[v] := distance of vertex v

vector<int> tot(mxn); // tot[d] := total sum of number of case at distance of d
vector<int> num(mxn); // num[v] := number of case of path from 1 to v


void bfs() {
    queue<int> q; q.emplace(1); // visited vertices at current distance
    queue<int> del;
    set<int> uv; // unvisited vertices
    for(int i=2; i<=N; i++) uv.insert(i);
    vector<bool> blocked(N+1);

    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int &v : be[u]) blocked[v] = true;
        for(auto v : uv) {
            if(!blocked[v]) {
                del.emplace(v);
                dis[v] = dis[u]+1;
                vd[dis[v]].emplace_back(v);
                q.emplace(v);
            }
        }
        while(!del.empty()) {
            uv.erase(del.front());
            del.pop();
        }
        for(int &v : be[u]) blocked[v] = false;
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    while(M--) {
        int u, v; cin >> u >> v;
        be[u].emplace_back(v);
        be[v].emplace_back(u);
    }

    bfs();
    tot[0] = 1;
    for(int d=1; d<=dis[N]; d++) {
        for(int &v : vd[d]) { // u->v
            num[v] += tot[d-1];
            for(int &u : be[v]) {
                if(dis[u]+1 == dis[v])
                    num[v] = (num[v] - num[u] + p) % p;
            }
            tot[dis[v]] = (tot[dis[v]] + num[v]) % p;
        }
    }
    if(dis[N]) cout << num[N] << endl;
    else cout << -1 << endl;

    return 0;
}