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

struct edge {
    int u, v;
    long long cap, flow;
};
struct Dinic {
    vector<int> ptr;
    vector<long long> d;
    vector<edge> e;
    vector<vector<int> > g;
    queue<int> q;
    int n, s, t;

    void reset(int n) {
        this -> n = n;
        ptr.clear(); d.clear(); g.clear(); e.clear();
        ptr.resize(n); d.resize(n); g.resize(n);
    }

    void addEdge(int u, int v, long long cap) {
        edge ee = {u, v, cap, 0};
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
            while (long long x = dfs(s, 1e18)) {
                flow += x;
            }
        }
        return flow;
    }
private:
    bool bfs() {
        REP(i, n) ptr[i] = 0;
        REP(i, n) d[i] = -1;
        d[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int id : g[u]) if (e[id].flow < e[id].cap) {
                int v = e[id].v;
                if (d[v] == -1) {
                    d[v] = d[u] + 1;
                    q.push(v);
                }
            }
        }
        return d[t] != -1;
    }

    long long dfs(int u, long long flow) {
        if (u == t || flow == 0) return flow;
        for (; ptr[u] < (int) g[u].size(); ++ptr[u]) {
            int id = g[u][ptr[u]];
            int v = e[id].v;
            if (d[v] == d[u] + 1 && e[id].flow < e[id].cap) {
                if (long long x = dfs(v, min(flow, e[id].cap - e[id].flow))) {
                    e[id].flow += x;
                    e[id^1].flow -= x;
                    return x;
                }
            }
        }
        return 0;
    }

}D;

int n, a[N];

int main() {
    IO;
    read(n);
    D.reset(n + 2);
    long long maxc = 0;
    FOR(i, 1, n) {
        read(a[i]);
        if (a[i] > 0) maxc += a[i];
    }
    FOR(i, 1, n) {
        if (a[i] >= 0) D.addEdge(0, i, a[i]);
        else D.addEdge(i, n + 1, -a[i]);
    }
    FOR(i, 1, n) {
        for (int j = i + i; j <= n; j += i) D.addEdge(j, i, maxc);
    }
    long long tmp = D.getMaxFlow(0, n + 1);
    writeln(maxc - tmp);
}
