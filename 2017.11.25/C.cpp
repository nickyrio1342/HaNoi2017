#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 2222
#define pp pair<int, int>
#define IO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define bit(S, i) (((S) >> (i)) & 1)

using namespace std;

int n, a[N];
int dp[N][N];

bool ok(int S) {
    if (bit(S, 8)) return false;
    if (bit(S, 0)) return false;
    if (bit(S, 1)) return false;
    return true;
}
int main() {
    IO;
    cin>>n;
    FOR(i, 1, n) cin>>a[i];
    sort(a + 1, a + n + 1);
    FOR(i, 1, n) REP(S, 1 << 10) dp[i][S] = -1;
    dp[1][1 << 9] = 1;
    dp[1][0] = 0;
    FOR(i, 2, n) {
        REP(S, 1 << 10) if (dp[i - 1][S] != -1) {
            int newS = 0;
            if (a[i] - a[i - 1] < 11) newS = S >> (a[i] - a[i - 1]);
            dp[i][newS] = max(dp[i][newS], dp[i - 1][S]);
            newS = newS | (1 << 9);
            if (ok(newS))
                dp[i][newS] = max(dp[i][newS], dp[i - 1][S] + 1);
        }
    }
    int ans = dp[n][0];
    REP(i, 1 << 10) ans = max(ans, dp[n][i]);
    cout<<n - ans;
}
