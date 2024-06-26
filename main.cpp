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

const ll MOD = 998244353;

// a^b mod c
ll Pow(ll a, ll b, ll c = MOD) {
    a %= c, b %= c;
    ll res = 1;
    while(b) {
        if(b%2) res = (res * a) % c;
        a = (a * a) % c;
        b >>= 1;
    }
    return res;
}

ll Mul(ll a, ll b, ll c = MOD) {
    a %= c, b %= c;
    return (a*b)%c;
}
ll Add(ll a, ll b, ll c = MOD) {
    a %= c, b %= c;
    return (a+b) % c;
}
ll Sub(ll a, ll b, ll c = MOD) {
    a %= c, b %= c;
    ll res = a - b;
    if(res < 0) res += c;
    return res;
}
ll Div(ll a, ll b, ll c = MOD) {
    a %= c; b %= c;
    return Mul(a, Pow(b,c-2));
}

void solve() {
    ll n, k; cin >> n >> k;
    ll a = Div(n-2, n);
    ll b = Div(2, Mul(n,n));
    ll a_k = Pow(a,k);

    ll x1 = 1;
    ll x1_k = Add(Mul(a_k,x1), Mul(b, Div(a_k-1, a-1)));
    ll x2_k = Div(Sub(1, x1_k), n-1);

    ll ans = Add(x1_k, Mul(x2_k, Sub(Div(Mul(n,n+1),2), 1)));
    cout << ans;
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