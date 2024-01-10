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

int N;
vector<string> words;
vector<int> g[26];
int indegree[26];

string topological_sort() {
    int cnt = 0;
    string ret = "";
    queue<int> que;
    //최초 그래프에서 진입 차수가 0인 정점을 삽입
    for (int i = 0; i < 26; i++) {
        if (indegree[i] != -1) cnt++;
        if (indegree[i] == 0) que.push(i);
    }

    bool flag = false;
    while (!que.empty()) {
        if(que.size() > 1) flag = true;
        int cur = que.front(); que.pop();

        ret += (char)(cur+'a');

        //큐에서 꺼낸 정점과 연결된 모든 정점에 대해
        for (int i = 0; i < g[cur].size(); i++) {
            int nextnode = g[cur][i];
            //그 노드의 진입차수를 1 감소
            indegree[nextnode]--;

            //만약 그 노드의 진입차수가 0이 되었다면, 조건을 모두 만족했으므로 나아갈 수 있음
            //따라서 큐에 삽입한다.
            if (indegree[nextnode] == 0) que.push(nextnode);
        }
    }
    if(ret.length() != cnt) return "!";
    if(flag) return "?";
    return ret;
}
string solve() {
    for(int i=1; i<N; i++) {
        int j, minLen = min(words[i-1].length(), words[i].length());
        for(j=0; j<minLen; j++) {
            if(words[i-1][j] != words[i][j]) break;
        }
        if(j == words[i-1].length()) continue;
        if(j == words[i].length()) return "!";
        int u = words[i-1][j] - 'a', v =  words[i][j] - 'a';
        g[u].emplace_back(v);
        indegree[v]++;
    }
    return topological_sort();
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    memset(indegree, -1, sizeof indegree);

    cin >> N;
    words.resize(N);
    for(int i=0; i<N; i++) {
        cin >> words[i];
        for(char c : words[i]) indegree[c-'a'] = 0;
    }
    cout << solve() << endl;

    return 0;
}