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
#define f first
#define s second
#define x first
#define y second
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ti3 = tuple<int, int, int>;
using pll = pair<ll, ll>;

int sqrt_N;
struct Query {
    int idx, i, j, k;

    bool operator<(Query other) const {
        if(i/sqrt_N == other.i/sqrt_N) return j < other.j;
        return i < other.i;
    }
};

int N, M;
vector<ll> v(101010);
vector<Query> qs;
int cnt[101010];
int now = 0;

void add(int s, int e) {
    for(int i=s; i<=e; i++) {
        if(cnt[i]++ == 0) now++;
    }
}
void remove(int s, int e) {
    for(int i=s; i<=e; i++) {
        if(--cnt[i] == 0) now--;
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(cnt, 0, sizeof cnt);

    cin >> N;
    sqrt_N = sqrt(N);
    for(int i=1; i<=N; i++) cin >> v[i];
    cin >> M;
    for(int i=0; i<M; i++) cin >> qs[i].idx >> qs[i].i >> qs[i].j >> qs[i].k;
    sort(all(qs));

    int ldx = qs[0].i, rdx = qs[0].j;
    add(ldx,rdx);
    for(Query q : qs) {
        if(q.i < )
    }

    return 0;
}