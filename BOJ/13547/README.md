## 백준 13547 - [수열과 쿼리 5](https://www.acmicpc.net/problem/13547)

### 풀이 - 온라인 쿼리 (머지소트 트리)
1. 자신보다 다음 인덱스에서 자신과 동일하면서 가장 가까운 수의 인덱스를 넣는다.<br/>
   [1,1,2,1,3] -> [2,4,6,6,6] 이 된다.<br/>
   배열이 A[s\~e]라고 할 때, e보다 큰 값의 개수가 서로 다른 수의 개수가 된다.<br/>
   위 예시는 A[1\~5]이므로 5보다 큰 수의 개수가 3이다.

2. 바뀐 배열을 머지소트 트리에 넣는다.
3. i~j에 포함되는 트리의 노드에서 이분탐색으로 해당 배열의 마지막 인덱스보다 큰 값의 개수를 찾는다. (머지소트 트리이므로 해당 배열은 정렬되어 있다. 이분탐색을 활용할 수 있다.)

```cpp
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

class segment {
public:
    vector<vector<int>> tree; //tree[node] := a[start ~ end] 의 합

    segment() {}
    segment(int size) {
        this->resize(size);
    }
    void resize(int size) {
        size = (int) floor(log2(size)) + 2;
        size = pow(2, size);
        tree.resize(size);
    }

    int query(int node, int start, int end, int left, int right) {
        if(right < start || end < left) return 0;
        if(left <= start && end <= right) return tree[node].end() - lower_bound(all(tree[node]), right+1);
        return query(2*node, start, (start+end)/2, left, right) + query(2*node+1, (start+end)/2+1, end, left, right);
    }
    void update(int node, int start, int end, int index, int value) {
        if(index < start || end < index) return;
        tree[node].emplace_back(value);
        if(start != end) {
            update(node * 2, start, (start + end) / 2, index, value);
            update(node * 2 + 1, (start + end) / 2 + 1, end, index, value);
        }
    }
};

const int MXN = 1e5;
int N, M;
vector<int> A(MXN+1);
vector<pii> nextIdx(MXN+1);
unordered_map<int,int> mp;

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=1; i<=N; i++) {
        cin >> A[i];
        mp[A[i]] = N+1;
    }
    for(int i=N; i>=1; i--) {
        nextIdx[i] = pii(mp[A[i]], i);
        mp[A[i]] = i;
    }
    sort(all(nextIdx));

    segment root(N);
    for(pii x : nextIdx) {
        root.update(1,1,N,x.s,x.f);
    }

    cin >> M;
    while(M--) {
        int i, j; cin >> i >> j;
        cout << root.query(1,1,N,i,j) << '\n';
    }
    return 0;
}
```
