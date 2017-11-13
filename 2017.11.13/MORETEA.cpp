#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 201000
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

int nChild[N], cnt, p[N], in[N], Chead[N], head[N], pos[N], nChain, level[N];
vector<int> e[N];

void dfs(int u) {
    nChild[u] = 1;
    for (int v : e[u]) if (p[v] == 0) {
        p[v] = u;
        level[v] = level[u] + 1;
        dfs(v);
        nChild[u] += nChild[v];
    }
}

void hld(int u) {
    if (Chead[nChain] == 0) Chead[nChain] = u;
    head[u] = Chead[nChain];
    in[++cnt] = u;
    pos[u] = cnt;
    int special = -1, mx = 0;
    for (int v : e[u]) if (v != p[u]){
        if (mx < nChild[v]) {
            special = v;
            mx = nChild[v];
        }
    }

    if (special != -1) {
        hld(special);
        for (int v : e[u]) if (v != p[u] && v != special) {
            ++nChain;
            hld(v);
        }
    }
}

struct data {
    long long MAX, cntLimit;
    long long sum;
}IT[N * 4];

int n, M, q, a[N];
long long lazy[4 * N];

data Union(const data &a, const data &b) {
    data res;
    res.MAX = max(a.MAX, b.MAX);
    res.cntLimit = a.cntLimit + b.cntLimit;
    res.sum = a.sum + b.sum;
    return res;
}

void buildIT(int k, int l, int r) {
    if (l == r) {
        if (a[in[l]] == M) {
            IT[k].cntLimit = 1;
            IT[k].MAX = -1;
        } else {
            IT[k].cntLimit = 0;
            IT[k].MAX = a[in[l]];
        }
        IT[k].sum = a[in[l]];
        return;
    }
    int m = (l + r) >> 1;
    buildIT(k * 2, l, m);
    buildIT(k * 2 + 1, m + 1, r);
    IT[k] = Union(IT[k * 2], IT[k * 2 + 1]);
}

void Down(int k, int l, int r) {
    if (lazy[k] == 0) return;
    int m = (l + r) >> 1;
    if (IT[k * 2].MAX != -1) {
        IT[k * 2].sum += lazy[k] * (m - l + 1 - IT[k * 2].cntLimit);
        lazy[k * 2] += lazy[k];
        IT[k * 2].MAX += lazy[k];
    }
    if (IT[k * 2 + 1].MAX != -1) {
        IT[k * 2 + 1].sum += lazy[k] * (r - m - IT[k * 2 + 1].cntLimit);
        IT[k * 2 + 1].MAX += lazy[k];
        lazy[k * 2 + 1] += lazy[k];
    }
    lazy[k] = 0;
}
void Up(int k, int l, int r, int u, int v, int val) {
    if (l > v || r < u || IT[k].MAX == -1) return;
    if (u <= l && r <= v) {
        IT[k].MAX += val;
        IT[k].sum += 1ll * val * (r - l + 1 - IT[k].cntLimit);
        lazy[k] += val;
        return;
    }
    Down(k, l, r);
    int m = (l + r) >> 1;
    Up(k * 2, l, m, u, v, val);
    Up(k * 2 + 1, m + 1, r, u, v, val);
    IT[k] = Union(IT[k * 2], IT[k * 2 + 1]);
}

long long get(int k, int l, int r, int u, int v) {
    if (l > v || r < u) return 0;
    if (u <= l && r <= v) return IT[k].sum;
    Down(k, l, r);
    int m = (l + r) >> 1;
    return get(k * 2, l, m, u, v) + get(k * 2 + 1, m + 1, r, u, v);
}

void research(int k, int l, int r) {
    if (IT[k].MAX < M) return;
    if (l == r) {
        a[in[l]] = M;
        IT[k].cntLimit = 1;
        IT[k].sum = M;
        IT[k].MAX = -1;
        return;
    }
    Down(k, l, r);
    int m = (l + r) >> 1;
    research(k * 2, l, m);
    research(k * 2 + 1, m + 1, r);
    IT[k] = Union(IT[k * 2], IT[k * 2 + 1]);
}

// HLD query

int lca(int u, int v) {
    while (true) {
        if (head[u] == head[v]) {
            if (level[u] > level[v]) return v;
            return u;
        }
        if (level[head[u]] > level[head[v]]) u = p[head[u]];
        else v = p[head[v]];
    }
}

long long query(int u, int lc, int t) {
    long long ans = 0;
    if (u == lc && t) return 0;
    while (true) {
        if (head[u] == head[lc]) {
            if (t) {
                ans += get(1, 1, n, pos[lc] + 1, pos[u]);
                research(1, 1, n);
                return ans;
            }
            ans += get(1, 1, n, pos[lc], pos[u]);
            research(1, 1, n);
            return ans;
        }
        ans += get(1, 1, n, pos[head[u]], pos[u]);
        research(1, 1, n);
        u = p[head[u]];
    }
}

long long cal(int u, int v) {
    int lc = lca(u, v);
    long long ans = query(u, lc, 0) + query(v, lc, 1);
    return ans;
}

void Upp(int u, int lc, int t, int val) {
    if (u == lc && t) return;
    while (true) {
        if (head[u] == head[lc]) {
            if (t) Up(1, 1, n, pos[lc] + 1, pos[u], val);
            else Up(1, 1, n, pos[lc], pos[u], val);
            research(1, 1, n);
            return;
        }
        Up(1, 1, n, pos[head[u]], pos[u], val);
        research(1, 1, n);
        u = p[head[u]];
    }
}
void Update(int u, int v, int val) {
    int lc = lca(u, v);
    Upp(u, lc, 0, val); Upp(v, lc, 1, val);
}
int main() {
    IO;
    freopen("MORETEA.inp","r",stdin);
  freopen("MORETEA.out","w",stdout);
//  freopen("E:\\input.txt","r",stdin);
 // freopen("E:\\out.txt","w",stdout);
    int u, v;
    read(n);read(M);read(q);
    FOR(i, 1, n) read(a[i]);
    REP(i, n - 1) {
        read(u);read(v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    p[1] = -1;
    dfs(1);
    nChain = 0;
    hld(1);
    buildIT(1, 1, n);
    int t, x;
    while (q--) {
        read(t); read(u); read(v);
        if (t) writeln(cal(u, v));
        else {
            read(x);
            Update(u, v, x);
        }
    }
}
