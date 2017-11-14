/*
    + Sử dụng QHĐ kết hợp đảo nhãn
*/
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 5111
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
long long t, a[N], dp[N][N];

int main() {
    IO;
    freopen("VQTT.inp","r",stdin);
    freopen("VQTT.out","w",stdout);
    read(n);read(t);
    FOR(i, 1, n) read(a[i]);
    memset(dp, 255, sizeof dp);
    dp[0][0] = 0;
    FOR(i, 1, n) FOR(j, 1, i) {
        if (dp[i - 1][j - 1] >= 0) {
            dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + a[i]);
        }
        if (i != n && dp[i - 1][j] >= t) {
            dp[i][j] = max(dp[i][j], dp[i - 1][j] - t);
        }
    }
    int ans = -1;
    FORD(i, n, 1) if (dp[n][i] >= 0) ans = i;
    writeln(ans);
}
