## [백준 13144 - List of Unique Numbers](https://www.acmicpc.net/problem/13144)

### 풀이
투포인터를 사용하여 풀면 해결되는 문제다.<br/>
1. s ~ e에서 e+1 값을 추가할 때 e+1이 이미 방문했으면 s에서 시작할 때는 e까지가 최선이다.
2. cnt[s++] = false 처리를 해준다.
3. 1~2를 끝까지 반복한다.

```c++
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

int N;
vector<int> v(101010);
bool cnt[101010];

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=1; i<=N; i++) cin >> v[i];

    ll ans = 0;
    for(int s=1, e=1; s<=N; s++) {
        while(e <= N) {
            if(cnt[v[e]]) break;
            cnt[v[e++]] = true;
        }
        ans += (e-s);
        cnt[v[s]] = false;
    }
    cout << ans << '\n';
    return 0;
}
```
### 후기
처음엔 어렵게 생각해서 세그먼트트리로 풀었는데 지금보니 투포인터가 훨씬 좋은 코드다.