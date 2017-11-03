
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 51
#define pp pair<int, int>
#define IO cin.tie(NULL);cout.tie(NULL);

using namespace std;
long long a[2 * N][2 * N], f[64][N][N], g[N][N], gg[N][N], c, K;
int n, m, u, v;

int main() {
  //  freopen("C.inp","r",stdin);
  //  freopen("C.ou","w",stdout);
    IO;
    scanf("%d %d", &n, &m);
    FOR(i, 1, n * 2) FOR(j, 1, n * 2) a[i][j] = 1e18;
    FOR(i, 1, n * 2) a[i][i] = 0;
    while (m--) {
        scanf("%d %d %lld", &u, &v, &c);
        a[u][v] = min(a[u][v], c);
        a[u + n][v + n] = min(a[u + n][v + n], c);
        a[u + n][v] = min(a[u + n][v], -c);
        a[u][v + n] = min(a[u][v + n], -c);
    }
    scanf("%lld", &K);
    //Step 1
    //Floyd
    FOR(k, 1, n) {
        FOR(i, 1, n) FOR(j, 1, 2 * n)
            a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
    }
    FOR(k, n + 1, n + n) {
        FOR(i, 1, 2 * n) FOR(j, n + 1, n + n)
            a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
    }

    FOR(i, 1, n) FOR(j, 1, n) FOR(p, 1, log2(K)) f[p][i][j] = 1e18;
    FOR(i, 1, n) FOR(j, 1, n) {
        f[0][i][j] = min(a[i][j], a[i][j + n]);
        g[i][j] = a[i][j];
    }
    //
    FOR(p, 1, log2(K)) {
        FOR(i, 1, n) FOR(j, 1, n) FOR(k, 1, n) //if (f[p - 1][i][k] != 1e18 && f[p - 1][k][j] != 1e18)
            f[p][i][j] = min(f[p][i][j], f[p - 1][i][k] + f[p - 1][k][j]);
    }
    REP(p, log2(K) + 1) if ((K >> p) & 1) {
        FOR(i, 1, n) FOR(j, 1, n) {
            gg[i][j] = g[i][j];
            FOR(k, 1, n) //if (gg[i][k] != 1e18 && f[p][k][j] != 1e18)
                gg[i][j] = min(gg[i][j], g[i][k] + f[p][k][j]);
        }
        FOR(i, 1, n) FOR(j, 1, n) g[i][j] = gg[i][j];
    }
    printf("%lld", g[1][n]);
}
