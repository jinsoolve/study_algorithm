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

int N, H, W;
int a[7], b[7];
bool c[10][10];


bool check(int x, int y, int h, int w) {
    if(x+h > H || y+w > W) return false;
    for(int nx=x; nx<x+h; nx++) {
        for(int ny=y; ny<y+w; ny++) {
            if(c[nx][ny]) return false;
        }
    }
    return true;
}
void color(int x, int y, int h, int w, bool val) {
    for(int nx=x; nx<x+h; nx++) {
        for(int ny=y; ny<y+w; ny++) {
            c[nx][ny] = val;
        }
    }
}

bool dfs(int tile, int sx, int sy) {
    while(sx<H && c[sx][sy]) {
        if(++sy == W) ++sx, sy=0;
    }
    if(sx == H) return true;

    for(int i=0; i<N; i++) {
        if(((1<<i) & tile) == 0) continue;
        // axb
        if(check(sx,sy,a[i],b[i])) {
            color(sx,sy,a[i],b[i],true);
            if(dfs(tile-(1<<i),sx,sy)) return true;
            color(sx,sy,a[i],b[i],false);
        }

        // bxa
        if(a[i] != b[i] && check(sx,sy,b[i],a[i])) {
            color(sx,sy,b[i],a[i],true);
            if(dfs(tile-(1<<i),sx,sy)) return true;
            color(sx,sy,b[i],a[i],false);
        }
    }

    return false;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N >> H >> W;
    for(int i=0; i<N; i++)
        cin >> a[i] >> b[i];
    memset(c, 0, sizeof c);
    cout << (dfs((1<<N)-1, 0, 0) ? "Yes" : "No") << endl;

    return 0;
}