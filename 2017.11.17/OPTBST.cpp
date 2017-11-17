#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 2222
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

int n, pos[N][N], c[N];
long long dp[N][N], s[N];
int main() {
    IO;
    freopen("OPTBST.inp","r",stdin);
    freopen("OPTBST.out","w",stdout);
    read(n);
    FOR(i, 1, n) read(c[i]);
    s[0] = 0;
    FOR(i, 1, n) s[i] = s[i - 1] + c[i];
    FOR(i, 1, n) {
        dp[i][i] = c[i];
        dp[i][i - 1] = 0;
        pos[i][i] = i;
        FOR(j, i + 1, n) dp[i][j] = 1e18;
    }
    FOR(len, 2, n) {
        FOR(i, 1, n - len + 1) {
            int j = i + len - 1;
            long long best = 1e18;
            FOR(k, pos[i][j - 1], pos[i + 1][j]) {
                if (best > dp[i][k - 1] + dp[k + 1][j] + s[j] - s[i - 1]) {
                    best = dp[i][k - 1] + dp[k + 1][j] + s[j] - s[i - 1];
                    pos[i][j] = k;
                }
            }
            dp[i][j] = best;
        }
    }
    writeln(dp[1][n]);
}
