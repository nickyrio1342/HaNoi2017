#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 4040
#define pp pair<int, int>
#define IO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define bit(S, i) ((S >> i) & 1)

using namespace std;

int m, k, f[N][N], n;
string st;

void init() {
    memset(f, 0, sizeof f);
    FOR(i, 1, n) FOR(j, i, n)
        if (st[i] == st[j])
            f[i][j] = f[i][j] = f[i - 1][j - 1];
        else f[i][j] = f[i - 1][j - 1] + 1;
}

int main() {
   IO;
   freopen("VIRUS.inp","r",stdin);
   freopen("VIRUS.out","w",stdout);
   cin>>m>>st;
   n = st.size();
   st = '~' + st;
   init();
   while (m--) {
        cin>>k;
        int ans = 0;
        FOR(i, 1, n - 1) FOR(j, i + 1, n) if (2 * i - j >= 0){
            if (f[i][j] - f[2 * i - j][i] <= k) {
                ans = max(ans, j - i);
            }
        }
        cout<<ans<<endl;
   }
}
