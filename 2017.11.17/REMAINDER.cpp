#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 1001000
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

long long x, MOD, n;

struct matrix {
    long long t[2][2];

    void reset(long long k) {
        if (k == 0) {
            REP(i, 2) REP(j, 2) t[i][j] = 0;
            return;
        }
        long long p = 1;
        while (k) {
            p = p * 10 % MOD;
            k /= 10;
        }
        t[0][0] = p;
        t[0][1] = t[1][1] = 1;
        t[1][0] = 0;
    }
}c;

long long mul(long long a, long long b) {
    a %= MOD;
    b %= MOD;
    long long q = (long double)a * b / MOD;

    long long r = (a * b - q * MOD) % MOD;
    if (r < 0) r += MOD;
    return r;
}

matrix operator* (matrix a, matrix b) {
    matrix c;c.reset(0);
    REP(i, 2) REP(j, 2) REP(k, 2) {
        c.t[i][j] += mul(a.t[i][k], b.t[k][j]);
        if (c.t[i][j] >= MOD) c.t[i][j] -= MOD;
    }
    return c;
}

matrix POW(const matrix &a, long long k) {
    if (k == 1) return a;
    matrix tmp = POW(a, k >> 1);
    tmp = tmp * tmp;
    if (k % 2) tmp = tmp * a;
    return tmp;
}

int main() {
    IO;
    freopen("REMAINDER.inp","r",stdin);
    freopen("REMAINDER.out","w",stdout);
    int test;
    read(test);
    while (test--) {
        read(x);read(n);read(MOD);
        matrix base;
        base.reset(x);
        if (n == 1) {
            writeln(x % MOD);
            continue;
        }
        matrix res = POW(base, n - 1);
        long long ans = mul(res.t[0][0], x % MOD) + mul(res.t[0][1], x % MOD);
        if (ans >= MOD) ans -= MOD;
        writeln(ans);
    }
}
