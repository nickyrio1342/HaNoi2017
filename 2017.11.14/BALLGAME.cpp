#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 1411
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
        write(-x);return;
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

int n, m, x[N], y[N];

void solve1() {
    read(m);
    REP(i, m) {
        read(x[i]);read(y[i]);
    }
    sort(x, x + m);
    sort(y, y + m);
    int midx = x[m / 2];
    int midy = y[m / 2];
    long long ans = 0;
    REP(i, m) {
        ans += abs(x[i] - midx);
        ans += abs(y[i] - midy);
    }
    writeln(ans);
}

long long d[444][444], f[444][444];
bool a[444][444];
queue<pp> q;
const int dd[4] = {0, 1, 0, -1};
const int cc[4] = {1, 0, -1, 0};

bool inside(int i, int j) {
    if (i >= 0 && i <= 221 && j >= 0 && j <= 221) return true;
    return false;
}
void bfs(int ii, int jj) {
    REP(i, 222) REP(j, 222) d[i][j] = -1;
    d[ii][jj] = 0;
    q.push(pp(ii, jj));
    while (!q.empty()) {
        pp u = q.front();
        q.pop();
        REP(i, 4) {
            pp v = pp(u.first + dd[i], u.second + cc[i]);
            if (inside(v.first, v.second) && d[v.first][v.second] == -1 && a[v.first][v.second]) {
                d[v.first][v.second] = d[u.first][u.second] + 1;
                q.push(v);
            }
        }
    }
}
int offset = 111;

void solve2() {
    int xx, yy;
    memset(a, true, sizeof a);
    REP(i, n) {
        read(xx);read(yy);
        a[xx + offset][yy + offset] = false;
    }
    read(m);
    REP(i, m) {
        read(x[i]);read(y[i]);
    }
    memset(f, 255, sizeof f);
    REP(i, m) {
        bfs(x[i] + offset, y[i] + offset);
        REP(j, 222) REP(k, 222) if (a[j][k]) {
            if (d[j][k] != -1) {
                if (f[j][k] == -1) f[j][k] = d[j][k];
                else f[j][k] += d[j][k];
            }
            else a[j][k] = false;
        }
    }
    long long ans = 1e18;
    REP(i, 222) REP(j, 222) if (f[i][j] >= 0 && a[i][j] && ans > f[i][j]) {
        ans = f[i][j];
    }
    if (ans == 1e18) ans = -1;
    writeln(ans);
}

int main() {
    IO;
    freopen("BALLGAME.inp","r",stdin);
    freopen("BALLGAME.out","w",stdout);
    read(n);
    if (n == 0) solve1();
    else solve2();
}
