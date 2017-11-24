#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 51000
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

set<pp> e[N];
int p[N], a[N], add[N], cnt, fr[N];

void dfs(int u) {
    int bef = -1, bef_v;
    for (pp t : e[u]) {
        int v = t.second;
        int c = t.first;
        e[v].erase(pp(c, u));
        a[v] = c;
        p[v] = u;
        if (a[v] == a[u]) {
            add[1]++;
            add[u]--;
            add[v]++;
        }
        if (bef == c) {
            fr[v] = false;
            if (fr[bef_v]) add[bef_v]++;
            add[v]++;
        }
        dfs(v);
        bef_v = v;
        bef = c;
    }
}

void dfs2(int u) {
    if (add[u] == 0) cnt++;
    for (pp t : e[u]) {
        int v = t.second;
        add[v] += add[u];
        dfs2(v);
    }
}

int main() {
    IO;
    int n, u, v, c;
    read(n);
    FOR(i, 1, n - 1) {
        read(u);read(v);read(c);
        e[u].insert(pp(c, v));
        e[v].insert(pp(c, u));
    }
    p[1] = -1;
    memset(fr, true, sizeof fr);
    dfs(1);
  //  FOR(i, 1, n) { write(add[i]); putchar(' ');}//return 0;
    cnt = 0;
    dfs2(1);
    //FOR(i, 1, n) { write(add[i]); putchar(' ');} return 0;
    writeln(cnt);
    FOR(i, 1, n) if (add[i] == 0) writeln(i);
}
