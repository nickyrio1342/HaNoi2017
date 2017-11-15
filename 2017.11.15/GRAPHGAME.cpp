#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 100100
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
int n, p, x, y, IN[N], OUT[N];
bool fr[N];
set<int> e[N];
int solve(int s) {
    FOR(i, 1, n) if (i != s && IN[i] < OUT[i]) {
        for (int v : e[i]) {
            if (*lower_bound(e[v].begin(), e[v].end(), i) != i) {
                return v;
            }
        }
    }
}
int main() {
    IO;
  freopen("GRAPHGAME.inp","r",stdin);
    freopen("GRAPHGAME.out","w",stdout);
    read(p);
    read(n);
    FOR(i, 1, n) {
        read(x);
        OUT[i] = x;
        while (x--) {
            read(y); e[i].insert(y);
            IN[y]++;
        }
    }
    memset(fr, true, sizeof fr);
    int t = solve(0);
    if (p == 2) {
        FOR(i, 1, n) {
            if (*e[i].lower_bound(t) == t) {
                OUT[i]--;
                e[i].erase(t);
            }
        }
        for (int x : e[t]) IN[x]--;
        int tt = solve(t);
        if (t > tt) swap(t, tt);
        printf("%d %d", t, tt);
    } else write(t);
}
