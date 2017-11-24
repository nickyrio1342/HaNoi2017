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

int main() {
    IO;
    freopen("ANTPATH.inp","r",stdin);
    freopen("ANTPATH.out","w",stdout);
    int a1, a2, a3, b1, b2, b3;
    read(a1);read(a2);read(a3);read(b1);read(b2);read(b3);
    long long ans = 0;
    // Case 3 - 3
    int k = min(a3, b3);
    ans += 9ll * k;
    a3 -= k; b3 -= k;
    // Case 3 - (1, 2)
    k = min(a3, min(b1, b2));
    ans += 9ll * k;
    a3 -= k; b1 -= k; b2 -= k;
    k = min(b3, min(a1, a2));
    ans += 9ll * k;
    b3 -= k; a1 -= k; a2 -= k;
     //Case (3, 1) - (2, 2)
    k = min(min(a3, a1), (b2 / 2));
    ans += 12ll * k;
    a3 -= k; a1 -= k; b2 -= 2 * k;
    k = min(min(b3, b1), a2 / 2);
    ans += 12ll * k;
    b3 -= k; b1 -= k; a2 -= 2 * k;
    // Case 3 - 2
    k = min(a3 / 2, b2 / 3);
    ans += 24ll * k;
    a3 -= 2 * k; b2 -= 3 * k;
    k = min(b3 / 2, a2 / 3);
    ans += 24ll * k;
    b3 -= 2 * k; a2 -= 3 * k;
    // Case 3 - (1, 1, 1)
    k = min(a3, b1 / 3);
    ans += 9ll * k;
    a3 -= k; b1 -= 3 * k;
    k = min(b3, a1 / 3);
    ans += 9ll * k;
    b3 -= k; a1 -= 3 * k;
    // Case 2 - 2
    k = min(a2, b2);
    ans += 4ll * k;
    a2 -= k; b2 -= k;
    // Case 2 - (1, 1)
    k = min(a2, b1 / 2);
    ans += 4ll * k;
    a2 -= k; b1 -= 2 * k;
    k = min(b2, a1 / 2);
    ans += 4ll * k;
    b2 -= k; a1 -= 2 * k;
    //Case 1 - 1
    ans += a1;
    writeln(ans);
}
