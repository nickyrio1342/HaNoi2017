#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 100100
#define pp pair<int, int>
#define IO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define bit(S, i) (((S) >> i) & 1)
using namespace std;
const int inf = 1e9;
int n, m, p[N], cost[N];
vector<pp> e[N];
int b[N][20], LOG, level[N];
int d[N][20];
struct edge {
    int u, v, c;
    bool operator < (const edge &a) {
        return c < a.c;
    }
}s[N];
void dfs(int u) {
    for (pp t : e[u]) {
        int v = t.first;
        int c = t.second;
        if (p[u] == v) continue;
        p[v] = u;
        cost[v] = c;
        level[v] = level[u] + 1;
        dfs(v);
    }
}

void BuildLCA() {
    p[1] = 0;
    FOR(i, 0, n) {
        b[i][0] = p[i];
        d[i][0] = cost[i];
    }
    LOG = log2(n);
    FOR(j, 1, LOG) FOR(i, 0, n) {
        b[i][j] = b[b[i][j - 1]][j - 1];
        d[i][j] = d[i][j - 1] + d[b[i][j - 1]][j - 1];
    }
}

int Up(int &u, int level) {
    int ans = 0;
    FORD(i, LOG, 0) if (bit(level, i)) {
        ans += d[u][i];
        u = b[u][i];
    }
    return ans;
}

int lca(int u, int v) {
    int ans = 0;
    if (level[u] < level[v]) ans += Up(v, level[v] - level[u]); 
    if (level[u] > level[v]) ans += Up(u, level[u] - level[v]);
    if (u == v) return ans;
    int uu = u, vv = v;
    int lc;
    FORD(i, LOG, 0) {
        if (b[u][i] != b[v][i]) {
            u = b[u][i];
            v = b[v][i];
        } else lc = b[u][i];
    }
    ans += Up(uu, level[uu] - level[lc]);
    ans += Up(vv, level[vv] - level[lc]);
    return ans;
}
int f[N];
int root(int u) {
    if (f[u] < 0) return u;
    f[u] = root(f[u]);
    return f[u];
}

void Union(int a, int b) {
    int t = f[a] + f[b];
    if (f[a] > f[b]) swap(a, b);
    f[a] = t;
    f[b] = a;
}

vector<edge> Special;
int Idx[N];
vector<int> sp;
int dd[111][N];
struct Graph {
    priority_queue<pp> heap;
    vector<pp> e[N];

    void reset() {
        FOR(i, 1, n) e[i].clear();
    }
    void addEdge(int u, int v, int c) {
        e[u].push_back(pp(v, c));
    }
    void Run(int k, int s) {
        FOR(i, 1, n) dd[k][i] = inf;
        dd[k][s] = 0;
        heap.push(pp(0, s));
        while (!heap.empty()) {
            int u = heap.top().second;
            int dist = -heap.top().first;
            heap.pop();
            if (dist != dd[k][u]) continue;
            for (pp t : e[u]) {
                int v = t.first;
                int c = t.second;
                if (dd[k][v] > dd[k][u] + c) {
                    dd[k][v] = dd[k][u] + c;
                    heap.push(pp(-dd[k][v], v));
                }
            }
        }
    }
}Graph_Dijk;
bool used[N];
void solve() {
    int q;
    memset(used, false, sizeof used);
    //read(n);read(m);read(q);
    cin>>n>>m>>q;
    Graph_Dijk.reset();
    Special.clear();
    sp.clear();
    FOR(i, 1, n) e[i].clear();
    REP(i, m) {
        //read(s[i].u);read(s[i].v);read(s[i].c);
        cin>>s[i].u>>s[i].v>>s[i].c;
        Graph_Dijk.addEdge(s[i].u, s[i].v, s[i].c);
        Graph_Dijk.addEdge(s[i].v, s[i].u, s[i].c);
    }
    sort(s, s + m);
    FOR(i, 1, n) f[i] = -1;
    REP(i, m) {
        int a = root(s[i].u);
        int b = root(s[i].v);
        if (a != b) {
            Union(a, b);
            e[s[i].u].push_back(pp(s[i].v, s[i].c));
            e[s[i].v].push_back(pp(s[i].u, s[i].c));
        } else {
            Special.push_back(s[i]);
            if (!used[s[i].u]) {
                used[s[i].u] = true;
                sp.push_back(s[i].u);
            }
            if (!used[s[i].v]) {
                used[s[i].v] = true;
                sp.push_back(s[i].v);
            }
        }
    }
    memset(p, 0, sizeof p);
    p[1] = -1;level[1] = 0;
    dfs(1);
    BuildLCA();
    REP(i, sp.size()) {
        Graph_Dijk.Run(i, sp[i]);
        Idx[sp[i]] = i;
    }
    int u, v;
    while (q--) {
        //read(u);read(v);
        cin>>u>>v;
        int ans = lca(u, v);
        for (edge x : Special) {
            ans = min(ans, dd[Idx[x.u]][u] + x.c + dd[Idx[x.v]][v]);
            ans = min(ans, dd[Idx[x.v]][u] + x.c + dd[Idx[x.u]][v]);
        }
        cout<<ans<<'\n';
    }
}
int main() {
    IO;
    int test;cin>>test;//read(test);
    while (test--) solve();
}
