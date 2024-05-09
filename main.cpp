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

const int LCM = 840;
ll dp[LCM];

ll N, X, Y;
vector<ll> P, T;
int Q;

ll solve(ll q) {
    ll &ret = dp[q];
    if(ret != -1) return ret;
    ret = q + X;
    for(int i=1; i<N; i++) {
        ret = ((ret-1)/P[i]+1)*P[i] + T[i];
    }
    return ret += Y - q;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> X >> Y;
    P = vector<ll>(N);
    T = vector<ll>(N);
    for(int i=1; i<N; i++)
        cin >> P[i] >> T[i];

    memset(dp, -1, sizeof dp);
    cin >> Q;
    while(Q--) {
        ll q; cin >> q;
        cout << q + solve(q%LCM) << endl;
    }

    return 0;
}