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

int n, w1, w2, h1, h2;

void solve() {
    int ans = 1;
    //Find k :
       // + w1 <= k * x <= w2
       // + h1 <= k * y <= h2
    FOR(i, 1, sqrt(w2)) {
        //Case k = i and x = w2 / i
        int k = i, x = w2 / i;
        if (1ll * x * k >= w1) {
            int y = h2 / k;
            if (1ll * y * k >= h1) {
                ans = max(ans, k);
            }
        }
        //Case k = w2 / i and x = i
        k = w2 / i; x = i;
        if (1ll * x * k >= w1) {
            int y = h2 / k;
            if (1ll * y * k >= h1) {
                ans = max(ans, k);
            }
        }
    }
    FOR(i, 1, sqrt(h2)) {
        //Case k = i and y = h2 / i
        int k = i, y = h2 / i;
        if (1ll * y * k >= h1) {
            int x = w2 / k;
            if (1ll * x * k >= w1) {
                ans = max(ans, k);
            }
        }
        //Case k = h2 / i and y = i
        k = h2 / i; y = i;
        if (1ll * y * k >= h1) {
            int x = w2 / k;
            if (1ll * x * k >= w1) {
                ans = max(ans, k);
            }
        }
    }
    writeln(ans);
}
int main() {
    IO;
    freopen("TEACAREER.inp","r",stdin);
    freopen("TEACAREER.out","w",stdout);
    read(n);
    REP(i, n) {
        read(w1);read(w2);read(h1);read(h2);
        solve();
    }
}
