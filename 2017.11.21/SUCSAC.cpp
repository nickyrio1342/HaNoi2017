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

int a[5][7], p[5];
vector<int> e[7];
const int c[7] = {0, 1, 6, 2, 5, 3, 4};
int main() {
    IO;
    freopen("SUCSAC.inp","r",stdin);
    freopen("SUCSAC.out","w",stdout);
    FOR(i, 1, 4) FOR(j, 1, 6) read(a[i][c[j]]);
    int ans = -1, all =  0;
    FOR(i, 1, 4) FOR(j, 1, 6) all += a[i][j];
    FOR(i, 1, 4) p[i] = i;
    do {
    FOR(i11, 1, 6)
        FOR(i12, 1, 6) if (i12 != i11 && i12 + i11 != 7)
            FOR(i21, 1, 6) if (a[p[1]][i12] == a[p[2]][i21])
                FOR(i22, 1, 6) if (i22 != i21 && i22 + i21 != 7)
                    FOR(i31, 1, 6) if (a[p[2]][i22] == a[p[3]][i31])
                        FOR(i32, 1, 6) if (i32 != i31 && i32 + i31 != 7)
                            FOR(i41, 1, 6) if (a[p[3]][i32] == a[p[4]][i41])
                                FOR(i42, 1, 6) if (i42 != i41 && i42 + i41 != 7 && a[p[4]][i42] == a[p[1]][i11]) {
                                    int sum = a[p[1]][i11] + a[p[1]][i12] + a[p[2]][i21] + a[p[2]][i22] + a[p[3]][i31] + a[p[3]][i32] + a[p[4]][i41] + a[p[4]][i42];
                                    ans = max(ans, all - sum);
                                }
    } while (next_permutation(p + 1, p + 5));
    writeln(ans);
}
