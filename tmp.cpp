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

using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAXN = 5e2 + 1, MAXK = 10;

int n, op[MAXN], s[MAXN], g[MAXN], id[MAXN], rid[MAXN], tot;
vector<int> ver[MAXN];

struct cmp {
    bool operator()(int i, int j) {
        return s[i] > s[j];
    }
};

struct State {
    ll hp;
    int cnt;
    priority_queue<int, vector<int>, cmp> monster;
    set<int> potion;
} a[1 << MAXK];

void work(State &a) {
    auto &[hp, cnt, monster, potion] = a;
    while (!monster.empty()) {
        int u = monster.top();
        if (hp < s[u]) break;
        hp += g[u], monster.pop(), cnt++;
        for (int v : ver[u]) {
            if (op[v] == 1) {
                monster.push(v);
            } else {
                potion.insert(v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for (int i = 2, p; i <= n; i++) {
        cin >> p >> op[i] >> s[i] >> g[i];
        ver[p].push_back(i);
        if (op[i] == 2) {
            id[i] = tot, rid[tot] = i, tot++;
        }
    }
    a[0].hp = 1, a[0].monster.push(1);
    for (int state = 0; state < 1 << tot; state++) {
        work(a[state]);
        if (a[state].hp >= 1e9 || a[state].cnt == n - tot) {
            cout << "Yes";
            return 0;
        }
        for (int u : a[state].potion) {
            int i = id[u], n_state = state | 1 << i;
            if (a[state].hp * g[u] > a[n_state].hp) {
                a[n_state] = a[state];
                a[n_state].hp *= g[u];
                a[n_state].potion.erase(u);
                for (int v : ver[u]) {
                    if (op[v] == 1) {
                        a[n_state].monster.push(v);
                    } else {
                        a[n_state].potion.insert(v);
                    }
                }
            }
        }
    }
    cout << "No";
    return 0;
}