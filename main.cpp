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

#define INF2 2147483647
#define all(v) (v).begin(), (v).end()

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using ti3 = tuple<int, int, int>;

const int mxn = 81;
const ll INF = numeric_limits<ll>::max();
int N;
ll P[mxn][mxn], R[mxn][mxn], D[mxn][mxn];

pll dp[mxn][mxn]; // dp[x][y] := (1,1) -> (x,y) 일 때의 <최소 횟수, 최대 비용>
ll cost[mxn][mxn];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=1; i<=N; i++)
        for(int j=1; j<=N; j++)
            cin >> P[i][j];
    for(int i=1; i<=N; i++)
        for(int j=1; j<=N-1; j++)
            cin >> R[i][j];
    for(int i=1; i<=N-1; i++)
        for(int j=1; j<=N; j++)
            cin >> D[i][j];

    for(int i=1; i<=N; i++)
        for(int j=1; j<=N; j++)
            dp[i][j] = {INF, INF};

    dp[1][1] = {0,0};
    for(int x=1; x<=N; x++) {
        for(int y=1; y<=N; y++) {
            auto &[turn, money] = dp[x][y];
            money *= -1;
            cost[x][y] = 0;
            for(int nx=x; nx<=N; nx++) {
                for(int ny=y; ny<=N; ny++) {
                    if(x==nx && y==ny) continue;
                    // (x,y) -> (nx,ny), P[x][y]를 이용해서 돈을 벌 때에 대해 계산
                    cost[nx][ny] = INF;
                    if(x < nx) cost[nx][ny] = min(cost[nx][ny], cost[nx-1][ny] + D[nx-1][ny]);
                    if(y < ny) cost[nx][ny] = min(cost[nx][ny], cost[nx][ny-1] + R[nx][ny-1]);

                    if(money >= cost[nx][ny])
                        dp[nx][ny] = min(dp[nx][ny], {turn, -(money - cost[nx][ny])});
                    else {
                        auto add = (cost[nx][ny] - money + P[x][y]-1) / P[x][y];
                        dp[nx][ny] = min(dp[nx][ny], {turn+add, -(money + add*P[x][y] - cost[nx][ny])});
                    }
                }
            }
        }
    }

    cout << dp[N][N].first + 2*N - 2 << endl;

    return 0;
}