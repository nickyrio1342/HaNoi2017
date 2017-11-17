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

struct edge {
    int u, v, cap, flow, cost;
};

struct MinCostFlow {
    vector<int> bef;
    vector<int>d;
    vector<vector<int> > g;
    vector<edge> e;
    priority_queue<pp> heap;
    int n;
    queue<int> q;
    void reset(int n) {
        bef.clear();d.clear();g.clear();e.clear();
        bef.resize(n);d.resize(n);g.resize(n);
        this -> n = n;
    }

    void addEdge(int u, int v, int cap, int cost) {
        edge ee = {u, v, cap, 0, cost};
        g[u].push_back(e.size());
        e.push_back(ee);
        g[v].push_back(e.size());
        ee = {v, u, 0, 0, -cost};
        e.push_back(ee);
    }

    long long getMinCost(int s, int t) {
        long long Cost = 0;
        while (true) {
            REP(i, n) {
                d[i] = 1e9;
            }
            d[s] = 0;
            while (!heap.empty()) heap.pop();
            heap.push(pp(0, s));
            while (!heap.empty()) {
                int u = heap.top().second;
                int dist = -heap.top().first;
                heap.pop();
                if (dist != d[u]) continue;
                if (u == t) break;
                for (int id : g[u]) if (e[id].flow < e[id].cap) {
                    int v = e[id].v;
                    int c = e[id].cost;
                    if (d[v] > d[u] + c) {
                        d[v] = d[u] + c;
                        bef[v] = id;
                        heap.push(pp(-d[v], v));
                    }
                }
            }
            if (d[t] == 1e9) break;
            int flow = 1e9;
            int v = t;
            while (v != s) {
                int id = bef[v];
                flow = min(flow, e[id].cap - e[id].flow);
                v = e[id].u;
            }
            v = t;
            while (v != s) {
                int id = bef[v];
                e[id].flow += flow;
                e[id ^ 1].flow -= flow;
                v = e[id].u;
            }
        }


        for (edge x : e) if (x.flow >= 0 && x.cost > 0 && x.u != 0 && x.v != n - 1) {
            Cost += 1ll * (x.flow + 1) * x.cost;
        }
        return Cost;
    }
}MCF;
int n, m, u, v, c;

int IN[N], OUT[N];

int main() {
    IO;
    freopen("DCPP.inp","r",stdin);
    freopen("DCPP.out","w",stdout);
    read(n);read(m);
    MCF.reset(n + 2);
    while (m--) {
        read(u);read(v);read(c);
        IN[v]++;
        OUT[u]++;
        MCF.addEdge(u, v, 1e9, c);
    }
    FOR(i, 1, n) {
        MCF.addEdge(0, i, IN[i], 0);
        MCF.addEdge(i, n + 1, OUT[i], 0);
    }
    writeln(MCF.getMinCost(0, n + 1));
}
