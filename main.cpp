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

const int MAX_N = 501, INF = 1e9;
int N;
vector<int> adj[MAX_N];
vector<int> t(MAX_N), s(MAX_N), g(MAX_N);

int medicine_cnt = 0;
vector<int> medicine_idx(MAX_N);

enum {Enemy=1, Medicine};

struct cmp {
    bool operator()(int a, int b) {
        return s[a] > s[b];
    }
};

struct State {
    ll strength = 0;
    int conquer = 0;
    priority_queue<int, vector<int>, cmp> enemies;
    set<int> medicines;

    bool check() const {
        return (conquer + medicines.size() == N);
    }
} A[1<<10];

void move(State &a, int here) {
    a.conquer++;
    for(int &there : adj[here]) {
        if(t[there] == Enemy) a.enemies.emplace(there);
        else a.medicines.insert(there);
    }
}
void work(State &a) {
    auto &[strength, conquer, enemies, medicines] = a;
    while(!enemies.empty()) {
        int enemy = enemies.top();
        if(strength < s[enemy]) break;
        enemies.pop();
        strength += g[enemy];
        move(a,enemy);
    }
}

bool solve() {
    // init
    A[0].strength = 1; A[0].enemies.emplace(1);

    for(int state=0; state<(1<<medicine_cnt); state++) {
        work(A[state]);
        if(A[state].strength >= INF || A[state].check()) return true;
        // take one of medicines and update max strength
        for(int medicine : A[state].medicines) {
            int nstate = state | (1<<medicine_idx[medicine]);
            if(A[state].strength * g[medicine] <= A[nstate].strength) continue;
            A[nstate] = A[state];
            A[nstate].strength *= g[medicine];
            A[nstate].medicines.erase(medicine);
            move(A[nstate], medicine);
        }
    }
    return false;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin >> N;
    for(int i=2; i<=N; i++) {
        int p; cin >> p >> t[i] >> s[i] >> g[i];
        adj[p].emplace_back(i);
        if(t[i] == 2) medicine_idx[i] = medicine_cnt++;
    }

    cout << (solve() ? "Yes" : "No") << endl;

    return 0;
}