#include <bits/stdc++.h>

#define endl "\n"
#define all(v) (v).begin(), (v).end()
#define For(i, n) for(int i=0; i<n; ++i)
#define For1(i, n) for(int i=1; i<=n; ++i)
#define For2(i, a, b) for(int i=(a); i<=(b); ++i)
#define x first
#define y second
#define Get(i, v) get<i>(v)

using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;
using tl3 = tuple<ll, ll, ll>;

const int INF = numeric_limits<int>::max();
const ll LNF = numeric_limits<ll>::max();

int n;
vector<ll> a, psum, dp;

ll sol(int i) {
    if(i == 1) return max(0LL, psum[i]);
    ll &ret = dp[i];
    if(ret != -1) return ret;
    return ret = max(sol(i-1), psum[i] - sol(i-1));
}

void solve() {
    int n; cin >> n;
    a.resize(n+1, 0); psum.resize(n+1, 0);
    For1(i,n) {
        cin >> a[i];
        psum[i] = psum[i-1] + a[i];
    }

    dp.resize(n+1, -1);
    cout << sol(n);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int tc = 1;
//    cin >> tc;
    while(tc--) {
        solve();
//        cout << solve() << endl;
    }


    return 0;
}