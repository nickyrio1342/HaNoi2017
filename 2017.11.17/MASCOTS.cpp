#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 3030
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


const long long MOD = 1e9 + 7;
int n, m, u, v, p, L, R, D, U;
bool fr[N][N];
long long gt[N * N], need, dp[N][N];
bool used[N][N];

long long cal(int x2, int y2) {
    if (x2 == D - U + 1 && y2 == R - L + 1) return 1;
    if (used[x2][y2]) return dp[x2][y2];
    used[x2][y2] = true;
    long long res = 0;

    if (y2 > R - L + 1) res = (res + cal(x2, y2 - 1) * gt[x2] % MOD) % MOD;
    if (x2 > D - U + 1) res = (res + cal(x2 - 1, y2) * gt[y2] % MOD) % MOD;
    dp[x2][y2] = res;
    return res;

}
long long f[N][N];

void init() {
    FOR(i, 0, max(m, n)) f[0][i] = 1;
    FOR(i, 1, max(m, n)) {
        f[i][i] = 1;
        FOR(j, i + 1, max(m, n)) f[i][j] = (f[i - 1][j - 1] + f[i][j - 1]) % MOD;
    }
}
long long row[N], col[N];

int main() {
    IO;
    read(m);read(n);
    L = 1e9, R = -1e9, U = 1e9, D = -1e9;
    FOR(i, 1, m) FOR(j, 1, n) fr[i][j] = true;
    read(p);
    gt[0] = 1;
    FOR(i, 1, m * n) gt[i] = gt[i - 1] * 1ll * i % MOD;
    REP(i, p) {
        read(u);read(v);
        fr[u][v] = false;
        L = min(L, v);
        R = max(R, v);
        U = min(U, u);
        D = max(D, u);
    }
    need = gt[(D - U + 1) * (R - L + 1) - p];
    need = cal(m, n) * need % MOD;
    m = m - D + U;
    n = n - R + L;
    init();
    FOR(i, 1, m) row[i] = f[i - 1][m - 1];
    FOR(i, 1, n) col[i] = f[i - 1][n - 1];
    long long res = row[U] * col[L] % MOD;
    res = res * need % MOD;
    writeln(res);
}
