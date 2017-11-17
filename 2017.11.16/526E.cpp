//http://codeforces.com/contest/526/problem/E
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 2001000
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

int n, level[N], dd[N], END[N], f[N];

long long m, a[N];

int cal(int u) {
    int cnt = 0;
    int t = u;
    while (u - t < n) {
        cnt++;
        u = f[u] + 1;
    }
    return cnt;
}
void solve() {
    read(m);
    long long sum = 0;
    int start = 1;
    FOR(last, 1, n * 2 - 1) {
        sum += a[last];
        while (sum > m) {
            sum -= a[start];
            f[start] = last - 1;
            start++;
        }
        int len = last - start + 1;
        f[start] = last;
    }
    for (; start < 2 * n; ++start) f[start] = 2 * n - 1;
    start = 1;
    int need = n;
    FOR(i, 2, n) {
        if (f[start] - start > f[i] - i) start = i;
    }
    FOR(i, start, f[start] + 1) {
        need = min(need, cal(((i - 1) % n) + 1));
    }
    writeln(need);
}
int q;
int main() {
    IO;
    read(n);read(q);
    FOR(i, 1, n) read(a[i]);
    FOR(i, 1, n) a[i + n] = a[i];
    while (q--) {
        solve();
    }
}

