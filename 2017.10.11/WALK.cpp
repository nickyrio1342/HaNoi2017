#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 1001000
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
    vector<long long> d;
    vector<int> bef;
    vector<vector<int> > g;
    vector<edge> e;
    priority_queue<pp> heap;
    vector<int> res;
    int n, s, t;
    vector<bool> fr;
    void reset(int n) {
        this -> n = n;
        d.clear();
        g.clear();
        bef.clear();
        e.clear();
        d.resize(n);
        bef.resize(n);
        g.resize(n);
        fr.clear();
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
        fr.resize(e.size());
        REP(i, e.size()) fr[i] = true;
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
            int v = t;
            while (s != v) {
                int id = bef[v];
                e[id].flow++;
                e[id^1].flow--;
                v = e[id].u;
            }
            Cost += d[t];
        }
        return Cost;
    }

    void traceFlow(int u, int t) {
        res.push_back(u);
        int cnt = 0;
        for (int id : g[u]) if (e[id].flow > 0 && fr[id]) {
            fr[id] = false;
            traceFlow(e[id].v, t);
            cnt++;
            if (cnt == 1 && s != u) break;
            if (s == u && cnt == 1) {
                for (int x : res) {
                    write(x + 1);putchar(' ');
                }
                res.clear();res.push_back(s);
            }

        }
        if (s == u) {
            res.pop_back();
            while (!res.empty()) {
                write(res.back() + 1);putchar(' ');
                res.pop_back();
            }
        }
    }
}MCF;
int n, m, u, v, c, s, t;
int main() {
    IO;
 //   freopen("WALK.inp","r",stdin);
 //   freopen("WALK.out","w",stdout);
    read(n);read(m);read(s);read(t);
    MCF.reset(n);
    REP(i, m) {
        read(u);read(v);read(c);
        u--;v--;
        MCF.addEdge(u, v, 1, c);
        MCF.addEdge(v, u, 1, c);
    }
    writeln(MCF.getMinCost(s - 1, t - 1));
    MCF.res.clear();
    //MCF.traceFlow(s - 1, t - 1);
}
