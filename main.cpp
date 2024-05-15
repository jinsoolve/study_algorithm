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

const int mxn = 5001;
int N, M;
vector<int> g[mxn];
vector<int> W(mxn), A(mxn);
ll bag[mxn][mxn];
ll dp[mxn];
vector<int> order;

bool cmp(int a, int b) {
    return W[a] < W[b];
}
ll knapsack(int u) {
    ll &ret = dp[u];
    for(int i=1; i<=g[u].size(); i++) {
        int v = g[u][i-1];
        for(int w=1; w<=W[u]; w++) {
            if(w <= W[v]) bag[i][w] = bag[i-1][w];
            else bag[i][w] = max(bag[i-1][w], dp[v] + bag[i-1][w-W[v]]);
        }
    }
    return ret = bag[g[u].size()][W[u]] + 1;
}


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> M;
    while(M--) {
        int u, v; cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    for(int i=1; i<=N; i++) cin >> W[i];
    for(int i=1; i<=N; i++) cin >> A[i];

    for(int i=1; i<=N; i++) order.emplace_back(i);
    sort(all(order), cmp);
    for(int &u : order) {
        knapsack(u);
    }

    ll ans = 0;
    for(int i=1; i<=N; i++) {
        ans += A[i] * dp[i];
    }
    cout << ans << endl;

    return 0;
}