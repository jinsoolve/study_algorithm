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
#include <climits>

#define INF 987654321
#define INF2 2147483647
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

int n, m, k;
int p[1001];
vector<pii> red, blue;

int F(int i) {
    if(i == p[i]) return i;
    return p[i] = F(p[i]);
}
void U(int a, int b) {
    a = F(a), b = F(b);
    p[b] = a;
}
pii kruskal(vector<pii> &e1, vector<pii> &e2) {
    int cnt1 = 0, cnt2 = 0;
    for(int i=1; i<=n; i++) p[i] = i;
    for(pii e : e1) {
        int u = e.first, v = e.second;
        if(F(u) == F(v)) continue;
        U(u,v);
        cnt1++;
    }
    for(pii e : e2) {
        int u = e.first, v = e.second;
        if(F(u) == F(v)) continue;
        U(u,v);
        cnt2++;
    }
    return {cnt1, cnt2};
}
int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    while(true) {
        blue.resize(0); red.resize(0);
        cin >> n >> m >> k;
        if(n==0 && m==0 && k==0) break;
        while(m--) {
            char c; int f, t; cin >> c >> f >> t;
            if(c=='R') red.emplace_back(f,t);
            else blue.emplace_back(f,t);
        }
        int min_blue = kruskal(red,blue).second;
        int max_blue = kruskal(blue, red).first;
        cout << (min_blue <= k && k <= max_blue) << '\n';
    }

    return 0;
}