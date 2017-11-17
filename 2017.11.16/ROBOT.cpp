#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 1111
#define pp pair<int, int>
#define IO cin.tie(NULL);cout.tie(NULL);
#define bit(S, i) ((S >> i) & 1)
template<typename T> inline void read(T &x) {
    char c;
    bool neg = false;
    while (!isdigit(c = getchar()) && c != '-');
    x = 0;
    if (c == '-') {
        neg = true;
        c = getchar();
    }
    do {
        x = x * 10 + c - '0';
    } while (isdigit(c = getchar()));
    if (neg) x = -x;
}
template<typename T> inline void write(T x) {
    if (x < 0) {
        putchar('-');
        write(-x); return;
    }
    if (x < 10) {
        putchar(char(x + 48));
    }
    else {
        write(x/10);
        putchar(char(48 + x%10));
    }
}
template<typename T> inline void writeln(T x) {
    write(x);
    putchar('\n');
}
using namespace std;

struct data {
    int u, v, dir;
};
int d[N][N][4], a[N][N], c[N][N][4];
const int dd[4] = {0, 1, -1, 0};
const int cc[4] = {1, 0, 0, -1};
int n;
deque<data> q;
bool inside(int i, int j) {
    return i>=0 && i<n && j>=0 && j<n;
}
void bfs(int l1, int c1, int l2, int c2) {
    while (!q.empty()) q.pop_back();
    REP(i, n) REP(j, n) REP(t, 4) d[i][j][t] = 1e9;
    REP(i, 4) {
        d[l1][c1][i] = 0;
        q.push_back(data({l1, c1, i}));
    }
    while (!q.empty()) {
        data u = q.front();
        q.pop_front();
        REP(i, 4) {
            data v;
            v.u = u.u + dd[i];
            v.v = u.v + cc[i];
            v.dir = i;
            if (inside(v.u, v.v)) {
                int k = 0;
                if (a[v.u][v.v]) k++;
                int t = 1;
                if (i == u.dir) t = 0;
                if (d[v.u][v.v][i] <= d[u.u][u.v][u.dir] + t) continue;
                if (u.dir == i) {
                    d[v.u][v.v][i] = d[u.u][u.v][u.dir];
                    if (k == 1) continue;
                    q.push_front(v);
                }
                else {
                    d[v.u][v.v][i] = d[u.u][u.v][u.dir] + 1;
                    if (k == 1) continue;
                    q.push_back(v);
                }
            }
        }
    }
}
int l1, l2, c1, c2;
int main() {
    IO;
    //freopen("E:\\input.txt","r",stdin);
    //freopen("E:\\output.txt","w",stdout);
    freopen("ROBOT.inp","r",stdin);
    freopen("ROBOT.out","w",stdout);
    read(n);
    REP(i, n) REP(j, n) read(a[i][j]);
    read(l1);read(c1);read(l2);read(c2);
    l1--;c1--;l2--;c2--;
    bfs(l1, c1, l2, c2);
    int mn1 = d[l2][c2][3];
    REP(i, 3) mn1 = min(mn1, d[l2][c2][i]);
    write(mn1);putchar(' ');
    REP(i, n) REP(j, n) REP(t, 4) c[i][j][t] = d[i][j][t];
    bfs(l2, c2, l1, c1);
    int cnt = 0, cntt = 0;
    int mn = mn1;
    REP(i, n) REP(j, n) if (a[i][j]) cntt++;
    REP(i, n) REP(j, n) REP(k, 4) REP(t, 4) if (a[i][j]){

        if (k == 3 - t && c[i][j][k] + d[i][j][t] <= mn) {
            a[i][j] = 0;
            if (mn == c[i][j][k] + d[i][j][t]) {
                cnt++;continue;
            }
            mn = c[i][j][k] + d[i][j][t];
            cnt = 1;
        }
        if (k != 3 - t && c[i][j][k] + d[i][j][t] + 1 <= mn) {
            a[i][j] = 0;
            if (mn == c[i][j][k] + d[i][j][t] + 1) {
                cnt++;continue;
            }
            mn = c[i][j][k] + d[i][j][t] + 1;
            cnt = 1;
        }
    }
    if (mn == mn1) {
        cnt = cntt;
    }
    write(mn);putchar(' ');
    writeln(cnt);
    //cout<<cnt;
}
