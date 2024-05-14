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

const ll p = 998244353;
int N;
string S;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> S;
    for(int i=0; i<N-1; i++) {
        if(S[i] != '1' && S[i+1] != '1') {
            cout << "-1\n";
            return 0;
        }
    }

    ll ans = 1;
    for(int i=N-2; i>=0; i--) {
        ans = (ans + 1 + (ans*(S[i+1]-'0' - 1) % p))  % p;
    }
    cout << ans-1 << endl;


    return 0;
}