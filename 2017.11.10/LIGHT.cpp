#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 3030
#define pp pair<long long, int>
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

struct edge {
    int u, v, cap, flow, cost;
};

struct MinCostFlow {
    vector<int> bef;
    vector<long long> d;
    vector<vector<int> > g;
    vector<edge> e;
    priority_queue<pp> heap;
    int n, s, t;

    void reset(int n) {
        bef.clear();
        d.clear();
        g.clear();
        e.clear();
        this -> n = n;
        bef.resize(n);
        d.resize(n);
        g.resize(n);
    }

    void addEdge(int u, int v, int cap, int cost) {
        edge ee = {u, v, cap, 0, cost};
        g[u].push_back(e.size());
        e.push_back(ee);
        ee = {v, u, 0, 0, -cost};
        g[v].push_back(e.size());
        e.push_back(ee);
    }
    const long long inf = 1e18;
    long long getMinCost(int s, int t) {
        this -> s = s;
        this -> t = t;
        long long Cost = 0;
        int test = 2;
        while (test--) {
            while (!heap.empty()) heap.pop();
            REP(i, n) d[i] = inf;
            d[s] = 0;
            heap.push(pp(0, s));
            while (!heap.empty()) {
                int u = heap.top().second;
                long long dist = -heap.top().first;
                heap.pop();
                if (dist != d[u]) continue;
                if (u == t) break;
                for (int id : g[u]) {
                    int v = e[id].v;
                    int c = e[id].cost;
                    if (d[v] > d[u] + c && e[id].flow < e[id].cap) {
                        d[v] = d[u] + c;
                        bef[v] = id;
                        heap.push(pp(-d[v], v));
                    }
                }
            }
            if (d[t] == inf) {
                writeln(-1);
                exit(0);
            }
            Cost += d[t];
            int v = t;
            while (v != s) {
                int id = bef[v];
                edge tmp = e[id];
                e[id].flow++;
                e[id ^ 1].flow--;
                v = e[id].u;
            }
        }
        return Cost;
    }
}MCF;
int p[N], a[N], b[N];
int main() {
    IO;
    freopen("LIGHT.inp","r",stdin);
    freopen("LIGHT.out","w",stdout);
    int n, t, x, h;
    read(n);read(t);
    MCF.reset(2 * n + 2);
    FOR(i, 1, n) {
        MCF.addEdge(i, i + n, 1, 0);
    }
    FOR(i, 1, n) {
        read(x);read(h);read(p[i]);
        a[i] = x - h;
        b[i] = x + h;
        if (a[i] <= 0) MCF.addEdge(0, i, 1, p[i]);
        if (b[i] >= t) MCF.addEdge(i + n, 2 * n + 1, 1, 0);
    }
    FOR(i, 1, n) FOR(j, 1, n) if (i != j){
        if (a[i] <= a[j] && a[j] <= b[i]) MCF.addEdge(i + n, j, 1, p[j]);
    }
    writeln(MCF.getMinCost(0, 2 * n + 1));
}
