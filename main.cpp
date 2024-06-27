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
vector<pii> a;
vector<int> lis;

void solve() {
    cin >> n; a.resize(n);
    For(i,n) {
        cin >> a[i].x >> a[i].y;
        if(a[i].x > a[i].y) swap(a[i].x, a[i].y);
    }
    sort(all(a));
    for(auto &[x,y] : a) {
        auto it = upper_bound(all(lis), y);
        if(it == lis.end()) lis.emplace_back(y);
        else *it = y;
    }
    cout << lis.size() << endl;
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