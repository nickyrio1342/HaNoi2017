#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = a; i<=b ; i++)
#define FORD(i, a, b) for (int i = a; i>=b; i--)
#define REP(i, a) for (int i = 0; i<a; i++)
#define N 100100
#define pp pair<long long, long long>
#define IO cin.tie(NULL);cout.tie(NULL);

using namespace std;

struct ConvexHull {
    vector<long long> a, b;
    vector<double> x;
    int start, last;

    void reset(int n) {
        a.resize(n);
        b.resize(n);
        x.resize(n);
        start = 1;
        last = 0;
    }

    void Up(long long aNew, long long bNew) {
        double xNew = -1e18;
        while (start <= last) {
            if (aNew == a[last] && bNew > b[last]) return;
            xNew = 1.0 * (b[last] - bNew) / (aNew - a[last]);
            if (start == last || xNew > x[last]) break;
            last--;
        }

        a[++last] = aNew;
        b[last] = bNew;
        x[last] = xNew;
    }

    long long value(long long aa, long long bb, int pos) {
        return aa * a[pos] + bb * b[pos];
    }

    long long Get(long long aa, long long bb) {
        int l = start;
        int r = last;
        while (l < r) {
            int m = (l + r) >> 1;
            if (value(aa, bb, m) > value(aa, bb, m + 1)) l = m + 1;
            else r = m;
        }
        return value(aa, bb, l);
    }
}CH;

int n, m, u, v, c, k;
vector<pp> e[N];
priority_queue<pp> heap;
long long d[2][N];
const long long inf = 1e18;

void Dijkstra(int k, int s) {
    while (!heap.empty()) heap.pop();
    heap.push(pp(0,s));
    FOR(i, 1, n) d[k][i] = inf;
    d[k][s] = 0;
    while (!heap.empty()) {
        int u = heap.top().second;
        heap.pop();
        for (pp tt : e[u]) {
            int v = tt.first;
            int c = tt.second;
            if (d[k][v] > d[k][u] + c) {
                d[k][v] = d[k][u] + c;
                heap.push(pp(-d[k][v], v));
            }
        }
    }
}
vector<pp> ee;

long long a, b;

bool cmp(const pp &a, const pp &b) {
    return a.first > b.first || (a.first == b.first && a.second < b.second);
}

int main() {
    IO;
    freopen("MPOINTS.inp","r",stdin);
    freopen("MPOINTS.out","w",stdout);
    scanf("%d %d %d", &n, &m, &k);
    REP(i, m) {
        scanf("%d %d %d", &u, &v, &c);
        e[u].push_back(pp(v, c));
    }
    Dijkstra(0, 1);
    Dijkstra(1, n);
    FOR(i, 1, n) if (d[0][i] != inf && d[1][i] != inf) {
        ee.push_back(pp(d[0][i], d[1][i]));
    }
    CH.reset(ee.size() + 1);
    sort(ee.begin(), ee.end(), cmp);
    for (pp x : ee) CH.Up(x.first, x.second);
    REP(i, k) {
        scanf("%d %d", &a, &b);
        printf("%lld\n", CH.Get(a, b));
    }
}
