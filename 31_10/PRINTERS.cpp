//http://www.spoj.com/problems/ACQUIRE/
#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 100100
#define pp pair<int, int>
#define IO ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);

using namespace std;
int n;
struct data {
    long long a, b;
}s[N];

bool cmp(const data &aa, const data &bb) {
    return aa.b > bb.b || (aa.b == bb.b && aa.a > bb.a);
}

vector<data> e;

struct ConvexHull {
    vector<long long> a, b;
    vector<double> x;
    int start, last;

    void reset(int n) {
        a.resize(n + 1);
        b.resize(n + 1);
        x.resize(n + 1);
        start = 1;
        last = 0;
    }

    void Up(long long aNew, long long bNew) {
        double xNew = -1e18;
        while (start <= last) {
            xNew = 1.0 * (bNew - b[last]) / (a[last] - aNew);
            if (start == last || xNew >= x[last]) break;
            --last;
        }
        a[++last] = aNew;
        b[last] = bNew;
        x[last] = xNew;
    }

    long long Get(long long p) {
        if (start > last) return 0;
        while (start < last && x[start + 1] <= p) start++;
        return p * a[start] + b[start];
    }

}CH;

long long dp[N];

int main() {
    freopen("PRINTERS.inp","r",stdin);
    freopen("PRINTERS.out","w",stdout);
    IO;
    scanf("%d", &n);
    FOR(i, 1, n) scanf("%lld %lld", &s[i].a, &s[i].b);
    sort(s + 1, s + n + 1, cmp);
    dp[0] = 0;
    int amax = 0;
    e.clear(); e.push_back(s[0]);
    FOR(i, 1, n) {
        if (s[i].a > amax) {
            e.push_back(s[i]);
            amax = s[i].a;
        }
    }
    n = e.size() - 1;
    CH.reset(n + 1);
    FOR(i, 1, n) {
        CH.Up(e[i].b, dp[i - 1]);
        dp[i] = CH.Get(e[i].a);
    }
    printf("%lld", dp[n]);
}
