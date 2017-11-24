#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 1111
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

struct HopcroftKarp {
    int n;
    int d[N], match[N];
    vector<int> e[N];
    int NIL = 0;
    queue<int> q;

    void reset(int n) {
        this -> n = n;
        FOR(i, 1, n) match[i] = 0;
        FOR(i, 1, n) e[i].clear();
    }

    void addEdge(int u, int v) {
        e[u].push_back(v);
        e[v].push_back(u);
    }

    int getMaxMatching() {
        int matching = 0;
        while (bfs()) {
            FOR(i, 1, n) {
                if (match[i] == NIL && dfs(i)) {
                    matching++;
                }
            }
        }
        return matching;
    }

private:
    const int inf = 1e9;
    bool bfs() {
        FOR(i, 1, n) {
            if (match[i] == NIL) {
                d[i] = 0;
                q.push(i);
            } else d[i] = inf;
        }
        d[NIL] = inf;
        while (!q.empty()) {
            int u = q.front();q.pop();
            for (int v : e[u]) {
                if (d[match[v]] == inf) {
                    d[match[v]] = d[u] + 1;
                    q.push(match[v]);
                }
            }
        }
        return d[NIL] != inf;
    }

    bool dfs(int u) {
        if (u != NIL) {
            for (int v : e[u]) {
                if (d[match[v]] == d[u] + 1) {
                    if (dfs(match[v])) {
                        match[u] = v;
                        match[v] = u;
                        return true;
                    }
                }
            }
            return false;
        }
        return true;
    }
}HK;

struct Graph {
    vector<int> e[N], newE[N];
    int num[N], low[N], mark[N];
    int n, component, cnt;
    stack<int> st;
    void reset(int n) {
        this -> n = n;
        FOR(i, 1, n) e[i].clear();
    }

    void addEdge(int u, int v) {
        e[u].push_back(v);
    }

    void dfs(int u) {
        num[u] = low[u] = ++cnt;
        st.push(u);
        for (int v : e[u]) {
            if (mark[v] != 0) continue;
            if (num[v] == 0) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else low[u] = min(low[u], num[v]);
        }
        if (low[u] == num[u]) {
            int v;component++;
            do {
                v = st.top();st.pop();
                mark[v] = component;
            } while (u != v);
        }
    }

    void Tarjan() {
        FOR(i, 1, n) mark[i] = num[i] = 0;
        cnt = component = 0;
        FOR(i, 1, n) if (num[i] == 0) dfs(i);
    }
    bool fr[N];

    void dfs2(int u) {
        fr[u] = false;
        for (int v : newE[u]) {
            if (fr[v]) {
                dfs2(v);
            }
        }
    }

    void CreateNewGraph() {
        FOR(i, 1, component) newE[i].clear();
        FOR(u, 1, n) {
            for (int v : e[u]) {
                if (mark[u] != mark[v]) {
                    newE[mark[u]].push_back(mark[v]);
                }
            }
        }
        HK.reset(component);
        FOR(u, 1, component) {
            FOR(i, 1, component) fr[i] = true;
            dfs2(u);
            FOR(i, 1, component) if (i != u && !fr[i]) {
                HK.addEdge(u, i + component);
            }
        }
    }
}G1;
int n, m, u, v;
void solve() {
    read(n);read(m);
    G1.reset(n);
    REP(i, m) {
        read(u);read(v);
        G1.addEdge(u, v);
    }
    G1.Tarjan();
    G1.CreateNewGraph();
    writeln(HK.n - HK.getMaxMatching());
}
int main() {
    IO;
    int test;
    read(test);
    FOR(i, 1, test) {
        printf("Case %d: ", i);
        solve();
        putchar('\n');
    }
}
