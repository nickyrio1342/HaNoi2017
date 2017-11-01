//Tương tự PTREE - SPOJ
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 111
#define pp pair<int, int>
#define IO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);

using namespace std;

int n, k, a[N], p[N], nChild[N];
long long f[N][N], now[N];
vector<int> e[N];

void dfs(int u) {
    nChild[u] = 1;
    f[u][1] = a[u];
    for (int v : e[u]) {
        if (p[v] == 0) {
            p[v] = u;
            dfs(v);
            nChild[u] += nChild[v];
            FOR(j, 2, min(k, nChild[u])) {
                now[j] = 0;
                FOR(t, 1, j - 1)
                    now[j] = max(now[j], f[u][t] + f[v][j - t]);
            }
            FOR(j, 2, min(k, nChild[u])) f[u][j] = max(f[u][j], now[j]);
        }
    }
}

int main() {
    freopen("OPTION.inp","r",stdin);
    freopen("OPTION.out","w",stdout);
    IO;
    cin>>n>>k;
    int v, m;
    FOR(i, 1, n) {
        cin>>a[i]>>m;
        while (m--) {
            cin>>v;
            e[i].push_back(v);
        }
    }
    long long ans = 0;
    FOR(i, 1, n) {
        memset(p, 0, sizeof p);
        memset(f, 0, sizeof f);
        p[i] = -1;
        dfs(i);
        FOR(t, 1, n) FOR(j, 1, min(k, nChild[t])) ans = max(ans, f[t][j]);
    }
    cout<<ans;
}
