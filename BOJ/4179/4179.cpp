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

int R, C;
bool board[1010][1010]; // false: can't go, true: can go
queue<pii> jihuns; //jihuns's location
queue<pii> fires;
bool visited[1010][1010];
int dx[] = {1,-1,0,0};
int dy[] = {0,0,-1,1};

bool out_of_bound(int i, int j) {
    return (i<0 || i>=R || j<0 || j>=C);
}
void fire_spreads() {
    int sz = fires.size();
    while(sz--) {
        int x = fires.front().x, y = fires.front().y;
        fires.pop();
        for(int d=0; d<4; d++) {
            int nx = x+dx[d], ny = y+dy[d];
            if(out_of_bound(nx, ny) || !board[nx][ny]) continue;
            board[nx][ny] = false;
            fires.emplace(nx,ny);
        }
    }
}
// can't move: -1, can move:0, can escape: 1
int jihuns_moves() {
    int sz = jihuns.size();
    while(sz--) {
        int x = jihuns.front().x, y = jihuns.front().y;
        jihuns.pop();
        for(int d=0; d<4; d++) {
            int nx = x+dx[d], ny = y+dy[d];
            if(out_of_bound(nx,ny)) return 1;
            if(!board[nx][ny] || visited[nx][ny]) continue;
            visited[nx][ny] = true;
            jihuns.emplace(nx,ny);
        }
    }
    return (jihuns.size() == 0) ? -1 : 0;
}

void print() {
    for(int i=0; i<R; i++) {
        for(int j=0; j<C; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
    cout << endl;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(board, 0, sizeof board);
    memset(visited, 0, sizeof visited);

    cin >> R >> C;
    for(int i=0; i<R; i++) {
        for(int j=0; j<C; j++) {
            char c; cin >> c;
            if(c == 'F') fires.emplace(i,j);
            if(c == 'J') {
                visited[i][j] = true;
                jihuns.emplace(i,j);
            }

            if(c == '.' || c == 'J') board[i][j] = true;
        }
    }

    int ans = 0;
    while(true) {
        fire_spreads();
        int res = jihuns_moves();
//        print();
        ans++;
        if(res == 0) continue;
        if(res == -1) ans = -1;
        break;
    }
    if(ans == -1) cout << "IMPOSSIBLE\n";
    else cout << ans << '\n';

    return 0;
}