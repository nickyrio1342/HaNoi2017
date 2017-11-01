#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 100100
#define pp pair<long long, long long>
#define IO cin.tie(NULL);cout.tie(NULL);
#define sz(a) (int)a.size()
#define x first
#define y second

using namespace std;


int n, m, t[N], c[N];
pp s[N];

long long ccw(pp a, pp b, pp c) {
    long long tmp = (c.y - a.y) * (a.x - b.x) - (a.x - c.x) * (b.y - a.y);
    return tmp;
}
vector<pp> e;
int sz;


struct ConvexHull {
    vector<pp> xx;

    void Up(long long aNew, long long bNew) {
        xx.push_back(pp(aNew, bNew));
        while (xx.size() >= 3 && ccw(xx[sz(xx) - 3], xx[sz(xx) - 2], xx.back()) < 0) xx.erase(xx.end() - 2);
    }

    long long value(long long aa, long long bb, int pos) {
        return aa * xx[pos].first + bb * xx[pos].second;
    }

    long long Get(long long aa, long long bb) {
        int l = 0;
        int r = xx.size() - 1;
        while (l < r) {
            int m = (l + r) >> 1;
            if (value(aa, bb, m) < value(aa, bb, m + 1)) l = m + 1;
            else r = m;
        }
        return value(aa, bb, l);
    }
}CH;

int main() {
    freopen("READERS.inp","r",stdin);
    freopen("READERS.out","w",stdout);
    IO;
    scanf("%d %d", &n, &m);
    FOR(i, 1, n) scanf("%lld", &t[i]);
    FOR(i, 1, m) scanf("%lld", &c[i]);
    long long now = 0;
    FOR(i, 1, n) {
        s[i] = pp(now + t[i], -now);
        CH.Up(s[i].first, s[i].second);
        now += t[i];
    }
    //sort(s, s + n);
    long long ans = s[n].first * c[m];
    FOR(i, 2, m) {
        long long t = CH.Get(c[i - 1], c[i]);
        ans +=  t ;
    }
    printf("%lld", ans);
    return 0;
}
