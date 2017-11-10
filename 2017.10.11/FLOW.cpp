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

int n, m, s, t;

struct edge {
    int u, v;
    long long cap, flow;
};

struct Dinic {
    int n, s, t;
    vector<int> ptr;
    vector<long long> d;
    queue<int> q;
    vector<vector<int> > g;
    vector<edge> e;


    void reset(int n) {
        this -> n = n;
        g.clear();
        d.clear();
        e.clear();
        ptr.clear();
        g.resize(n);
        d.resize(n);
        ptr.resize(n);
    }
    void addEdge(int u, int v, long long c) {
        edge ee = {u, v, c, 0};
        g[u].push_back(e.size());
        e.push_back(ee);
        ee = {v, u, 0, 0};
        g[v].push_back(e.size());
        e.push_back(ee);
    }

    long long getMaxFlow(int s, int t) {
        this -> s = s;
        this -> t = t;
        long long flow = 0;
        while (bfs()) {
            REP(i, n) ptr[i] = 0;
            while (long long x = dfs(s, inf)) {
                flow += x;
            }
        }
        return flow;
    }

    void traceFlow() {
        for (edge x : e) if (x.cap > 0) {
            writeln(x.flow);
        }
    }
    const long long inf = 1e18;

private:
    bool bfs() {
        while (!q.empty()) q.pop();
        REP(i, n) d[i] = inf;
        d[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == t) return true;
            for (int id : g[u]) {
                int v = e[id].v;
                if (d[v] == inf && e[id].flow < e[id].cap) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
        return false;
    }

    long long dfs(int u, long long flow) {
        if (!flow) return 0;
        if (u == t) return flow;
        for(; ptr[u] < (int) g[u].size(); ++ptr[u]) {
            int id = g[u][ptr[u]];
            int v = e[id].v;
            if (d[v] == d[u] + 1) {
                if (long long x = dfs(v, min(flow, e[id].cap - e[id].flow))) {
                    e[id].flow += x;
                    e[id ^ 1].flow -= x;
                    return x;
                }
            }
        }
        return 0;
    }
}D;

int main() {
    IO;
    freopen("FLOW.inp","r",stdin);
    freopen("FLOW.out","w",stdout);
    read(n);read(m); read(s);read(t);
    s--;t--;
    D.reset(n);
    int u, v;
    long long c;
    REP(i, m) {
        read(u);read(v);read(c);
        u--;v--;
        D.addEdge(u, v, c);
    }
    writeln(D.getMaxFlow(s, t));
    D.traceFlow();
}
