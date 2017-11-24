#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 1001000
#define pp pair<int, int>
#define IO cin.tie(NULL);cout.tie(NULL);
#define bit(S, i) (((S) >> i) & 1)
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
int n, m, a[N];

bool ok(int mid) {
    long long ans = 0;
    FOR(i, 1, n) {
        if (a[i] > mid) ans += a[i] - mid;
        if (ans >= m) return true;
    }
    return false;
}
int main() {
    IO;
    
    freopen("BLADE.inp","r",stdin);
    freopen("BLADE.out","w",stdout);
    read(n); read(m);
    FOR(i, 1, n) read(a[i]);
    int l = 0;
    int r = *max_element(a + 1, a + n + 1);
    int cur = 0;
    
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (ok(mid)) {
            cur = mid;
            l = mid + 1;
        } else r = mid - 1;
    }
    writeln(cur);
}
