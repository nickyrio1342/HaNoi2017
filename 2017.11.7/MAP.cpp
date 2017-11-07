/*Để kiểm tra 1 điểm có thuộc trong 1 đa giác hay không, 
ta có thể kẻ 1 đường thẳng từ ngoài đến điểm đó, 
nếu nó cắt một số lẻ lần cạnh thì điểm đó thuộc đa giác
*/
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 1001
#define pp pair<int, int>
#define IO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define bit(S, i) ((S >> i) & 1)

using namespace std;

int n, w, h, u, v;
bool a[N][N];
vector<pp> e;
pp nxt[N][N];

bool inside(int u, int v) {
    return (u >= 0 && u <= w && v >= 0 && v <= h);
}
const int d[4] = {0, 1, 0, -1};
const int c[4] = {1, 0, -1, 0};

bool check(int ii, int jj) {
    int cnt1 = 0;
    REP(i, ii) if (nxt[i][jj] == pp(i,jj - 1) || nxt[i][jj - 1] == pp(i, jj)) cnt1++;
    return cnt1 % 2;

}
int main() {
   IO;
   freopen("MAP.inp","r",stdin);
   freopen("MAP.out","w",stdout);
   cin>>n>>w>>h;
   FOR(i, 0, w) FOR(j, 0, h) nxt[i][j] = pp(-2, -2);
   memset(a, false, sizeof a);
   REP(i, n + 1) {
        if (i != n) cin>>u>>v;
        else {
            u = e[0].first;
            v = e[0].second;
        }
        if (e.empty()) e.push_back(pp(u, v));
        pp t = e.back();
        if (t.first == u) {
            FORD(i, t.second - 1, v) {
                nxt[u][i] = e.back();
                a[u][i] = true;
                e.push_back(pp(u, i));
            }
            FOR(i, t.second + 1, v) {
                nxt[u][i] = e.back();
                a[u][i] = true;
                e.push_back(pp(u, i));
            }
        }
        if (t.second == v) {
            FORD(i, t.first - 1, u) {
                nxt[i][v] = e.back();
                a[i][v] = true;
                e.push_back(pp(i, v));
            }
            FOR(i, t.first + 1, u) {
                nxt[i][v] = e.back();
                a[i][v] = true;
                e.push_back(pp(i, v));
            }
        }
   }

    FORD(j, h, 1) {
        FOR(i, 1, w) {
            if (check(i, j)) putchar('#');
            else putchar('.');
        }
        putchar('\n');
    }
}
