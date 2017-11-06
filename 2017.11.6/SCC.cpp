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
    while (!isdigit(c = getchar()));
    x = 0;
    do {
        x = x * 10 + c - '0';
    } while (isdigit(c = getchar()));
}
template<typename T> inline void write(T x) {
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

int num[N], low[N], dd[N], n, m, k;
vector<int> e[N];
int cnt, nScc;
stack<int> st;

void dfs(int u, int p) {
    st.push(u);
    num[u] = low[u] = ++cnt;
    for (int v : e[u]) {
        if (dd[v] == 0) {
            if (num[v] == 0) {
                dfs(v, u);
                low[u] = min(low[u], low[v]);
            } else low[u] = min(low[u], num[v]);
        }
    }
    if (low[u] == num[u]) {
        int v;nScc++;
        do {
            v = st.top();
            st.pop();
            dd[v] = nScc;
        } while (u != v);
    }
}

int main() {
    freopen("SCC.inp","r",stdin);
    freopen("SCC.out","w",stdout);
    IO;
    int u, v;
    read(n); read(m); read(k);
    REP(i, m) {
        read(u); read(v);
        e[u].push_back(v);
    }
    FOR(i, 1, n) dd[i] = num[i] = 0;
    cnt = 0;
    nScc = 0;
    FOR(i, 1, n) {
        if (num[i] == 0) dfs(i, -1);
    }
    writeln(nScc);
    while (k--) {
        read(u); read(v);
        if (dd[u] == dd[v]) {
            writeln(nScc);
            continue;
        }
        e[u].push_back(v);
        FOR(i, 1, n) num[i] = dd[i] = 0;
        cnt = nScc = 0;
        FOR(i, 1, n) if (num[i] == 0) dfs(i, -1);
        writeln(nScc);
    }
}
