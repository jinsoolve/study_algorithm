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

const int mxn = 1e6;
int m, n;
vector<int> p, idx, dp;
vector<bool> visited;
stack<int> s;
int ans = 0;

int dfs(int u) {
    int &ret = dp[idx[u]];
    if(ret != -1) return ret;
    if(visited[u]) { // new cycle
        while(!s.empty() && s.top() != u) {
            idx[s.top()] = u;
            s.pop();
        }
        return 0;
    }
    visited[u] = true;
    s.emplace(u);
    return ret = dfs(p[u]) + 1;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> m >> n;

    p = vector<int>(n);
    idx = vector<int>(n);
    for(int i=0; i<n; i++) idx[i] = p[i] = i;
    dp = vector<int>(n, -1);
    visited = vector<bool>(n, false);

    while(m--) {
        int u, v; cin >> u >> v;
        p[u] = v;
    }
    for(int i=0; i<n; i++) {
        if(visited[i]) continue;

        while(!s.empty()) s.pop();
        ans = max(ans, dfs(i));
    }
    cout << ans << endl;

    return 0;
}