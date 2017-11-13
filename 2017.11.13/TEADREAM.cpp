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

long long ansk, ansm, n, d;

long long solve(long long n, long long u) {
    if ((n - d) % u != 0) return 0;
    return solve((n - d) / u, u) + 1;
}

int main() {
    IO;
    //freopen("TEADREAM.inp","r",stdin);
    //freopen("TEADREAM.out","w",stdout);
    read(n);read(d);
    ansk = 2;
    ansm = 0;
    FOR(i, 1, sqrt(n - d)) if ((n - d) % i == 0) {
        long long m;
        if (i != 1 && i > d) {
            m = solve(n, i);
            if (m > ansm || (m == ansm && i < ansk)) {
                ansm = m;
                ansk = i;
            }
        }
        if ((n - d) / i <= d) continue;
        m = solve(n, (n - d)/ i);
        if (m > ansm || (m == ansm && ((n - d) / i) < ansk)) {
            ansm = m;
            ansk = (n - d) / i;
        }
    }
    write(ansk);putchar(' ');writeln(ansm);
}
