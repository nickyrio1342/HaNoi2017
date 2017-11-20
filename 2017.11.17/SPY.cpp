#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define M 501000
#define N 2020
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

int n, m, x;
vector<int> a[N], b[N];
bitset<M> bsa[N], bsb[N], now;

void dfsa(int u, int p) {
    for (int v : a[u]) if (v != p) {
        bsa[v] |= bsa[u];
        dfsa(v, u);
    }
}

void dfsb(int u, int p) {
    for (int v : b[u]) if (v != p) {
        bsb[v] |= bsb[u];
        dfsb(v, u);
    }
}

int main() {
    IO;
    int ra, rb;

    read(n);read(m);
    FOR(i, 1, n) {
        read(x);
        if (x == 0) ra = i;
        else a[x].push_back(i);
        read(x);
        if (x == 0) rb = i;
        else b[x].push_back(i);
    }
    REP(i, m) {
        read(x);
        bsa[x].set(i);
        read(x);
        bsb[x].set(i);
    }
    dfsa(ra, -1);
    dfsb(rb, -1);
    FOR(i, 1, n) {
        now = bsa[i] & bsb[i];
        writeln(now.count());
    }
}
