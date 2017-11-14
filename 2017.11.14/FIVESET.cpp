#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 101000
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

int n;
long long w1, w2, a[N], f[N][6];

int main() {
    IO;
    freopen("FIVESET.inp","r",stdin);
    freopen("FIVESET.out","w",stdout);
    read(n);read(w1);read(w2);
    FOR(i, 1, n) read(a[i]);
    FOR(i, 0, n) FOR(j, 1, 5) f[i][j] = -1e18;
    FOR(i, 0, n) f[i][0] = 0;
    FOR(j, 1, 5) FOR(i, 1, n) {
        long long c;
        if (j == 1 || j == 5) c = a[i] * w1;
        if (j == 2 || j == 4) c = a[i] * w2;
        if (j == 3) c = a[i];
        f[i][j] = max(f[i - 1][j], f[i - 1][j - 1] + c);
    }
    writeln(f[n][5]);
}
