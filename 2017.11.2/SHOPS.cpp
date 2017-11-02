#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 1010100
#define pp pair<int, int>
#define IO cin.tie(NULL);cout.tie(NULL);

using namespace std;

int n, BIT[N];
long long s[N], a[N], t[N], c[N];
vector<long long> e;

void Up(int u, int val) {
    for(; u > 0; u -= u&-u) {
        if (BIT[u] == -1) BIT[u] = val;
        else BIT[u] = min(BIT[u], val);
    }
}

int Get(int u) {
    int ans = 1e9;
    for(; u <=2 * n + 10; u += u&-u) {
        if (BIT[u] != -1) ans = min(ans, BIT[u]);
    }
    if (ans == 1e9) ans = -1;
    return ans;
}
long long S;
int main() {
  //  freopen("SHOPS.inp","r",stdin);
  //  freopen("SHOPS.out","w",stdout);
    IO;
    scanf("%d %lld", &n, &S);
    long long now = 0;
    FOR(i, 1, n) scanf("%lld", &a[i]);
    s[0] = 0;
    e.push_back(0);
    e.push_back(-S);
    FOR(i, 1, n) {
        s[i] = s[i - 1] + a[i];
        e.push_back(s[i]);
        e.push_back(s[i] - S);
    }
    sort(e.begin(), e.end());
    FOR(i, 1, n) {
        t[i] = lower_bound(e.begin(), e.end(), s[i]) - e.begin() + 1;
        c[i] = lower_bound(e.begin(), e.end(), s[i] - S) - e.begin() + 1;
    }
    int ans = 0; int ansb = 0;
    int pos = lower_bound(e.begin(), e.end(), 0) - e.begin() + 1;
    FOR(i, 0, n * 2 + 10) BIT[i] = -1;
    Up(pos, 0);
    FOR(i, 1, n) {
        int now = Get(c[i]);
        if (now != -1) {
            if (ans < i - now) {
                ans = i - now;
                ansb = now + 1;
            }
        }
        Up(t[i], i);
    }
    printf("%d %d", ans, ansb);
}
