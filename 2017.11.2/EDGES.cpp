#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 100100
#define pp pair<long long, int>
#define IO cin.tie(NULL);cout.tie(NULL);

using namespace std;

int n, m, u, v, c, IN[N], OUT[N], num[N], low[N], comp, cnt, dd[N];
vector<pp> e[N];
vector<int> ee[N];
priority_queue<pp> heap;
long long d[N];
const long long inf = 1e18;
long long neg;
stack<int> st;

void dfs(int u) {
    num[u] = low[u] = ++cnt;
    st.push(u);
    for (int v : ee[u]) {
        if (dd[v] == 0) {
            if (num[v] == 0) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else low[u] = min(low[u], num[v]);
        }
    }
    if (num[u] == low[u]) {
        int v;
        ++comp;
        do {
            v = st.top();st.pop();
            dd[v] = comp;
        } while (u != v);
    }
}

void Tarjan() {
    cnt = comp = 0;
    FOR(i, 1, n ) num[i] = 0;
    FOR(i, 1, n) if (num[i] == 0) dfs(i);
}

void Dijkstra() {
    while (!heap.empty()) {
        int u = heap.top().second;
        if (IN[dd[u]] == 0) {
            printf("YES\n%lld", d[u] + neg);
            return;
        }
        long long dd = -heap.top().first;
        heap.pop();
        if (dd != d[u]) continue;
        for (pp t : e[u]) {
            int v = t.first;
            int c = t.second;
            if (d[v] > d[u] + c) {
                d[v] = d[u] + c;
                heap.push(pp(-d[v], v));
            }
        }
    }
    printf("NO");
}
set<pp> tab;

int main() {
    freopen("EDGES.inp","r",stdin);
    freopen("EDGES.out","w",stdout);
    IO;
    scanf("%d %d", &n, &m);
    memset(IN, 0, sizeof IN);
    memset(OUT, 0, sizeof OUT);
    while (m--) {
        scanf("%d %d", &u, &v);
        e[u].push_back(pp(v, 0));
        ee[u].push_back(v);
    }
    Tarjan();
    FOR(u, 1, n) {
        for (int v : ee[u]) {
            if (dd[u] != dd[v]) {
                if (tab.find(pp(dd[u], dd[v])) == tab.end()) {
                    IN[dd[v]]++;
                    OUT[dd[u]]++;
                    tab.insert(pp(dd[u], dd[v]));
                }
            }
        }
    }
    scanf("%d", &m);
    neg = 0;
    while (m--) {
        scanf("%d %d %d", &u, &v, &c);
        if (c < 0) {
            e[u].push_back(pp(v, 0));
            neg += c;
        }else e[u].push_back(pp(v, c));
    }
    FOR(i, 1, n) if (OUT[dd[i]] == 0) {
        d[i] = 0;
        heap.push(pp(0ll, i));
    } else d[i] = inf;
    Dijkstra();
}
