#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; ++i)
#define FORD(i, a, b) for (int i = a; i>=b; --i)
#define REP(i, a) for (int i = 0; i<a; ++i)
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
        write(-x);
        return;
    }
    if (x < 10) putchar(char(x + 48));
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


int n, m, cnt, num[N], low[N];
long long nChild[N];
vector<int> e[N];
long long ans = 0;
void dfs(int u, int p) {
    num[u] = low[u] = ++cnt;
    nChild[u] = 1;
    for (int v : e[u]) if (v != p) {
        if (num[v] == 0) {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] <= num[u]) {
                if (nChild[v] > 2) ans += (nChild[v] - 2) * (nChild[v] - 1) / 2;
            } else nChild[u] += nChild[v];
        } else low[u] = min(low[u], num[v]);
    }
}

int main() {
    
    freopen("addedge.inp","r",stdin);
    freopen("addedge.out","w",stdout);
    IO;
    int u, v;
    read(n); read(m);
    REP(i, m) {
        read(u); read(v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    cnt = 0;
    ans = 0;
    FOR(i, 1, n) num[i] = 0;
    FOR(i, 1, n) if (num[i] == 0) {
        dfs(i, -1);
        if (nChild[i] > 2) ans += (nChild[i] - 2) * (nChild[i] - 1) / 2;
    }
    write(ans);
}
