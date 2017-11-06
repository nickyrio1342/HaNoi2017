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

int n, x;
vector<int> e[N];
int nxt[N], d[N], b[N][30], LOG, p[N];
bool fr[N];

void dfs(int u) {
    if (u == 1) return;
    for (int v : e[u]) {
        p[v] = u;
        d[v] = d[u] + 1;
        dfs(v);
    }
}

int go(int u) {
    if (!fr[u]) return 0;
    fr[u] = false;
    return go(nxt[u]) + 1;
}

void buildLCA() {
    FOR(i, 0, n + 1) if (p[i] == -1) p[i] = n + 1;
    FOR(i, 0, n + 1) b[i][0] = p[i];
    LOG = log2(n + 10);
    FOR(j, 1, LOG) FOR(i, 0, n + 1)
        b[i][j] = b[b[i][j - 1]][j - 1];
}

void Up(int &u, int level) {
    FORD(i, LOG, 0) if (bit(level, i)) {
        u = b[u][i];
    }
}

int lca(int u, int v) {
    if (d[u] > d[v]) Up(u, d[u] - d[v]);
    if (d[u] < d[v]) Up(v, d[v] - d[u]);
    if (u == v) return u;
    int res;
    FORD(i, LOG, 0) if (b[u][i] != b[v][i]) {
        u = b[u][i];
        v = b[v][i];
    } else res = b[u][i];
    return res;
}

int main() {
    IO;
    freopen("LINKLIST.inp","r",stdin);
    freopen("LINKLIST.out","w",stdout);
    read(n);
    REP(i, n) {
        read(x);
        e[x + 1].push_back(i + 1);
        nxt[i + 1] = x + 1;
    }
    FOR(i, 0, n) d[i] = -1;
    memset(p, -1, sizeof p);
    d[0] = 0;
    dfs(0);
    memset(fr, true, sizeof fr);
    buildLCA();
    int ans = -1;
    if (d[1] == -1) {
        int dis1 = go(1);
        int ans = 0;
        FOR(i, 0, n) ans = max(ans, d[i]);
        writeln(dis1 + ans);
        return 0;
    }
    ans = 0;
    FOR(i, 0, n) {
        if (d[i] != -1) {
            int par = lca(1, i);
            ans = max(ans, d[1] + d[i] - d[par]);
        }
    }
    writeln(ans);
}
