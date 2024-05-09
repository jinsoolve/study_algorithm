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

const double MAX = 362880;
int grid[9];
vector<ti3> line {
        {0,1,2}, {3,4,5}, {6,7,8}, // horizontal
        {0,3,6}, {1,4,7}, {2,5,8}, // vertical
        {0,4,8}, {2,4,6} // diagonal
};
vector<int> order{1,2,3,4,5,6,7,8,9};

bool check() {
    for(auto &l : line) {
        int a = get<0>(l), b = get<1>(l), c = get<2>(l);
        if(grid[a] == grid[b] && order[a] < order[c] && order[b] < order[c]) return false;
        else if(grid[b] == grid[c] && order[b] < order[a] && order[c] < order[a]) return false;
        else if(grid[c] == grid[a] && order[c] < order[b] && order[a] < order[b]) return false;
    }
    return true;
}


int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cout << fixed; cout.precision(8);

    for(int i=0; i<9; i++) cin >> grid[i];

    double ans = 0;
    do {
        ans += check();
    } while(next_permutation(all(order)));
    cout << ans / MAX << endl;

    return 0;
}