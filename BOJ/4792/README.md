## [백준 4792 - 레드 블루 스패닝 트리](https://www.acmicpc.net/problem/4792)

### 알고리즘
- kruskal algorithm(MST, 최소 스패닝 트리)
- 분리 집합(union-find)

### 풀이
kruskal 알고리즘으로 스패닝 트리를 찾는다.  
이때 빨간색 간선을 우선으로 할지, 파란색 간선으로 우선으로 할지를 정한다.
1. 빨간색 간선을 최대로 연결했을 때의 파란색 간선의 개수를 min_blue 라 하자.
2. 파란색 간선을 최대로 연결했을 때의 파란색 간선의 개수를 max_blue 라 하자.
3. min_blue <= k <= max_blue 이면 가능하다.

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
```

### 참고
https://4legs-study.tistory.com/118